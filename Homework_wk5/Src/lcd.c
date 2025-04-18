/**
  ******************************************************************************
  * @file		lcd.c
  * @brief		LCD control source file
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/

#include <stdint.h>
#include  "lcd.h"
#include "gpio.h"
#include "timer.h"

static volatile uint32_t *gpioa = (uint32_t*) GPIOA;
static volatile uint32_t *gpioc = (uint32_t*) GPIOC;

/**
 * @brief initializes GPIOA and GPIOC for LCD use
 */
static void port_init(void) {
	volatile uint32_t *rcc_enr = (uint32_t*) RCC_ENR;
	*rcc_enr |= GPIOAEN | GPIOCEN;

	gpioa[MODER_INDEX] |= (0b01<<4*2)|(0b01<<5*2)|(0b01<<6*2)|(0b01<<7*2)|
			(0b01<<8*2)|(0b01<<9*2)|(0b01<<10*2)|(0b01<<11*2);
	gpioc[MODER_INDEX] |= (0b01<<8*2)|(0b01<<9*2)|(0b01<<10*2);

	//set to write mode
	gpioc[BSRR_INDEX] |= LCD_RW_WRITE;
}

/**
 * @brief executes the given command OR data by loading the databus
 * @param cmd_data - the 8 bit command or data to be sent to LCD
 */
static void lcd_exec(uint8_t cmd_data) {
	// load databus
	gpioa[BSRR_INDEX] |= (cmd_data<<4);

	gpioc[BSRR_INDEX] |= LCD_E_SET;
	//delay for >500ns
	delay_us(1);
	gpioc[BSRR_INDEX] |= LCD_E_CLEAR;

	delay_us(100);
}

/**
 * @brief sets the LCD up for command mode and execution
 * @ param cmd - the 8 bit command to be executed
 */
static void lcd_cmd(uint8_t cmd) {
	gpioc[BSRR_INDEX] |= LCD_RS_CLEAR;
	lcd_exec(cmd);
}

/**
 * @brief sets the LCD up for data write mode and display
 * @ param data - the 8 bit data to be stored to memory
 */
static void lcd_data(uint8_t data) {
	gpioc[BSRR_INDEX] |= LCD_RS_SET;
	lcd_exec(data);
}

/**
 * @brief initializes everything for LCD use and display,
 * calling on helper functions to accomplish much
 */
void lcd_init(void) {
	// gpio set up
	port_init();

	//send init sequence to LCD
	delay_ms(200);		//delay for power on
	lcd_cmd(0x30);		//wake up #1
	delay_ms(100);		//delay #1
	lcd_cmd(0x30);		//wake up #2
	delay_ms(100);		//delay #2
	lcd_cmd(0x30);		//wake up #3
	delay_ms(100);		//delay #3

	//now for our set up
	lcd_cmd(0x38);		//8-bit/2-line/5x8 font
	lcd_cmd(0x14);		//cursor moving right
	lcd_cmd(0x0F);		//Display - on / Cursor - on
	lcd_cmd(0x06);		//Entry mode set

	lcd_clear();
}

void lcd_clear(void) {
	lcd_cmd(1);
	delay_ms(10);
}

void lcd_home(void) {
	lcd_cmd(0b10);
	delay_ms(10);
}

void lcd_set_position(int row, int col) {
	uint8_t cmd = (row * 0x40) + (col);
	lcd_cmd((1<<7)|cmd);
}

void lcd_print_char(char c) {
	lcd_data(c);
}

int lcd_print_string(char* s) {
	int i = 0;
	while(s[i] != '\0') {
		lcd_data(s[i]);
		i++;
	}
	return i;
}

int lcd_print_hex(int lead_zeroes, int width, int num) {
	char print[width+1]; //account for \0
	print[0] = '0';
	print[1] = 'x';

	for (int i = width-1; i > 1; --i) {
		int digit = num & 0xF; //get last hex digit
		print[i] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
		num = num>>4;
	}

	if(!lead_zeroes) {
		print[0] = '0';
		print[1] = '0';
		char *walk = print+2;
		while (*walk++ == '0'); //move pointer to first non zero
		walk--; //move back one because the ++ increments even after loop end
		*(walk-2) = '0';
		*(walk-1) = 'x';
		int i = 0;
		while (print[i+1] != 'x') {
			print[i] = ' ';
			i++;
		}
	}
	return lcd_print_string(print);
}

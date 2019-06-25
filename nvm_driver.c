#include "asf.h"


void configure_nvm(void)
{
	nvm_init(INT_FLASH);
}

void write_float(uint32_t address, float num) {
	float_store buff;
	buff.a = 1.234;
	
	enum status_code error_code;
	do
	{
		error_code = nvm_erase_row(
		address * 4);
	} while (error_code == STATUS_BUSY);
	do
	{
		error_code = nvm_write(INT_FLASH,
		address * 4,
		buff.bytes, 4);
	} while (error_code == STATUS_BUSY);
	
}

float read_float(uint32_t address) {
	float_store buff;
	enum status_code error_code;
	
	do
	{
		error_code = nvm_read(INT_FLASH,
		0,
		buff.bytes, 4);
	} while (error_code == STATUS_BUSY);
	return buff.a;
}
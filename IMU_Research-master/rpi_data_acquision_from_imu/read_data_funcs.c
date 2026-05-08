#include "smbus.h"

int soft_reset(int fd)
{
	int32_t ret;
	ret = i2c_smbus_write_byte_data(fd, 0x7E, 0xB6);
	sleep(0.015);
	if(ret < 0)
		return(0);
	else
		return(1);
	return(0);
}

int set_normal_mode(int fd)
{
	int32_t ret;
	ret = i2c_smbus_write_byte_data(fd, 0x7E, 0x11);
	if(ret < 0) return(0);
	sleep(0.05);
	ret = i2c_smbus_write_byte_data(fd, 0x7E, 0x15);
	if(ret < 0) return(0);
	sleep(0.1);
	ret = i2c_smbus_write_byte_data(fd, 0x7E, 0x19);
	if(ret < 0) return(0);
	sleep(0.01);
	ret = set_mag(fd);
	if(ret < 0) return(0);
	return(1);
}

int set_mag(int fd)
{
	int32_t ret;
	ret = i2c_smbus_write_byte_data(fd, 0x4C, 0x80);
	sleep(0.06);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4F, 0x01);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4E, 0x4B);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4F, 0x04);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4E, 0x51);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4F, 0x0E);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4E, 0x52);
	
	//prepare mag_if data_mode
	ret = i2c_smbus_write_byte_data(fd, 0x4F, 0x02);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4E, 0x4C);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x4D, 0x42);
	if(ret < 0) return(0);
	
	//set ODR
	ret = i2c_smbus_write_byte_data(fd, 0x44, 0x08);
	if(ret < 0) return(0);

	ret = i2c_smbus_write_byte_data(fd, 0x4C, 0x03); //set 0 offset 8bit data
	sleep(0.06);
	return(1);
}

int set_low_power(int fd)
{
	soft_reset(fd);
	sleep(0.1);
	set_mag(fd);
	sleep(0.1);
	int32_t ret;
	ret = i2c_smbus_write_byte_data(fd, 0x7E, 0x12);
	sleep(0.1);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x7E, 0x17);
	sleep(0.1);
	if(ret < 0) return(0);
	ret = i2c_smbus_write_byte_data(fd, 0x7E, 0x1B);
	sleep(0.1);
	if(ret < 0) return(0);

	return(1);
}

int set_gyro_range(int fd, uint8_t sat, uint8_t freq)
{
	int32_t ret;
	if (freq == 800)
		ret = i2c_smbus_write_byte_data(fd, 0x42, 0x2B);
	else if (freq == 400)
		ret = i2c_smbus_write_byte_data(fd, 0x42, 0x2A);
	else //100 Hz
		ret = i2c_smbus_write_byte_data(fd, 0x42, 0x28);
	if(ret < 0) return(0);
	//ret = i2c_smbus_read_byte_data(fd, 0x42);
	//printf("0x42 ->%X\n", ret);
	if (sat == 125)
		ret = i2c_smbus_write_byte_data(fd, 0x43, 0x04);
	else if (sat == 250)
		ret = i2c_smbus_write_byte_data(fd, 0x43, 0x03);
	else //500 deg/s
		ret = i2c_smbus_write_byte_data(fd, 0x43, 0x02);
	if(ret < 0) return(0);
	//ret = i2c_smbus_read_byte_data(fd, 0x43);
	//printf("0x43 ->%X\n", ret);
	return(1);
}

int set_acc_range(int fd, uint8_t sat, uint8_t freq)
{
	int32_t ret;

	if(freq == 800)
		ret = i2c_smbus_write_byte_data(fd, 0x40, 0x2B);
	else if(freq == 400)
		ret = i2c_smbus_write_byte_data(fd, 0x40, 0x2A);
	else 
		ret = i2c_smbus_write_byte_data(fd, 0x40, 0x29);
	if(ret < 0) return(0);
	
	//ret = i2c_smbus_read_byte_data(fd, 0x40);
	//printf("0x40 ->%X\n", ret);

	if(sat == 2) 	
		ret = i2c_smbus_write_byte_data(fd, 0x41, 0x03);
	else if(sat == 4)
		ret = i2c_smbus_write_byte_data(fd, 0x41, 0x05);
	else //8g
		ret = i2c_smbus_write_byte_data(fd, 0x41, 0x08);
	if(ret < 0) return(0);
	
	//ret = i2c_smbus_read_byte_data(fd, 0x41);
	//printf("0x41 ->%X\n", ret);
	return(1);
}

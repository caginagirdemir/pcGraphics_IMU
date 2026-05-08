#include <stdint.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#ifndef NULL
#define NULL 0
#endif

int32_t i2c_smbus_access(int file, char read_write, uint8_t command, int size, union i2c_smbus_data *data)
{
	struct i2c_smbus_ioctl_data args;
	int32_t err;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;
	
	err = ioctl(file, I2C_SMBUS, &args);
	if(err = -1)
		err = -errno;
	return err;
}

int32_t i2c_smbus_read_byte_data(int file, uint8_t reg)
{
	union i2c_smbus_data data;
	int err;

	err = i2c_smbus_access(file, I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data);
	if (err < 0)
		return err;
	return 0x0FF & data.byte;
}


int32_t i2c_smbus_read_word_data(int file, uint8_t reg)
{
	union 	i2c_smbus_data data;
	int 	err;

	err = i2c_smbus_access(file, I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data);
	if(err < 0)
		return err;
	return 0x0FFFF & data.word;
}

int32_t i2c_smbus_read_i2c_block_data(int file, uint8_t reg, uint8_t length, uint8_t *value)
{
	union	i2c_smbus_data data;
	int	i, err;

	if (length > I2C_SMBUS_BLOCK_MAX)
		length = I2C_SMBUS_BLOCK_MAX;
	data.block[0] = length;

	err = i2c_smbus_access(file, I2C_SMBUS_READ, reg, length == 32 ? I2C_SMBUS_I2C_BLOCK_BROKEN : I2C_SMBUS_I2C_BLOCK_DATA, &data);
	if(err < 0)
		return err;
	for(i = 1; i <= data.block[0]; i++)
		value[i-1] = data.block[i];
	return data.block[0];
}

int32_t i2c_smbus_write_byte_data(int file, uint8_t reg, uint8_t value)
{
	union	i2c_smbus_data data;
	data.byte = value;
	return i2c_smbus_access(file, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data);
}

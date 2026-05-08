#ifndef SMBUS_H
#define SMBUS_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <stdint.h>

extern int32_t i2c_smbus_read_byte_data(int file, uint8_t reg);

extern int32_t i2c_smbus_read_word_data(int file, uint8_t reg);


extern int32_t i2c_smbus_read_i2c_block_data(int file, uint8_t reg, uint8_t length, uint8_t *value);

extern int32_t i2c_smbus_write_byte_data(int file, uint8_t reg, uint8_t value);

int soft_reset(int fd);
int set_normal_mode(int fd);
int set_mag(int fd);
int set_low_power(int fd);
int set_gyro_range(int fd, uint8_t sat, uint8_t freq);
int set_acc_range(int fd, uint8_t sat, uint8_t freq);

#endif

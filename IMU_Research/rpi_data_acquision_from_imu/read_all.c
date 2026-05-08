#include "smbus.h"
#include <signal.h>
#define ACC_2G_VALUE 0.000061035
#define ACC_4G_VALUE 0.000122070
#define ACC_8G_VALUE 0.000244141
#define ACC_16_VALUE 0.000488281

#define GYRO_125_VALUE 0.0038110
#define GYRO_250_VALUE 0.0076220
#define GYRO_500_VALUE 0.0152439
#define GYRO_1000_VALUE 0.0304878
#define GYRO_2000_VALUE 0.0609756

int fd;
FILE *filePointer;

void handle_sigint(int sig)
{
	close(fd);
	fclose(filePointer);
	write(1,"Interrupt Exit\n", 5);
	exit(1);

}

void exit_f(void)
{
	write(1,"Read Error Exit\n", 16);
	close(fd);
	fclose(filePointer);
	exit(1);
}

int main(int argc, char **argv)
{
	const char *device = "/dev/i2c-1";
	const uint8_t address = 0x68;

	fd = open(device, O_RDWR);
	if(fd < 0)
		return(-1);
	if (ioctl(fd, I2C_SLAVE, address) < 0)
	{
		printf("Error\n");
		close(fd);
		exit(1);
	}
	if(!argv[1])
	{
		printf("File name error\n");
		close(fd);
		return(0);
	}
	else
	{
		filePointer = fopen(argv[1], "w");
		if(filePointer < 0)
			printf("open error");
	}
	//soft_reset(fd);
	if (set_normal_mode(fd) == 0)
		return(0);
	if(set_gyro_range(fd, (uint8_t) 125, (uint8_t) 800) == 0)
		return(0); //fd, saturation, frequency
	if(set_acc_range(fd, (uint8_t) 2, (uint8_t) 800) == 0)
		return(0);

	signal(SIGINT, handle_sigint);
	uint8_t data[26];

	int16_t mag[3];
	int16_t gyro[3];
	int16_t acc[3];
	int16_t rhall;

	int32_t ret;

	float mag_f[3];
	float gyro_f[3];
	float acc_f[3];
	float rhall_f;

	uint8_t ret_2;

	ret = i2c_smbus_write_byte_data(fd, 0x51, 0x00);
	while(1)
	{
		
		ret = i2c_smbus_read_i2c_block_data(fd, 0x04, 26, data);
		if(ret < 0) exit_f();
			
		if(data[20] & 0x20)
		{
		////MAG READ
		mag[0] = ((data[1] << 8) | (data[0]));
		mag[1] = ((data[3] << 8) | (data[2]));
		mag[2] = ((data[5] << 8) | (data[4]));

		////RHALL READ
		rhall = ((data[7] << 8) | data[6]);


		//GYRO READ
		gyro[0] =  (data[9] << 8) | (data[8]);
        	gyro[1] =  (data[11] << 8) | (data[10]);
        	gyro[2] =  (data[13] << 8) | (data[12]);

		////ACC READ
        	acc[0] =  (data[15] << 8) | (data[14]);
        	acc[1] =  (data[17] << 8) | (data[16]);
       		acc[2] =  (data[19] << 8) | (data[18]);
		
		
		acc_f[0] = acc[0] * ACC_2G_VALUE * 9.8;
		acc_f[1] = acc[1] * ACC_2G_VALUE * 9.8;
		acc_f[2] = acc[2] * ACC_2G_VALUE * 9.8;

		gyro_f[0] = gyro[0] * GYRO_125_VALUE;
		gyro_f[1] = gyro[1] * GYRO_125_VALUE;
		gyro_f[2] = gyro[2] * GYRO_125_VALUE;

		mag_f[0] = mag[0] * 0.3;
		mag_f[1] = mag[1] * 0.3;
		mag_f[2] = mag[2] * 0.3;

		rhall_f = rhall;
	
		fprintf(filePointer, "%.2f ,%.2f ,%.2f ,%.2f ,%.2f ,%.2f ,%.2f ,%.2f ,%.2f\n",acc_f[0], acc_f[1], acc_f[2],gyro_f[0],gyro_f[1],gyro_f[2],mag_f[0],mag_f[1],mag_f[2]);
		}
	}

	//ret = i2c_smbus_write_byte_data(fd, 0x51, 0x10);
	//ret = i2c_smbus_read_byte_data(fd, 0x51);
	//printf("%x\n", ret);
	//set_low_power(fd);
	printf("test\n");
	close(fd);
	return(0);
}

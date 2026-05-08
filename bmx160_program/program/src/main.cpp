#include <iostream>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "../inc/Realtime.h"
#include "../inc/i2c-utils.h"

using namespace std;

const char	*device = "/dev/i2c-1";
int			fd;
FILE		*filePointer;
uint8_t 	buffer[720000][15];
int 		i = 0;
char		filename[20];

void	*get_time(void *arg)
{
	
	return (0);
}

void	exit_procedure(int signum)
{

	printf("\033[K\033[1;31mExit procedure begin...\033[0m\n");
	filePointer = fopen(filename, "w");
	unsigned char acc_range = i2c_smbus_read_byte_data(fd, 0x41);
	unsigned char gyro_range = i2c_smbus_read_byte_data(fd, 0x43);
	fprintf(filePointer, "%02X,%02X\n", acc_range, gyro_range);
	int j = -1;
	while(++j < i)
		fprintf(filePointer,"%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X\n", buffer[j][14],buffer[j][13],buffer[j][12], buffer[j][11],buffer[j][10],buffer[j][9],buffer[j][8],buffer[j][7],buffer[j][6], buffer[j][5],buffer[j][4],buffer[j][3],buffer[j][2],buffer[j][1],buffer[j][0]);
	fclose(filePointer);
	exit(1);
}

void	i2c_read_func(int signum)
{
	i2c_smbus_read_i2c_block_data(fd, 0x0C, 15, buffer[i++]);
}

int main(int argc, char **argv)
{
	
	fd = open(device, O_RDWR);
	if(fd < 0)
        return(printf("IMU Status : \033[1;31m Offline \n\033[0m"));
    if(ioctl(fd, I2C_SLAVE, 0x68) < 0)
        return(printf("IMU Status : \033[1;31m Offline \n\033[0m"));
    if(i2c_smbus_read_byte_data(fd, 0x00) != 0xD8)
        return(printf("IMU Status : \033[1;31m Offline \n\033[0m"));

	printf("Enter file name [Max:20 character]:");
	scanf("%[^\n]s",filename);

	Realtime::setup();
	struct itimerval timer1;
	timer1.it_value.tv_sec = 0;
	timer1.it_value.tv_usec = 2857;
	timer1.it_interval.tv_sec = 0;
	timer1.it_interval.tv_usec = 2857;
	setitimer(ITIMER_REAL, &timer1, NULL);
	signal(SIGALRM, i2c_read_func);
	signal(SIGINT, exit_procedure);
	printf("\033[1;32mReading...\033[0m\n");
	while(1)
		pause();
	
	return 0;
}

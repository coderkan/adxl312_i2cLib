#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "adxl312.h"

int i2c_init(char *i2cdevice,int addr){
	int file;
	if( ( file = open(i2cdevice,O_RDWR)) < 0 ){
		perror("Failed to open the i2c bus\n");
		return -1;
	}
	if( ioctl(file,I2C_SLAVE,addr) < 0 ) {
		printf("Failed to talk i2c\n");
		return -1;
	}
	return file;
}

int i2c_writeByte(int file,int addr,int value){
	char buf[10] = {0};
	buf[0] = addr;
	buf[1] = value;
	if(write(file,buf,2) != 2){
		printf("Error setting i2c device\n");
		return -1;
	}
	return 1;
}

int i2c_writeBytes(int file,int addr,char value[10],int nbytes){
	int i;
	unsigned char buf[10] = {0};
	buf[0] = addr ;
	for(i=0;i<nbytes;i++)
		buf[1+i] = value[i];
	if(write(file,buf,nbytes) != nbytes){
		printf("Error writing bytes to i2c device\n");
		return -1;
	}
	return 1;
}

char i2c_readByte(int file,int addr){

	char buf = addr;
	if(write(file,&buf,1) != 1 ){
		printf("Error reading byte from i2c device\n");
		return -1;
	}
	buf = '\0';
	if(read(file,&buf,1)!=1){
		printf("Error reading byte from i2c device\n");
		return -1;
	}
	return buf;
}

int i2c_readByte(int file,int addr1,int addr2){

	char buf1,buf2;
	int fl = 0x0000FFFF;
	if(write(file,&addr1,1) != 1 ){
		printf("Error reading byte from i2c device\n");
		return -1;
	}
	if(read(file,&buf1,1)!=1){
		printf("Error reading byte from i2c device\n");
		return -1;
	}
	if(write(file,&addr2,1) != 1 ){
		printf("Error reading byte from i2c device\n");
		return -1;
	}
	if(read(file,&buf2,1)!=1){
		printf("Error reading byte from i2c device\n");
		return -1;
	}
	printf(":::  0x%02x  ::: 0x%02x \n",buf1,buf2);
	int bf = ((int)buf1 << 8) | buf2;
	return (fl&bf);
}

char *i2c_readBytes(int file,int addr,int nbytes){
	char *bufx;
	if( ( bufx = (char*)calloc(nbytes,sizeof(char)) ) == NULL ){
		printf("Error allocating buffer...\n");
		return NULL;
	}
	char buf = addr;
	if(write(file,&buf,1) != 1 ){
		printf("Error reading bytes from i2c device\n");
		return NULL;
	}
	if(read(file,bufx,nbytes) != nbytes){
		printf("Error reading byte from i2c device\n");
		return NULL;
	}
	return bufx;
}

int i2c_close(int file){
	if(close(file)!=0){
		printf("Error while closing file...\n");
		return -1;
	}
	return 1;
}

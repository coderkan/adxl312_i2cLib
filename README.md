# adxl312_i2cLib

This Library can be used to communicate with the I2C protocol for the [ADXL312](http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL312.pdf) Digital Accelerometer in Embedded Linux Systems.

You can find detailed definitions of ADXL312 in the [adxl312_io.h] (https://github.com/coderkan/adxl312_i2cLib/blob/master/adxl312_io.h)library. 

* [Setup](#setup)
* [Write Byte](#write-byte)
* [Write Bytes](#write-bytes)
* [Read Byte](#read-byte)
* [Read Bytes](#read-bytes)
* [Close](#close)


## Setup

`i2c_init` function takes 2 parameters. They are `\*i2cdevice` and `addr`. This function open device and talk with i2c slave. If connection has any error return -1. If connection is Ok than return opened file data.

```C
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
```

## Write Byte

`i2c_writeByte` function takes 3 parameters. They are `file`,`addr` and `value`. `file` is opened device and `addr` is the address to be written and `value` is the value to send. This function returns 1 if write correctly else return -1.

```C
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
```

## Write Bytes

`i2c_writeBytes` function takes 4 parameters. They are `file`,`addr`, `value[]` and `nbytes`. `file` is opened device and `addr` is the address to be written, `value[]` is the array values to send and `nbytes` shows how many bytes are written. This function returns 1 if write correctly else return -1.

```C
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
```

## Read Byte

`i2c_readByte` function takes 2 parameters and its returning type is a `char`. `file` is opened device and `addr` is a address to be read. This function returns the byte value read from the address if read is successful, otherwise returns -1.


```C
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
```

This function takes 4 parameters. It reads more than one address from device. This function freturns 16 bit byte value read from the address if read is successful, otherwise return -1.

```C
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
```

## Read Bytes

`*i2c_readBytes` function takes 3 parameters and its returning type is a `char*`. `file` is opened device, `addr` is a address to be read and `nbytes`shows how many bytes are read. This function returns the byte array value read from the address if read is successful, otherwise returns `NULL`.

```C
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
```

## Close

Close opened file function.

```C
int i2c_close(int file){
	if(close(file)!=0){
		printf("Error while closing file...\n");
		return -1;
	}
	return 1;
}
```

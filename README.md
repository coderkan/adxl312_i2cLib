# adxl312_i2cLib

This library can be use for embedded Linux systems to communicate protocol I2C for [ADXL312](http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL312.pdf) Digital Accelerometer. 


Definition of ADXL312 you can check **adxl312_io.h** library. More detail you can check this out [file](https://github.com/coderkan/adxl312_i2cLib/blob/master/adxl312_io.h).

Init I2C setup. Pass `i2cdevice` and `addr`. Return file address if write correctly else return -1.

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

Write a byte to given address and file. `file` is a value that is returned `i2c_init` function. `value` is a value you want to write. Return 1 if write correctly else return -1.

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

Write more than one byte to given file. `file` is a value that returned `i2c_init` function and `value` is a byte array you want to send and `nbytes` is a array length. Return 1 if write correctly else return -1.
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
Read a byte from given file. `file` is a value that returned `i2c_init` function and `addr` is a address you want to read.  Return value is a byte readed value from address if read byte is correct else return -1.

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

Read 2 byte from given file. `file` is a value that returned `i2c_init` function and `addr1` and `addr2` is a address you want to read. Return value 16 bit readed value from address if read byte is correct else return -1.

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

Read given byte size from file. `file` is a value that returned `i2c_init` function and `addr` is a address you want to read. `nbytes` is size of array. Return `nbytes` array pointer if read bytes is correct else return `NULL`  .

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

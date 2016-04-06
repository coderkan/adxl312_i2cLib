#ifndef __ADXL312_H
#define __ADXL312_H
#include "adxl312_io.h"
/**
 * Writing one byte to i2c device.
 * Args: 
 * 		i2cdevice: i2c bus name/path ( eg /dev/i2c-2 )
 * 		addr: i2c device address  
 * Return:
 * 		if an error occured -1 return, otherwise, returned opened file.
 * */
int i2c_init(char *i2cdevice,int addr);

/**
 * Writing one byte to i2c device.
 * Args: 
 * 		file: i2c_init return value.
 * 		addr: an address to write value to i2c device.
 * 		value: an integer to writing byte to i2c device. 
 * Return:
 * 		if an error occured -1 return, otherwise, returned 1.
 * */
int i2c_writeByte(int file,int addr,int value);

/**
 * Writing more than one byte to i2c device.
 * Args: 
 * 		file: i2c_init return value.
 * 		addr: an address to write value to i2c device.
 * 		value: an buffer to send bytes to i2c device. 
 * 		nbytes: takes how many value will send to i2c device.
 * Return:
 * 		if an error occured -1 return, otherwise, returned 1.
 * */
int i2c_writeBytes(int file,int addr,char value[10],int nbytes);

/**
 * Reading a byte from i2c device.
 * Args:
 * 		file: i2c_init return value.
 * 		addr: an address that will read value.
 * Return:
 * 		if an error -1 returned ,otherwise a byte return.
 * */
char i2c_readByte(int file,int addr);

/**
 * Reading DataXN and DataXM values,x,y,z axis. 
 * Args:
 * 		file: i2c_init return value, opened file.
 * 		addr1: The first reading address.
 * 		addr2: The last  reading address.
 * Return:
 * 		if an error occured -1 return, otherwise reading addr1 response and
 * 	addr2 response associated for 16 bit value. 
 * */
int i2c_readByte(int file,int addr1,int addr2);

/**
 * Reading more than one bytes from i2c device.
 * Args:
 * 		file: i2c_init return value. if value is different '-1' file is created.
 * 		addr: i2c register address to read value
 * 		nbytes: how many bytes reading value.
 * Return:
 * 		if a error occurred return NULL, otherwise return char array(char *). 
 * */
char *i2c_readBytes(int file,int addr,int nbytes);

/**
 * Closing i2c file.
 * Args: 
 * 		file: i2c_init return value to close.
 * Return:
 * 		if an error occured -1 return, otherwise 1 shall be returned.
 * */
int i2c_close(int file);

#endif /*__ADXL312_H*/



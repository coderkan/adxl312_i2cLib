#ifndef __ADXL312_IO_H
#define __ADXL312_IO_H


/**
 *
 *
 * */
#define SLAVE_ADDRESS	  0x1D
#define ALT_ADDRESS		  0x53
#define SLAVE_READ		  0x3B
#define SLAVE_WRITE		  0x3A
#define	ALT_READ		    0xA7
#define ALT_WRITE		    0xA6
#define ADXL_ID			    0xE5

/**
 * Register Map
 * */
#define DEVICE_ID    	   0x00
#define OFSX			       0x1E
#define OFSY			       0x1F
#define OFSZ		  	     0x20

#define THRESH_ACT  	   0x24
#define THRESH_INACT  	 0X25
#define TIME_INACT		   0x26
#define ACT_INACT_CTL    0x27
#define BW_RATE			     0x2C
#define POWER_CTL 		   0x2D
#define INT_ENABLE		   0x2E
#define INT_MAP 		     0x2F
#define INT_SOURCE		   0x30
#define DATA_FORMAT		   0x31
#define DATAX0			     0x32
#define DATAX1			     0x33
#define DATAY0			     0x34
#define DATAY1			     0x35
#define DATAZ0			     0x36
#define DATAZ1			     0x37
#define FIFO_CTL		     0x38
#define FIFO_STATUS		   0x39


/**
 * Power Ctl Register values
 * */
#define WAKEUP_8HZ		    0x00
#define WAKEUP_4HZ		    0x01
#define WAKEUP_2HZ		    0x02
#define WAKEUP_1HZ		    0x03
#define SLEEP			        0x04
#define MEASUREMENT		    0x08
#define STANDBY		 	      0x00
#define AUTO_SLEEP		    0x10

/**
 * INT_ENABLE & INT_SOURCE & INT_MAP
 * values
 * */
#define	OVERRUN 		      0x01
#define	WATERMARK		      0x02
#define NA_2			        0x04
#define	INACTIVITY		    0x08
#define	ACTIVITY		      0x10
#define	NA_5			        0x20
#define	NA_6			        0x40
#define	DATAREADY		      0x80

/**
 * DATA_FORMAT	values
 * */
#define	RANGE_1_5G		    0x00
#define	RANGE_3G		      0x01
#define	RANGE_6G		      0x02
#define	RANGE_12G		      0x03
#define DATA_RIGHT		    0x00
#define DATA_LEFT		      0x04
#define TEN_BIT_RES		    0x00
#define	FULL_RES		      0x08
#define	INT_LOW			      0x20
#define	INT_HIGH		      0x00
#define	SPI_3_WIRE		    0x40
#define	SPI_4_WIRE		    0x00
#define SELFTEST_ON		    0x80
#define	SELFTEST_OFF	    0x00

/**
 * FIFO_CTL bit tanımlamaları...
 * */
#define	TRIGGER_INT1		  0x00
#define TRIGGER_INT2		  0x20
#define	FIFO_MODE_BYPASS	0x00
#define	FIFO_RESET			  0x00
#define	FIFO_FIFO_MODE		0x40
#define FIFO_STREAM_MODE	0x80
#define	FIFO_TRIGGER_MODE	0xC0


/**
 * ACT_INACT_CTL
 * */

#define INACT_Z_ENABLE		0x01
#define INACT_Z_DISABLE		0x00
#define INACT_Y_ENABLE		0x02
#define INACT_Y_DISABLE		0x00
#define INACT_X_ENABLE		0x04
#define	INACT_X_DISABLE		0x00
#define INACT_AC			    0x08
#define INACT_DC			    0x00
#define ACT_Z_ENABLE	 	  0x10
#define ACT_Z_DISABLE		  0x00
#define ACT_Y_ENABLE		  0x20
#define ACT_Y_DISABLE		  0x00
#define ACT_X_ENABLE	 	  0x40
#define ACT_X_DISABLE		  0x00
#define ACT_AC				    0x80
#define ACT_DC 				    0x00

/**
 * FIFO_STATUS	Bit declaration
 * */
#define	FIFO_TRIGGERRED		0x80

#endif /* __ADXL312_IO_H */

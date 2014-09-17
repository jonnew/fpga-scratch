#define CDC_DATA_OUT_EP_SIZE	70
#define CDC_DATA_IN_EP_SIZE		70

#define IO_DIRECTION_OUT		0
#define IO_DIRECTION_IN			1


#define   MODE_00       0x00              // Setting for SPI bus Mode 0,0
#define   MODE_01       0x01              // Setting for SPI bus Mode 0,1
#define   MODE_10       0x02              // Setting for SPI bus Mode 1,0
#define   MODE_11       0x03             // Setting for SPI bus Mode 1,1

#define   SPI_FOSC_64   0x02
#define   SMPMID        0x00

typedef enum _SPARTAN_3A_CONFIG_OUT_PACKET_TYPE{
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_OPEN,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_CLOSE,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GETSTRING,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUTSTRING,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GETSTRING_ATADDRESS,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUTSTRING_ATADDRESS,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GET_CHAR,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUT_CHAR,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_SET_IO_DIR,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_SET_IO_VALUE,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GET_IO_VALUE,
	SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GET_ALL_IO_VALUES
}SPARTAN_3A_CONFIG_OUT_PACKET_TYPE, *PTR_SPARTAN_3A_CONFIG_OUT_PACKET_TYPE;

typedef enum _SPARTAN_3A_CONFIG_IO_PIN{
	SPARTAN_3A_CONFIG_IO_PIN_SI,
	SPARTAN_3A_CONFIG_IO_PIN_SO,
	SPARTAN_3A_CONFIG_IO_PIN_CS,
	SPARTAN_3A_CONFIG_IO_PIN_CLK,
	SPARTAN_3A_CONFIG_IO_PIN_PROGB,
	SPARTAN_3A_CONFIG_IO_PIN_DONE,
	SPARTAN_3A_CONFIG_IO_PIN_INITB
}SPARTAN_3A_CONFIG_IO_PIN, *PTR_SPARTAN_3A_CONFIG_IO_PIN;

typedef enum _SPARTAN_3A_CONFIG_IN_PACKET_TYPE{
	SPARTAN_3A_CONFIG_IN_PACKET_STATUS,
	SPARTAN_3A_CONFIG_IN_PACKET_BUFFER
}SPARTAN_3A_CONFIG_IN_PACKET_TYPE, *PTR_SPARTAN_3A_CONFIG_IN_PACKET_TYPE;

typedef enum _SPARTAN_3A_CONFIG_STATUS{
	STATUS_SUCCESS,
	STATUS_FAILURE,
	STATUS_FAIL_PACKET_SIZE_TOO_LARGE,
	STATUS_FAIL_UNEXPECTED_PACKET,
	STATUS_FAIL_INCORRECT_PARAMETER,
	STATUS_FAIL_DEVICE_NOT_READY,
	STATUS_FAIL_READ_ERROR,
	STATUS_FAIL_WRITE_ERROR,
	STATUS_FAIL_UNSUPPORTED_OFFSET,
	STATUS_FAIL_DATA_PACKET_EXPECTED
}SPARTAN_3A_CONFIG_STATUS, *PTR_SPARTAN_3A_CONFIG_STATUS;



typedef union _SPARTAN_3A_CONFIG_OUT_PACKET{
	unsigned char RawData[CDC_DATA_OUT_EP_SIZE];
	
	struct{
		unsigned char Byte0; //~
		unsigned char Byte1; //Packet Type
		unsigned char Byte2;
		unsigned char Byte3;
		unsigned char Byte4;
		unsigned char Byte5;
		unsigned char Data[64];
	}RawPacket;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_OPEN
		unsigned char SpiNum;
		unsigned char SyncMode;
		unsigned char BusMode;
		unsigned char SmpPhase;
	}SpiOpen;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_CLOSE
		unsigned char SpiNum;
	}SPIClose;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GETSTRING
		unsigned char SpiNum;
		unsigned char Length;
	}SPIGetString;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUTSTRING
		unsigned char SpiNum; 
		unsigned char Length;
		unsigned char reserved0;
		unsigned char reserved1;
		unsigned char Data[64];
	}SPIPutString;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GETSTRING_ATADDRESS
		unsigned char SpiNum;
		unsigned char Length;
		unsigned char address[3];
	}SPIGetStringAtAddress;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUTSTRING_ATADDRESS
		unsigned char SpiNum; 
		unsigned char address[3];
		unsigned char Data[64];
	}SPIPutStringAtAddress;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GET_CHAR
		unsigned char SpiNum; 
	}SPIGetChar;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUT_CHAR
		unsigned char SpiNum; 
		unsigned char Data;
	}SPIPutChar;
		
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_SET_IO_DIR
		unsigned char SpiNum; 
		unsigned char Io;
		unsigned char Direction;
	}SetIODir;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_SET_IO_VALUE
		unsigned char SpiNum; 
		unsigned char Io;
		unsigned char Value;
	}SetIOValue;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GET_IO_VALUE
		unsigned char SpiNum; 
		unsigned char Io;
	}GetIOValue;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GET_ALL_IO_VALUES
		unsigned char SpiNum; 
	}GetAllIOValues;
	
}SPARTAN_3A_CONFIG_OUT_PACKET, *PTR_SPARTAN_3A_CONFIG_OUT_PACKET;


typedef union _SPARTAN_3A_CONFIG_IN_PACKET{
	unsigned char RawData[38];
	
	struct{
		unsigned char Byte0; //~
		unsigned char Byte1; //Packet Type
		unsigned char Byte2;
		unsigned char Byte3;
		unsigned char Byte4;
		unsigned char Byte5;
		unsigned char Data[32];
	}RawPacket;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_IN_PACKET_STATUS
		unsigned char SpiNum; 
		unsigned char Status;
		unsigned char ExecutedCmd;
	}Status;
	
	struct{
		unsigned char Tilda; //This has to be ~
		unsigned char PacketType; //SPARTAN_3A_CONFIG_IN_PACKET_BUFFER
		unsigned char SpiNum; 
		unsigned char reserved0;
		unsigned char reserved1;
		unsigned char reserved2;
		unsigned char Data[32];
	}SPIBuffer;
	
}SPARTAN_3A_CONFIG_IN_PACKET, *PTR_SPARTAN_3A_CONFIG_IN_PACKET;

#define DEV_ID_M45PE10VMN6P             0x114020         
#define DEV_ID_ATMEL_AT45DB021D         0x241F      //0x231F
#define DEV_ID_ATMEL_AT45DB161D         0x261F       

#define FLASH_ALGORITHM_M45PE10VMN6P    0x01
#define FLASH_ALGORITHM_ATMEL_DATAFLASH 0x02

//Generic SPI flash commands
#define	SPI_FLASH_READ_ID			    0x9F

//Atmel Dataflash specific
#define	ATMEL_DATAFLASH_READ			0x03
#define	ATMEL_DATAFLASH_READ_STATUS		0xD7
#define	ATMEL_DATAFLASH_BUFFER_WRITE    0x84
#define	ATMEL_DATAFLASH_PAGE_PROGRAM    0x83

//M45PE10VMN6P Specific
#define	M45PE10VMN6P_WRITE_ENABLE		0x06
#define	M45PE10VMN6P_WRITE_DISABLE		0x04
#define	M45PE10VMN6P_READ_ID			0x9F
#define	M45PE10VMN6P_READ_STATUS		0x05
#define	M45PE10VMN6P_READ				0x03
#define	M45PE10VMN6P_FAST_READ			0x0B
#define	M45PE10VMN6P_PAGE_WRITE			0x0A
#define	M45PE10VMN6P_PAGE_PROGRAM		0x02
#define	M45PE10VMN6P_PAGE_ERASE			0xDB
#define	M45PE10VMN6P_SECTOR_ERASE		0xD8
#define	M45PE10VMN6P_DEEP_PWR_DOWN		0xB9
#define	M45PE10VMN6P_REL_DEEP_PWR_DOWN	0xB9




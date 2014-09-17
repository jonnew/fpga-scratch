#include "memory.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include "Antero.hpp"
#include "AnteroConfig.hpp"
#include "Serial.hpp"

#define ERROR_FILE_NOT_FOUND   1
#define ERROR_GEN_FAILURE      2
#define ERROR_INVALID_DATA     3
#define ERROR_FILE_TOO_LARGE   4

Antero::Antero()
{
    DeviceID = 0;
    FlashAlgorithm = FLASH_ALGORITHM_ATMEL_DATAFLASH;
}

LONG Antero::AddLog(const char *strLog)
{
	printf("%s\n", strLog);
	return 0;
}

LONG Antero::OpenPort(const char *devName)
{
	LastError = serial.Open(devName);
	if( LastError != 0)
	{
		if(serial.IsOpen())
		{
			serial.Close();
		}

		AddLog("Unable to open COM port\n");
		return LastError;
	}

	LastError = serial.Setup(19200);
	if( LastError != 0)
	{
		if(serial.IsOpen())
		{
			serial.Close();
		}
		AddLog("Unable to setup COM Port\n");
		return LastError;
	}
    
	return 0;
}


Antero::~Antero()
{
	if(serial.IsOpen())
	{
		serial.Close();
	}
}

LONG Antero::SendAndReceive(unsigned char *SendBuffer, unsigned char SendLen, unsigned char *ReceiveBUffer, unsigned char ReceiveLen)
{
	unsigned char i = 0;
	unsigned char tmpSend = 0;

	if(serial.IsOpen())
	{
		serial.Purge();
		for(i=0;i<SendLen;i+=32)
		{
			if((SendLen - i) > 32)
			{
				tmpSend = 32;
			}
			else
			{
				tmpSend = SendLen - i;
			}

			LastError = serial.Write(SendBuffer+i, tmpSend);

			if(LastError != 0)
			{
				return LastError;
			}
		}

		return serial.Read(ReceiveBUffer, ReceiveLen);
	}
	else
	{
		return ERROR_FILE_NOT_FOUND;
	}
}

LONG Antero::SPIOpen(unsigned char SPINum)
{
	SPARTAN_3A_CONFIG_OUT_PACKET OutPacket;
	SPARTAN_3A_CONFIG_IN_PACKET	InPacket;
	
#ifdef VERBOSE
	AddLog("Starting SPIOpen\n");
#endif

	memset(&OutPacket, 0, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET));
	memset(&InPacket, 0, sizeof(SPARTAN_3A_CONFIG_IN_PACKET));

	OutPacket.SpiOpen.Tilda = '~';
	OutPacket.SpiOpen.PacketType = SPARTAN_3A_CONFIG_OUT_PACKET_SPI_OPEN;
	OutPacket.SpiOpen.SpiNum = 1;
	OutPacket.SpiOpen.BusMode = MODE_00;
	OutPacket.SpiOpen.SyncMode = SPI_FOSC_64;
	OutPacket.SpiOpen.SmpPhase = SMPMID;
	LastError = SendAndReceive((unsigned char*)&OutPacket, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET), (unsigned char*)&InPacket, 5);
	
	if(LastError != 0)
		return LastError;

	if(InPacket.Status.Tilda != '~' || InPacket.Status.PacketType != SPARTAN_3A_CONFIG_IN_PACKET_STATUS || InPacket.Status.Status != STATUS_SUCCESS)
	{
        #ifdef VERBOSE
		AddLog("SPIOpen failed\n");
		#endif
		return ERROR_GEN_FAILURE;
	}
	else
	{
        #ifdef VERBOSE
		AddLog("SPIOpen succeeded\n");
		#endif
		return 0;
	}

}

LONG Antero::SPISetIODirection(unsigned char SPINum, unsigned char Io, unsigned char Direction)
{
	SPARTAN_3A_CONFIG_OUT_PACKET OutPacket;
	SPARTAN_3A_CONFIG_IN_PACKET	InPacket;

#ifdef VERBOSE
	AddLog("SPISetDirection started\n");
#endif

	memset(&OutPacket, 0, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET));
	memset(&InPacket, 0, sizeof(SPARTAN_3A_CONFIG_IN_PACKET));

	OutPacket.SetIODir.Tilda = '~';
	OutPacket.SetIODir.PacketType = SPARTAN_3A_CONFIG_OUT_PACKET_SPI_SET_IO_DIR;
	OutPacket.SetIODir.SpiNum = SPINum;
	OutPacket.SetIODir.Io = Io;
	OutPacket.SetIODir.Direction = Direction;
	LastError = SendAndReceive((unsigned char*)&OutPacket, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET), (unsigned char*)&InPacket, 5);
	
	if(LastError != 0)
		return LastError;

	if(InPacket.Status.Tilda != '~' || InPacket.Status.PacketType != SPARTAN_3A_CONFIG_IN_PACKET_STATUS || InPacket.Status.Status != STATUS_SUCCESS)
	{
        #ifdef VERBOSE
		AddLog("SPISetDirection failed\n");
		#endif
		return ERROR_GEN_FAILURE;
	}
	else
	{
        #ifdef VERBOSE
		AddLog("SPISetDirection succeeded\n");
		#endif
		return 0;
	}
}

LONG Antero::SPISetIOValue(unsigned char SPINum, unsigned char Io, unsigned char Value)
{
	SPARTAN_3A_CONFIG_OUT_PACKET OutPacket;
	SPARTAN_3A_CONFIG_IN_PACKET	InPacket;
#ifdef VERBOSE
	AddLog("SPISetIOValue started\n");
#endif
	memset(&OutPacket, 0, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET));
	memset(&InPacket, 0, sizeof(SPARTAN_3A_CONFIG_IN_PACKET));

	OutPacket.SetIOValue.Tilda = '~';
	OutPacket.SetIOValue.PacketType = SPARTAN_3A_CONFIG_OUT_PACKET_SPI_SET_IO_VALUE;
	OutPacket.SetIOValue.SpiNum = SPINum;
	OutPacket.SetIOValue.Io = Io;
	OutPacket.SetIOValue.Value = Value;
	LastError = SendAndReceive((unsigned char*)&OutPacket, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET), (unsigned char*)&InPacket, 5);
	
	if(LastError != 0)
		return LastError;

	if(InPacket.Status.Tilda != '~' || InPacket.Status.PacketType != SPARTAN_3A_CONFIG_IN_PACKET_STATUS || InPacket.Status.Status != STATUS_SUCCESS)
	{
        #ifdef VERBOSE
		AddLog("SPISetIOValue failed\n");
		#endif
		return ERROR_GEN_FAILURE;
	}
	else
	{
        #ifdef VERBOSE
		AddLog("SPISetIOValue succeeded\n");
		#endif
		return 0;
	}
}

LONG Antero::SPIGetChar(unsigned char SPINum, unsigned char* chr)
{
	SPARTAN_3A_CONFIG_OUT_PACKET OutPacket;
	SPARTAN_3A_CONFIG_IN_PACKET	InPacket;
#ifdef VERBOSE
	AddLog("SPIGetChar started\n");
#endif
	memset(&OutPacket, 0, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET));
	memset(&InPacket, 0, sizeof(SPARTAN_3A_CONFIG_IN_PACKET));

	OutPacket.SPIGetChar.Tilda = '~';
	OutPacket.SPIGetChar.PacketType = SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GET_CHAR;
	OutPacket.SPIGetChar.SpiNum = SPINum;
	LastError = SendAndReceive((unsigned char*)&OutPacket, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET), (unsigned char*)&InPacket, 7);
	
	if(LastError != 0)
		return LastError;

	if(InPacket.SPIBuffer.Tilda != '~' || InPacket.SPIBuffer.PacketType != SPARTAN_3A_CONFIG_IN_PACKET_BUFFER)
	{
        #ifdef VERBOSE
		AddLog("SPIGetChar failed\n");
		#endif
		return ERROR_GEN_FAILURE;
	}
	else
	{
        #ifdef VERBOSE
		AddLog("SPIGetChar succeeded\n");
		#endif
		*chr = InPacket.SPIBuffer.Data[0];
		return 0;
	}
}

LONG Antero::SPIPutChar(unsigned char SPINum, unsigned char chr)
{
	SPARTAN_3A_CONFIG_OUT_PACKET OutPacket;
	SPARTAN_3A_CONFIG_IN_PACKET	InPacket;

#ifdef VERBOSE
	AddLog("SPIPutChar started\n");
#endif
	memset(&OutPacket, 0, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET));
	memset(&InPacket, 0, sizeof(SPARTAN_3A_CONFIG_IN_PACKET));

	OutPacket.SPIPutChar.Tilda = '~';
	OutPacket.SPIPutChar.PacketType = SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUT_CHAR;
	OutPacket.SPIPutChar.SpiNum = SPINum;
	OutPacket.SPIPutChar.Data = chr;
	LastError = SendAndReceive((unsigned char*)&OutPacket, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET), (unsigned char*)&InPacket, 5);
	
	if(LastError != 0)
		return LastError;

	if(InPacket.Status.Tilda != '~' || InPacket.Status.PacketType != SPARTAN_3A_CONFIG_IN_PACKET_STATUS || InPacket.Status.Status != STATUS_SUCCESS)
	{
        #ifdef VERBOSE
		AddLog("SPIPutChar failed\n");
		#endif
		return ERROR_GEN_FAILURE;
	}
	else
	{
        #ifdef VERBOSE
		AddLog("SPIPutChar succeeded\n");
		#endif
		return 0;
	}
}

LONG Antero::SPIGetString(unsigned char SPINum, unsigned char* ptrBuffer, unsigned char len)
{
	SPARTAN_3A_CONFIG_OUT_PACKET OutPacket;
	SPARTAN_3A_CONFIG_IN_PACKET	InPacket;

	//AddLog("SPIGetString started\n");
	memset(&OutPacket, 0, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET));
	memset(&InPacket, 0, sizeof(SPARTAN_3A_CONFIG_IN_PACKET));

	OutPacket.SPIGetString.Tilda = '~';
	OutPacket.SPIGetString.PacketType = SPARTAN_3A_CONFIG_OUT_PACKET_SPI_GETSTRING;
	OutPacket.SPIGetString.SpiNum = SPINum;
	OutPacket.SPIGetString.Length = len;
	LastError = SendAndReceive((unsigned char*)&OutPacket, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET), (unsigned char*)&InPacket, 6+len);
	
	if(LastError != 0)
		return LastError;

	if(InPacket.SPIBuffer.Tilda != '~' || InPacket.SPIBuffer.PacketType != SPARTAN_3A_CONFIG_IN_PACKET_BUFFER)
	{
		//AddLog("SPIGetString failed\n");
		return ERROR_GEN_FAILURE;
	}
	else
	{
		//AddLog("SPIGetString succeeded\n");
		memcpy(ptrBuffer, &InPacket.SPIBuffer.Data[0], len);
		return 0;
	}
}

LONG Antero::SPIPutString(unsigned char SPINum, unsigned char* ptrBuffer, unsigned char len)
{
	SPARTAN_3A_CONFIG_OUT_PACKET OutPacket;
	SPARTAN_3A_CONFIG_IN_PACKET	InPacket;
    #ifdef VERBOSE
	AddLog("SPIPutString started\n");
	#endif
	memset(&OutPacket, 0, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET));
	memset(&InPacket, 0, sizeof(SPARTAN_3A_CONFIG_IN_PACKET));

	OutPacket.SPIPutString.Tilda = '~';
	OutPacket.SPIPutString.PacketType = SPARTAN_3A_CONFIG_OUT_PACKET_SPI_PUTSTRING;
	OutPacket.SPIPutString.SpiNum = SPINum;	
	OutPacket.SPIPutString.Length = len;

	memcpy(&OutPacket.SPIPutString.Data[0], ptrBuffer, len);

	LastError = SendAndReceive((unsigned char*)&OutPacket, sizeof(SPARTAN_3A_CONFIG_OUT_PACKET), (unsigned char*)&InPacket, 5);
	
	if(LastError != 0)
		return LastError;

	if(InPacket.Status.Tilda != '~' || InPacket.Status.PacketType != SPARTAN_3A_CONFIG_IN_PACKET_STATUS || InPacket.Status.Status != STATUS_SUCCESS)
	{
        #ifdef VERBOSE
		AddLog("SPIPutString failed\n");
		#endif
		return ERROR_GEN_FAILURE;
	}
	else
	{
        #ifdef VERBOSE
		AddLog("SPIPutString succeeded\n");
		#endif
		return 0;
	}
}

LONG Antero::SPIAssertCS(unsigned char SPINum)
{
	LONG LastError;
    #ifdef VERBOSE
	AddLog("SPIAssertCS called\n");
	#endif
	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CS, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;

	return Antero::SPISetIOValue(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CS, 0);
}

LONG Antero::SPIDeAssertCS(unsigned char SPINum)
{
	LONG LastError;
    #ifdef VERBOSE
	AddLog("SPIDeAssertCS called\n");
	#endif
	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CS, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;

	return Antero::SPISetIOValue(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CS, 1);
}

LONG Antero::SPIToggleCS(unsigned char SPINum)
{
	LONG LastError;
    #ifdef VERBOSE
	AddLog("SPIToggleCS called\n");
	#endif
	LastError = Antero::SPIDeAssertCS(SPINum);
	if (LastError != 0)
		return LastError;

	return Antero::SPIAssertCS(SPINum);
}

LONG Antero::FlashReadID9Fh(unsigned char SPINum, unsigned char* Buffer, unsigned char Len)
{
	LONG LastError;
	unsigned char tmpBuffer[4];
    #ifdef VERBOSE
	AddLog("FlashReadID9Fh called\n");
	#endif
	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, SPI_FLASH_READ_ID);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIGetString(SPINum, tmpBuffer, 3);
	if (LastError != 0)
		return LastError;

	memcpy(Buffer, tmpBuffer, Len<3?Len:3);

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::LoadFile(const char *FileName, void* Buffer, int Length) {
	FILE *f = fopen(FileName, "rb");
	if (!f) return ERROR_FILE_NOT_FOUND;
	int nr = (int) fread(Buffer, 1, Length, f);
	fclose(f);
	if (nr != Length) return ERROR_INVALID_DATA;
	return 0;
}
	
LONG Antero::ConfigureBoard(unsigned char SPINum, unsigned char* Buffer, int Length)
{
	LONG LastError;
	unsigned char tmpBuffer[20];

    #ifdef VERBOSE
    AddLog("ConfigureBoard called\n");
    #endif
	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_PROGB, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;

	//Pull PROGB Low while Flash is being programmed
	LastError = Antero::SPISetIOValue(SPINum, SPARTAN_3A_CONFIG_IO_PIN_PROGB, 0);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIOpen(SPINum);
	if (LastError != 0)
		return LastError;
		
	// Read Device ID
	FlashReadID9Fh(SPINum, &tmpBuffer[0], 3);
	DeviceID = 0;
	memcpy(&DeviceID, tmpBuffer, 3);
	
	if( DeviceID == DEV_ID_M45PE10VMN6P )
	{
        FlashAlgorithm = FLASH_ALGORITHM_M45PE10VMN6P;
    }
    else if( DeviceID == DEV_ID_ATMEL_AT45DB021D )
    {
        FlashAlgorithm = FLASH_ALGORITHM_ATMEL_DATAFLASH;
        BlockCount = 30;//Actual block count is 127 but we use only less than 100K
        PageSize = 256;
        BlockSize = 2048;
    }
    else if( DeviceID == DEV_ID_ATMEL_AT45DB161D )
    {
        FlashAlgorithm = FLASH_ALGORITHM_ATMEL_DATAFLASH;
        BlockCount = 15; //Actual block count is 512 but we use only less than 100K
        PageSize = 512;
        BlockSize = 4096;
    }
    else
    {
        return ERROR_INVALID_DATA;
    }

    if( FlashAlgorithm == FLASH_ALGORITHM_M45PE10VMN6P )
    {
    	LastError = Antero::M45PE10VMN6PWriteEnable(SPINum);
    	if (LastError != 0)
    		return LastError;
    
    
    	//Erase flash
    	LastError = Antero::M45PE10VMN6PChipErase(SPINum);
    	if (LastError != 0)
    		return LastError;
            
    	LastError = Antero::M45PE10VMN6PWriteEnable(SPINum);
    	if (LastError != 0)
    		return LastError;
    		
    
    	//Program Flash
    	LastError = Antero::M45PE10VMN6PProgramEEPROM(SPINum, Buffer, 0, Length);
    	if (LastError != 0)
    		return LastError;
    }
    
    if( FlashAlgorithm == FLASH_ALGORITHM_ATMEL_DATAFLASH )
    {
        AtmelDataFlashProgramEEPROM(SPINum, Buffer, 0, Length);
    }

	//Set all pins to in puts to avoid interruption during config
/*	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CS, IO_DIRECTION_IN);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_SI, IO_DIRECTION_IN);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_SO, IO_DIRECTION_IN);
	if (LastError != 0)
		return LastError;

	return Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CLK, IO_DIRECTION_IN);*/
	
	return 0;
}

LONG Antero::ReadFlashMemory(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length )
{
    if( FlashAlgorithm == FLASH_ALGORITHM_M45PE10VMN6P )
	{
        return M45PE10VMN6PRead(SPINum, Buffer, Address, Length );
    }
    else if( FlashAlgorithm == FLASH_ALGORITHM_ATMEL_DATAFLASH )
    {
        return AtmelDataFlashRead(SPINum, Buffer, Address, Length );
    }
    else
    {
        return ERROR_INVALID_DATA;
    }
}

//Atmel Dataflash specific

LONG Antero::AtmelDataFlashBlockErase(unsigned char SPINum, __int32 Address )
{
	LONG LastError;
	unsigned char Status;

    #ifdef VERBOSE
	AddLog("AtmelDataFlashPageErase called\n");
    #endif

	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, 0x50);//0x81
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&Address + 2));
	if (LastError != 0)
		return LastError;
		
	LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&Address + 1));
	if (LastError != 0)
		return LastError;
		
	LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&Address ));
	if (LastError != 0)
		return LastError;

	Antero::SPIDeAssertCS(SPINum);

	Status = 0x00;

	while(!(Status & 0x80))
	{
		LastError = Antero::AtmelDataFlashReadStatus(SPINum, &Status);
		if (LastError != 0)
			return LastError;
	}
	
	return 0;
}


LONG Antero::AtmelDataFlashChipErase(unsigned char SPINum)
{
	LONG i, pageAddress;
	
	LONG eraseLength = BlockCount;

	#ifdef VERBOSE
		printf("Erasing Flash\n");
	#endif

    pageAddress = 0;
    
    for(i = 0; i < eraseLength; i++)
    {
        AtmelDataFlashBlockErase(SPINum, pageAddress);
    	pageAddress += BlockSize;
    }

	
	return 0;
}


LONG Antero::AtmelDataFlashSetpageSize(unsigned char SPINum)
{
    unsigned char Status;
    
    LastError = Antero::AtmelDataFlashReadStatus(SPINum, &Status);
    			if (LastError != 0)
    				return LastError;
    if( !(Status & 0x01) )
    {
        // Page size is not 512, change it to 512
    	LastError = Antero::SPIToggleCS(SPINum);
    	if (LastError != 0)
    		return LastError;
    	
    	LastError = Antero::SPIPutChar(SPINum, 0x3D);
    	if (LastError != 0)
    		return LastError; 

    	LastError = Antero::SPIPutChar(SPINum, 0x2A);
    	if (LastError != 0)
    		return LastError;    
             	
    	LastError = Antero::SPIPutChar(SPINum, 0x80);
    	if (LastError != 0)
    		return LastError;  
    		
      	LastError = Antero::SPIPutChar(SPINum, 0xA6);
    	if (LastError != 0)
    		return LastError;  
    		
	   Antero::SPIDeAssertCS(SPINum);   
       
       return ERROR_INVALID_DATA;              	
    }
    else
    {
        return 0;
    }
}

LONG Antero::AtmelDataFlashRead(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length )
{
    
    LONG LastError;
#ifdef VERBOSE
	AddLog("AtmelDataFlashRead called\n");
#endif
	LastError = Antero::SPISetIODirection(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIOValue(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, 0);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CS, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;
	
	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CLK, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_SI, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;


	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, ATMEL_DATAFLASH_READ);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutString(SPINum, (unsigned char*)&Address, 3);
	if (LastError != 0)
		return LastError;
		
	/*LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&Address + 2));
	if (LastError != 0)
		return LastError;
		
	LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&Address + 1));
	if (LastError != 0)
		return LastError;
		
	LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&Address ));
	if (LastError != 0)
		return LastError;*/

	while(Length)
	{
		LastError = Antero::SPIGetString(SPINum, (unsigned char*)Buffer , Length<32?Length:32);
		if (LastError != 0)
			return LastError;

			if(Length > 32)
		{
			Buffer += 32;
			Length = Length - 32;
			
			Address = Address + 32;
		}
		else
		{
			Length = 0;
		}
		
	}

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::AtmelDataFlashReadStatus(unsigned char SPINum, unsigned char* Buffer)
{
	LONG LastError;
#ifdef VERBOSE
	AddLog("AtmelDataFlashReadStatus called\n");
#endif
	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, ATMEL_DATAFLASH_READ_STATUS);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIGetString(SPINum, Buffer, 1);
	if (LastError != 0)
		return LastError;

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::AtmelDataFlashPageWrite(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length )
{
	LONG LastError;

#ifdef VERBOSE
	AddLog("AtmelDataFlashPageProgram called\n");
#endif
	if(DeviceID == DEV_ID_ATMEL_AT45DB021D && Length > 0x100)
	{
		return ERROR_FILE_TOO_LARGE;
	}
	
	if(DeviceID == DEV_ID_ATMEL_AT45DB161D && Length > 0x200)
	{
		return ERROR_FILE_TOO_LARGE;
	}

	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, ATMEL_DATAFLASH_BUFFER_WRITE);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutString(SPINum, (unsigned char*)&Address, 3);
    if (LastError != 0)
	return LastError;


	while(Length)
	{
		LastError = Antero::SPIPutString(SPINum, (unsigned char*)Buffer , Length<64?Length:64);
		if (LastError != 0)
			return LastError;

		if(Length >= 64)
		{
			Buffer += 64;
			Length = Length - 64;
		}
		else
		{
			Length = 0;
		}
	}

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::AtmelDataFlashProgramEEPROM(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length )
{
	LONG LastError;
	LONG ProgramLen = 0;
	LONG PageAddress;
	unsigned char Status = 0x01;
	
#ifdef VERBOSE
	AddLog("AtmelDataFlashProgramEEPROM called\n");
#endif
	
	if( AtmelDataFlashSetpageSize(SPINum) != 0 )
	{
		printf("Please power cycle the board and try reconfiguring"); //QQQ
        return 0;
    }
	
	
	if(DeviceID == DEV_ID_ATMEL_AT45DB021D)
	{
        ProgramLen = 256;
    }
    else if(DeviceID == DEV_ID_ATMEL_AT45DB161D)
    {
        ProgramLen = 512;
    }
    
    //Erase the flash
    AtmelDataFlashChipErase(SPINum);
    
    AddLog("Programming onboard flash..."); //QQQ
    
    
	while(Length)
	{
		#ifdef VERBOSE
			printf("Programming location %X\n", Address);
		#endif
        printf(".");
        //Write data to page
		LastError = Antero::AtmelDataFlashPageWrite(SPINum, &Buffer[Address], 0, ProgramLen);
		if (LastError != 0)
			return LastError;

        //Program page to sector
        LastError = Antero::SPIToggleCS(SPINum);
	    if (LastError != 0)
		return LastError;
		
        LastError = Antero::SPIPutChar(SPINum, ATMEL_DATAFLASH_PAGE_PROGRAM);
	    if (LastError != 0)
		return LastError;

        PageAddress = Address;// >> 6;

		LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&PageAddress + 2));
	    if (LastError != 0)
		  return LastError;
		
	    LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&PageAddress + 1));
	    if (LastError != 0)
		  return LastError;
		
    	LastError = Antero::SPIPutChar(SPINum, *((unsigned char*)&PageAddress ));
	    if (LastError != 0)
		  return LastError;
		
		Antero::SPIDeAssertCS(SPINum);

		Length = Length>ProgramLen?Length-ProgramLen:0;
		Address += ProgramLen;

		Status = 0x00;

		while(!(Status & 0x80))
		{
			LastError = Antero::AtmelDataFlashReadStatus(SPINum, &Status);
			if (LastError != 0)
				return LastError;
		}
	
	}
    printf("\n");
	return 0;
}


//Numonyx M45PE10VMN6P specific

LONG Antero::M45PE10VMN6PWriteEnable(unsigned char SPINum)
{
	LONG LastError;

#ifdef VERBOSE
	AddLog("M45PE10VMN6PWriteEnable called\n");
#endif
	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError =Antero::SPIPutChar(SPINum, M45PE10VMN6P_WRITE_ENABLE);
	if (LastError != 0)
		return LastError;

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::M45PE10VMN6PWriteDisable(unsigned char SPINum)
{
	LONG LastError;

#ifdef VERBOSE
	AddLog("M45PE10VMN6PWriteDisable called\n");
#endif
	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, M45PE10VMN6P_WRITE_DISABLE);
	if (LastError != 0)
		return LastError;

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::M45PE10VMN6PReadID(unsigned char SPINum, unsigned char* Buffer, unsigned char Len)
{
	LONG LastError;
	unsigned char tmpBuffer[4];

#ifdef VERBOSE
	AddLog("M45PE10VMN6PReadID called\n");
#endif
	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, M45PE10VMN6P_READ_ID);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIGetString(SPINum, tmpBuffer, 3);
	if (LastError != 0)
		return LastError;

	memcpy(Buffer, tmpBuffer, Len<3?Len:3);

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::M45PE10VMN6PReadStatus(unsigned char SPINum, unsigned char* Buffer)
{
	LONG LastError;

#ifdef VERBOSE
	AddLog("M45PE10VMN6PReadStatus called\n");
#endif

	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, M45PE10VMN6P_READ_STATUS);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIGetString(SPINum, Buffer, 1);
	if (LastError != 0)
		return LastError;

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::M45PE10VMN6PRead(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length )
{
	LONG LastError;

#ifdef VERBOSE
	AddLog("M45PE10VMN6PRead called\n");
#endif

	LastError = Antero::SPISetIODirection(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIOValue(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, 0);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CS, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;
	
	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_CLK, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPISetIODirection(SPINum, SPARTAN_3A_CONFIG_IO_PIN_SI, IO_DIRECTION_OUT);
	if (LastError != 0)
		return LastError;


	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, M45PE10VMN6P_READ);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutString(SPINum, (unsigned char*)&Address, 3);
	if (LastError != 0)
		return LastError;

	while(Length)
	{
		LastError = Antero::SPIGetString(SPINum, (unsigned char*)Buffer , Length<32?Length:32);
		if (LastError != 0)
			return LastError;

		if(Length > 32)
		{
			Buffer += 32;
			Length = Length - 32;
		}
		else
		{
			Length = 0;
		}
	}

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::M45PE10VMN6PPageProgram(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length )
{
	LONG LastError;

#ifdef VERBOSE
	AddLog("M45PE10VMN6PPageProgram called\n");
#endif

	if(Length > 0x100)
	{
		return ERROR_FILE_TOO_LARGE;
	}

	LastError = Antero::M45PE10VMN6PWriteEnable(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, M45PE10VMN6P_PAGE_PROGRAM);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutString(SPINum, (unsigned char*)&Address, 3);
	if (LastError != 0)
		return LastError;

	while(Length)
	{
		LastError = Antero::SPIPutString(SPINum, (unsigned char*)Buffer , Length<64?Length:64);
		if (LastError != 0)
			return LastError;

		if(Length >= 64)
		{
			Buffer += 64;
			Length = Length - 64;
		}
		else
		{
			Length = 0;
		}
	}

	return Antero::SPIDeAssertCS(SPINum);
}

LONG Antero::M45PE10VMN6PSectorErase(unsigned char SPINum, __int32 Address )
{
	LONG LastError;

#ifdef VERBOSE
	AddLog("M45PE10VMN6PSectorErase called\n");
#endif

	LastError = Antero::M45PE10VMN6PWriteEnable(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIToggleCS(SPINum);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutChar(SPINum, M45PE10VMN6P_SECTOR_ERASE);
	if (LastError != 0)
		return LastError;

	LastError = Antero::SPIPutString(SPINum, (unsigned char*)&Address, 3);
	if (LastError != 0)
		return LastError;

	return Antero::SPIDeAssertCS(SPINum);
}


LONG Antero::M45PE10VMN6PChipErase(unsigned char SPINum)
{
	unsigned char Status = 0x01;
	LONG LastError;

	#ifdef VERBOSE
		printf("Erasing Flash\n");
	#endif

#ifdef VERBOSE
	AddLog("M45PE10VMN6PChipErase called\n");
#endif

	LastError = Antero::M45PE10VMN6PSectorErase(SPINum, 0x00000);
	if (LastError != 0)
		return LastError;

	while(Status & 0x01)
	{
		//Sleep(1000);

		LastError = Antero::M45PE10VMN6PReadStatus(SPINum, &Status);
		if (LastError != 0)
			return LastError;
	}	

	LastError = Antero::M45PE10VMN6PSectorErase(SPINum, 0x10000);
	if (LastError != 0)
		return LastError;

	Status = 0x01;

	while(Status & 0x01)
	{
		LastError = Antero::M45PE10VMN6PReadStatus(SPINum, &Status);
		if (LastError != 0)
			return LastError;
	}	

	return 0;
}

LONG Antero::M45PE10VMN6PProgramEEPROM(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length )
{
	LONG LastError;
	unsigned char Status = 0x01;

#ifdef VERBOSE
	AddLog("M45PE10VMN6PProgramEEPROM called\n");
#endif

	while(Length)
	{
		#ifdef VERBOSE
			printf("Programming location %X\n", Address);
		#endif

		LastError = Antero::M45PE10VMN6PPageProgram(SPINum, Buffer, Address, 0x100);
		if (LastError != 0)
			return LastError;

		Length = Length>0x100?Length-0x100:0;
		Buffer += 0x100;
		Address += 0x100;

		Status = 0x01;

		while(Status & 0x01)
		{
			LastError = Antero::M45PE10VMN6PReadStatus(SPINum, &Status);
			if (LastError != 0)
				return LastError;
		}	
	}

	return 0;
}







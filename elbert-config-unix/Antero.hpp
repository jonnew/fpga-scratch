#include "Serial.hpp"

typedef int LONG;
typedef int __int32;

class Antero{
public:
	CSerial serial;
	LONG LastError;
	LONG DeviceID;
	LONG FlashAlgorithm;
	LONG BlockCount;
	LONG PageSize;
	LONG BlockSize;

	Antero();
	~Antero(void);

	LONG OpenPort(const char *devName);
	LONG SendAndReceive(unsigned char *SendBuffer, unsigned char SendLen, unsigned char *ReceiveBUffer, unsigned char ReceiveLen);
	LONG AddLog(const char *strLog);

	LONG SPIOpen(unsigned char SPINum);
	LONG SPISetIODirection(unsigned char SPINum, unsigned char Io, unsigned char Direction);
	LONG SPISetIOValue(unsigned char SPINum, unsigned char Io, unsigned char Value);
	LONG SPIGetChar(unsigned char SPINum, unsigned char* chr);
	LONG SPIGetString(unsigned char SPINum, unsigned char* ptrBuffer, unsigned char len);
	LONG SPIPutChar(unsigned char SPINum, unsigned char chr);
	LONG SPIPutString(unsigned char SPINum, unsigned char* ptrBuffer, unsigned char len);

	LONG SPIAssertCS(unsigned char SPINum);
	LONG SPIDeAssertCS(unsigned char SPINum);
	LONG SPIToggleCS(unsigned char SPINum);
	
	LONG FlashReadID9Fh(unsigned char SPINum, unsigned char* Buffer, unsigned char Len);
	LONG ReadFlashMemory(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length );

    //Atmel Dataflash specific
    LONG AtmelDataFlashRead(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length );
    LONG AtmelDataFlashReadStatus(unsigned char SPINum, unsigned char* Buffer);
    LONG AtmelDataFlashPageWrite(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length );
    LONG AtmelDataFlashProgramEEPROM(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length );
    LONG AtmelDataFlashSetpageSize(unsigned char SPINum);
    LONG AtmelDataFlashChipErase(unsigned char SPINum);
    LONG AtmelDataFlashBlockErase(unsigned char SPINum, __int32 Address );

	//Numonyx M45PE10VMN6P specific
	LONG M45PE10VMN6PWriteEnable(unsigned char SPINum);
	LONG M45PE10VMN6PWriteDisable(unsigned char SPINum);
	LONG M45PE10VMN6PReadID(unsigned char SPINum, unsigned char* Buffer, unsigned char Len);
	LONG M45PE10VMN6PReadStatus(unsigned char SPINum, unsigned char* Buffer);
	LONG M45PE10VMN6PRead(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length);
	LONG M45PE10VMN6PPageProgram(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length);
	LONG M45PE10VMN6PSectorErase(unsigned char SPINum, __int32 Address );
	LONG M45PE10VMN6PChipErase(unsigned char SPINum);
	LONG M45PE10VMN6PProgramEEPROM(unsigned char SPINum, unsigned char* Buffer, __int32 Address, int Length);

	LONG ConfigureBoard(unsigned char SPINum, unsigned char* Buffer, int Length);
	LONG LoadFile(const char *FileName, void* Buffer, int Length);
};


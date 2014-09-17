#ifndef SERIAL_H
#define SERIAL_H

class CSerial {
	
public:
	
	CSerial();
	~CSerial();
	int  Open(const char *devName);
	int  IsOpen();
	int  Setup(int baud);
	void Close();
	int  Write(unsigned char *buffer, int n);
	int  Read(unsigned char *buffer, int n);
	int  Purge();

private:
	
	int fd;
	
};

#endif

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "Serial.hpp"

#define verbose 0
#define WAIT   10     // microseconds to wait when no data available to read / blocked to write

#define ERR_DEVICE_NOT_FOUND     1
#define ERR_DEVICE_NOT_OPEN      2
#define ERR_DEVICE_ALREADY_OPEN  4
#define ERR_SETUP                5
#define ERR_WRITE                6
#define ERR_READ                 7

CSerial::CSerial() {
	fd = -1;
}

CSerial::~CSerial() {
	if (fd > 0) close(fd);
}

int CSerial::Open(const char *devName) {
    if (fd > 0) return ERR_DEVICE_ALREADY_OPEN;
	fd = open(devName, O_RDWR | O_NONBLOCK);
    if (fd < 0 || !isatty(fd)) return ERR_DEVICE_NOT_FOUND;
	return 0;
}

void CSerial::Close() {
    if (fd > 0) {
        close(fd);
        fd = -1;
    }
}

int CSerial::IsOpen() {
	return fd > 0;
}

int CSerial::Setup(int baud) {
    struct termios t;
    if (fd < 0) return ERR_DEVICE_NOT_OPEN;
    int r = tcgetattr(fd, &t);
    if (r) return ERR_SETUP;
    t.c_iflag = 0;
    t.c_oflag = 0;
    t.c_lflag = 0;
    t.c_cflag = CS8 | CREAD | CLOCAL;
    t.c_cc[VMIN]  = 1;
    t.c_cc[VTIME] = 0;
    r = cfsetspeed(&t, baud);
    if (r) return ERR_SETUP;
    r = tcsetattr(fd, TCSANOW, &t);
    if (r) return ERR_SETUP;
	return 0;
}

int CSerial::Write(unsigned char *buffer, int n) {
    if (fd < 0) return ERR_DEVICE_NOT_OPEN;
    while (n > 0) {
        int nw = (int) write(fd, buffer, n);
        if (nw < 0) {
            if (errno == EAGAIN) {
                nw = 0;
                usleep(WAIT);
            } else {
                return ERR_WRITE;
            }
        }
        n -= nw;
        buffer += nw;
        if (verbose) printf("wrote %d\n", nw);
    }
    int r = tcdrain(fd);
    if (r < 0) return ERR_WRITE;
	return 0;
}

int CSerial::Read(unsigned char *buffer, int n) {
    if (fd < 0) return ERR_DEVICE_NOT_OPEN;
    while (n > 0) {
        int nr = (int) read(fd, buffer, n);
        if (nr < 0) {
            if (errno == EAGAIN) {
                nr = 0;
                usleep(WAIT);
            } else {
                return ERR_READ;
            }
        }
        n -= nr;
        buffer += nr;
        if (verbose) printf("read %d\n", nr);
    }
    return 0;
}

int CSerial::Purge() {
    if (fd < 0) return ERR_DEVICE_NOT_OPEN;
    tcflush(fd, TCIFLUSH);
    return 0;
}


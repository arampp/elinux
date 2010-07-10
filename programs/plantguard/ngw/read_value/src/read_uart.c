#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <stdio.h> /* only for printf */
#include <errno.h>
#include <unistd.h>

#define BAUDRATE B9600
#define DEVICE "/dev/ttyS2"
#define LOGNAME "read_value"

int
main (int argc, char** argv) {

  int fd;
  fd = open(DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd <0) {perror(DEVICE); return -1; }


  struct termios newtio;

  //  newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
  newtio.c_cflag = BAUDRATE | CS8 |CREAD | CLOCAL;

  //newtio.c_iflag = IGNPAR | ICRNL;
  newtio.c_iflag = ICRNL|BRKINT|IXON;
  
  //  newtio.c_oflag = OPOST;
  newtio.c_oflag = ONLCR;
  
  //  newtio.c_lflag = ICANON;
  newtio.c_lflag = ISIG|ICANON|ECHO|IEXTEN;

  newtio.c_cc[VMIN]  = 1;
  newtio.c_cc[VTIME] = 0;


  tcflush(fd, TCIFLUSH);
  tcsetattr(fd,TCSANOW,&newtio);
  sleep(1);

  char buf[255];
  while (1) {
    int res = read(fd, buf, 255);
    if (res == -1) {
      if (errno == EAGAIN) {
        /* there is no data so do nothing */
      }
      else {
        perror("read");
      }
    }
    else {
      printf("%d", res);
      buf[res] = 0;
      printf(buf);
    }
    //    sleep(1);
  }


  return 0;
}

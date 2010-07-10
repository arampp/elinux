/*
 * This programm reads a value via usart and prints the answer to the console
 */

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

void
init_usart (int fd) {

  syslog(LOG_DEBUG, "entering init_usart(%d)", fd);

  struct termios newtio;

  /* 
  BAUDRATE: Set bps rate. You could also use cfsetispeed and 
            cfsetospeed.
  CRTSCTS : output hardware flow control (only used if the
            cable has all necessary lines. See sect. 7 of 
            Serial-HOWTO)
  CS8     : 8n1 (8bit,no parity,1 stopbit)
  CLOCAL  : local connection, no modem contol
  CREAD   : enable receiving characters
  */
  //  newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
  newtio.c_cflag = BAUDRATE | CS8;
  
  /*
  IGNPAR  : ignore bytes with parity errors
  ICRNL   : map CR to NL (otherwise a CR input on the other
            computer will not terminate input) otherwise make 
            device raw (no other input processing)
  */
  //newtio.c_iflag = IGNPAR | ICRNL;
  newtio.c_iflag = IGNPAR|ICRNL|BRKINT|IXON;
  
  /*
  Raw output.
  */
  //  newtio.c_oflag = OPOST;
  newtio.c_oflag = ONLCR;
  
  /*
  ICANON  : enable canonical input
  disable all echo functionality, and don't send signals to
  calling program
  */
  //  newtio.c_lflag = ICANON;
  newtio.c_lflag = ISIG|ICANON|ECHO|IEXTEN;

  newtio.c_cc[VMIN]  = 1;
  newtio.c_cc[VTIME] = 0;


  tcflush(fd, TCIFLUSH);
  tcsetattr(fd,TCSANOW,&newtio);

  syslog(LOG_DEBUG, "returning from init_uart(%d)", fd);
}

void
read_uart(int fd) {
  syslog(LOG_DEBUG, "entering read_uart(%d)", fd);
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
}

int
main (int argc, char** argv) {
  
  openlog(LOGNAME, LOG_PERROR, LOG_LOCAL0);

  int fd;
  fd = open(DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd <0) {perror(DEVICE); return -1; }
  syslog(LOG_DEBUG, "opened %s, got fd %d", DEVICE, fd);

  init_usart(fd);

  syslog(LOG_DEBUG, "writing to uart.");
  int bytes = write(fd, "A", 1);
  syslog(LOG_DEBUG, "wrote %d bytes to uart", bytes);
  if (tcdrain(fd) != 0) {
    syslog(LOG_ERR, "tcdrain failed");
  }

  read_uart(fd);

  close(fd);
  return 0;
}


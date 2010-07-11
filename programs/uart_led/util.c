#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <strings.h>
#include "util.h"


int
setup_uart (int fd) {

  struct termios term_attr;

  if( tcgetattr( fd, &term_attr ) == 0 ) {

    /* clear the old settings */
    //bzero( &term_attr, sizeof( term_attr ) );

    /* 
       BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
       CRTSCTS : output hardware flow control (only used if the cable has
       all necessary lines. See sect. 7 of Serial-HOWTO)
       CS8     : 8n1 (8bit,no parity,1 stopbit)
       CLOCAL  : local connection, no modem contol
       CREAD   : enable receiving characters
    */
    term_attr.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

    /*
      IGNPAR  : ignore bytes with parity errors
      ICRNL   : map CR to NL (otherwise a CR input on the other computer
      will not terminate input)
      otherwise make device raw (no other input processing)
    */
    term_attr.c_iflag = IGNPAR | ICRNL;
         
    /*
      Raw output.
    */
    term_attr.c_oflag = 0;
         
    /*
      ICANON  : enable canonical input
      disable all echo functionality, and don't send signals to calling program
    */
    term_attr.c_lflag = ICANON;

    /* 
       now clean the modem line and activate the settings for the port
    */
    tcflush( fd, TCIFLUSH );
    tcsetattr( fd, TCSANOW, &term_attr );


    term_attr.c_cflag = BAUDRATE;
    tcsetattr( fd, BAUDRATE, &term_attr );

    /* 
       now clean the modem line and activate the settings for the port
    */
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&term_attr);

    return 0;
  }
  else {
    return 1;
  }
}

#define BAUDRATE B115200


/*
  Sets up the UART device.

  @param fd: A file descriptor pointing to the serial device.
  
  @return: 0 if the setup worked fine.
           1 if there was an error.
*/
int
setup_uart (int fd);

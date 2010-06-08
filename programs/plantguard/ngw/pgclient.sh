#!/bin/sh
#
# This shell script implements the following workflow:
# 1. Fetch resistor value from AVR micro controller
# 2. Calculate moisture percentage
# 3. Push data to the web application using a HTTP GET request

#-------------------------------------------------------------------------------
# CONFIGURATION
#-------------------------------------------------------------------------------
# URL the web application is hosted.
URL=http://localhost:8000

# Password to store date in the web app
PASSWORD=Streng5632Geheim

# The log facility, syslog should log messages from this script
# see manpage logger(1) for details
LOG_FACILITY=local0

# DEBUG mode. If set to one, there will be no interaction with external systems.
DEBUG=1

#-------------------------------------------------------------------------------
# CODE
# Do not edit unless you know what you're doing.
#-------------------------------------------------------------------------------

#####################################################
# 1. Fetch resistor value from AVR micro controller #
#####################################################
# Currently this is a dummy due to the lack of the hardware
raw_data=$RANDOM    

####################################
# 2. Calculate moisture percentage #
####################################
# Currently this is a dummy due to the lack of the hardware specifications
value=$( expr $raw_data % 100 )

################################################################
# 3. Push data to the web application using a HTTP GET request #
################################################################
curl_url=${URL}/store/${value}/${PASSWORD}

if [ $DEBUG -eq 1 ]; then
    echo EXECUTING: curl $curl_url
    curl_result=0
else
    curl ${URL}/store/${value}/${PASSWORD}
    curl_result=$?
fi

if [ $curl_result -ne 0 ]; then
    logger -p ${LOG_FACILITY}.err Curl returned $curl_result -t $(basename $0)
    exit 1
fi

exit 0
#!/bin/sh
#
# This shell script implements the following workflow:
# 1. Fetch resistor value from AVR micro controller
# 2. Calculate moisture percentage
# 3. Push data to the web application using a HTTP GET request

CONFIGFILE=/etc/pg_config
. $CONFIGFILE
LOGGER="logger -s -p ${LOG_FACILITY}"

#####################################################
# 1. Fetch resistor value from AVR micro controller #
#####################################################

# in debug mode we will use random values
if [ $DEBUG -eq 1 ]; then
    raw_value=$RANDOM
else
    raw_value=$(read_value)
    if [ $? -ne 0 ]; then
        echo "Error reading raw value"
        exit 1
    fi
fi
${LOGGER}.notice Got raw_value: $raw_value

####################################
# 2. Calculate moisture percentage #
####################################
# this is just a dummy expression
value=$( expr $raw_value % 100 )
${LOGGER}.notice Calculated value:  $value

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
    ${LOGGER}.err Curl returned $curl_result -t $(basename $0)
    exit 1
fi

exit 0
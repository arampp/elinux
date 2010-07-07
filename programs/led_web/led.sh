#!/bin/bash

FILE_A=/sys/class/leds/a/brightness
FILE_B=/sys/class/leds/b/brightness


message="default"
if [ ${QUERY_STRING} = "A" ]; then
    message="A"
    br=$(cat $FILE_A)
    if [ $br -ne 0 ]; then
        echo 0 > $FILE_A
        message="null"
    else
        echo 1 > $FILE_A
        message="eins"
    fi
elif [ ${QUERY_STRING} = "B" ]; then
    br=$(cat $FILE_B)
    if [ $br -ne 0 ]; then
        echo 0 > $FILE_B
    else
        echo 1 > $FILE_B
    fi
fi

echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"
       \"http://www.w3.org/TR/html4/loose.dtd\">
       <html>
       <head>
       <title>Beschreibung der Seite</title>
       </head>
       <body>
         <a href=\"/cgi-bin/test.sh?A\">Led A</a><br />
         <a href=\"/cgi-bin/test.sh?B\">Led B</a><br />
       </body>
       </html>
       
"

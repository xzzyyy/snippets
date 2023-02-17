#!/bin/sh
progstr=$1
progpid_cmd="pgrep -f CATCH_ME"
while
    pid=$($progpid_cmd)
    [ "$pid" = "" ]
do:
done
gdb -p $pid

#!/bin/bash

i=0
for param in $@; do
    ((i++))
    echo "param: $i, value: ${!i}"
done
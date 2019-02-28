#!/bin/bash

line=$(gcov -f -b -c $1 | grep -n $2 | cut -f 1 -d :)
((line+=3))
gcov -f -b -c $1 | head -n $(echo $line) | tail -n 4
echo
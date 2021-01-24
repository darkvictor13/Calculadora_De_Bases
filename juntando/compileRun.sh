#!/bin/sh

gcc -g -c baseX.c && gcc -g -c main.c && gcc -o main main.o baseX.o
exit 0

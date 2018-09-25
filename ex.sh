#!/bin/bash

printf "starting flex\n***\n"
flex first.l
printf "\n\nstarting g++\n***\n"
g++ lex.yy.cc
printf "\n\nrunning\n***\n"
./a.out
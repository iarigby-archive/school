#!/bin/bash

printf "\n\n| starting flex\n|*************\n| flex first.l\n"
flex first.l
printf "\n\n| starting g++\n|************\n| g++ lex.yy.cc\n"
g++ lex.yy.cc
printf "\n\n| running\n|*******\n| ./a.out\n"
./a.out
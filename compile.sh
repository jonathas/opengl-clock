#!/bin/bash

echo "Entre com o nome do arquivo"
read archname

#ArchLinux
#g++ -Wall -lGLU -o $archname $archname.cpp -lglut

#Fedora
g++ -L/usr/lib -o $archname $archname.cpp -lglut -lGL -lGLU

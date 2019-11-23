#!/bin/bash

mkdir ./build

cd ./build

cmake ..

if [ $? -eq 0 ]; then
    make
fi

if [ $? -eq 0 ]; then
    make test
fi

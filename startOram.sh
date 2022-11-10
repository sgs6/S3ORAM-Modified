#!/bin/bash

if [ -d "./logs" ]
then
    echo "Logs directory exists. Doing nothing."
else
    echo "Logs directory dosnt exist, making one."
    mkdir ./logs/
fi

echo -n "" > ./logs/$1.log

cd ./Debug
./S3ORAM | tee ../logs/$1.log

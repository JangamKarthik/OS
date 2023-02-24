#!/bin/bash

# Prompt the user to enter the file name to check
echo  "Enter the name of the file to check: "
read  filename

# Check if the file exists
if [ ! -e "$filename" ]; then
#-e checks if the file exists or not
    echo "$filename does not exist"
    exit 1
fi

# Check if the file is a directory or a regular file
if [ -d "$filename" ]; then
    echo "$filename is a directory"
elif [ -f "$filename" ]; then
    echo "$filename is a regular file"
else
    echo "$filename is not a valid file or directory"
    exit 1
fi

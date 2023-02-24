#!/bin/bash

# Ask user for input file name
echo "Enter the name of the file you want to duplicate: "
read input_file

# Ask user for output file name
echo "Enter the name of the duplicate file: "
read output_file

# Use cp command to make a copy of the input file with the name of output file
cp $input_file $output_file

# Check if the copy was successful by using the exit status of cp command
if [ $? -eq 0 ]
then
    echo "Duplicate created successfully!"
else
    echo "Error creating duplicate."
fi

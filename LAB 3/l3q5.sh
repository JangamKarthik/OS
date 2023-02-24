#!/bin/bash

# This script copies all files with a certain file extension from the current directory to a new directory

# Read the file extension from the user
echo "Enter file extension:"
read ext

# Read the directory name to copy the files to
echo "Enter destination directory name:"
read dir

# Create the destination directory if it doesn't exist
if [ ! -d "$dir" ]
then
    mkdir "$dir"
fi

# Loop through all files in the current directory
for file in *
do
    # Check if the file has the given extension
    if [ "${file##*.}" = "$ext" ]
    then
        # Copy the file to the destination directory
        cp "$file" "$dir"
    fi
done

# Print a message to the user indicating that the operation is complete
echo "All files with extension .$ext have been copied to $dir"

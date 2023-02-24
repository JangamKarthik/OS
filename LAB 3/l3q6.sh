#!/bin/bash

# loop through all the files in the current directory
for file in *
do
  # check if the file is a regular file
  if [ -f "$file" ]
  then
    # use sed to replace all occurrences of "ex:" at the beginning of the line or after a period (.)
    # with "Example:"
    sed -i -r 's/(^|\.)ex:/\1Example:/g' "$file"
  fi
done

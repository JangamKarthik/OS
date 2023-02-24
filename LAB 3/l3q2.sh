#!/bin/bash

# Ask user for directory name and pattern to search for
read -p "Enter directory name: " dirname
read -p "Enter pattern to search for: " pattern

# Check if directory exists
if [ ! -d "$dirname" ]; then
  echo "Directory does not exist."
  exit 1
fi

# Change to the directory specified by the user
cd "$dirname" || exit 1

# List all files that contain the specified pattern
grep -l "$pattern" * | sed 's/^.*\///'


#!/bin/bash

# Check if there are any command line arguments
if [ $# -eq 0 ]; then
  echo "Usage: $0 file1 file2 file3 ..."
  exit 1
fi

# Loop through each argument provided
for file in "$@"
do
  # Check if the file exists
  if [ -f "$file" ]; then
    # Ask the user if they want to delete the file
    read -p "Do you want to delete $file? (y/n) " answer

    # If the user types 'y' or 'Y', delete the file
    if [ "$answer" == "y" ] || [ "$answer" == "Y" ]; then
      rm "$file"
      echo "File $file deleted successfully"
    else
      echo "File $file not deleted"
    fi
  else
    echo "Error: $file does not exist"
  fi
done

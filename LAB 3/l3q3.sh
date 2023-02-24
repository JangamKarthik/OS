#!/bin/bash

# This script replaces all files with a .txt extension in the current directory and all its subdirectories with a .text extension.

# Find all files with a .txt extension recursively in the current directory and its subdirectories
files=$(find . -type f -name "*.txt")

# Loop through each file
for file in $files; do
    # Get the filename without the path or extension
    filename=$(basename "$file" .txt)

    # Get the directory path
    dir=$(dirname "$file")

    # Rename the file by adding the .text extension
    mv "$file" "$dir/$filename.text"
done

echo "All files with .txt extension in the current directory and its subdirectories have been renamed to .text."

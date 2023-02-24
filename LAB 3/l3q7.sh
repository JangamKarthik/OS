#!/bin/bash

# Ask user for input file name
echo "Enter the input file name: "
read input_file

# Ask user for output file name
echo "Enter the output file name: "
read output_file

# Use sed to delete all even numbered lines and save output to the output file
sed 'n;d' $input_file > $output_file

# Display success message
echo "Even numbered lines deleted successfully!"

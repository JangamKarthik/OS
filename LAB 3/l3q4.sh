#!/bin/bash

# This script calculates the gross salary, given the basic salary and the travel allowance (TA)

# Read the basic salary from the user
echo "Enter basic salary:"
read basic

# Read the travel allowance (TA) from the user
echo "Enter travel allowance (TA):"
read ta

# Calculate the gross salary using floating point arithmetic
gs=$(echo "$basic + $ta + ($basic * 0.1)" | bc)

# Print the result to the console
echo "Gross salary: $gs"

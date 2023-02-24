#!/bin/bash

# Define a function to sort the strings
sort_strings() {
    # Store the arguments in an array
    strings=("$@")
    # Sort the array using the sort command
    sorted=($(printf '%s\0' "${strings[@]}" | sort -z | tr '\0' '\n'))
    # Print the sorted array
    printf '%s\n' "${sorted[@]}"
}

# Call the sort_strings function with the command line arguments
sort_strings "$@"

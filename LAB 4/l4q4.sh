#!/bin/bash

# Define a usage function to show how to use the script
function usage {
  echo "Usage: $0 [-l | -w | -c] file"
  echo "  -l: Count the number of lines"
  echo "  -w: Count the number of words"
  echo "  -c: Count the number of characters"
  exit 1
}

# Check if the correct number of arguments are given
if [ $# -lt 2 ]; then
  usage
fi

# Parse the command line arguments
while getopts "lw:c:" opt; do
  case ${opt} in
    l) # Count the number of lines
      wc -l ${2}
      ;;
    w) # Count the number of words
      wc -w ${2}
      ;;
    c) # Count the number of characters
      wc -m ${2}
      ;;
    *) # Invalid option
      usage
      ;;
  esac
done

#!/bin/bash

# Function to search for pattern in file
search_pattern() {
  grep "$1" "$2"
}

# Function to delete all occurrences of pattern in file
delete_pattern() {
  sed -i "s/$1//g" "$2"
}

# Loop to display menu until user chooses to exit
while true; do
  # Display menu options
  echo "Enter the number corresponding to the operation you want to perform:"
  echo "1. Search patterns in file"
  echo "2. Delete patterns from file"
  echo "3. Exit"
  
  # Read user's choice
  read choice
  
  # Perform action based on user's choice
  case $choice in
    1) # User wants to search for patterns in file
       # Read file name from user
       echo "Enter the file name:"
       read file
       
       # Loop through all patterns provided as command line arguments
       for pattern in "${@:2}"; do
         # Call search_pattern function to search for pattern in file and display output
         echo "Lines containing \"$pattern\":"
         search_pattern "$pattern" "$file"
         echo ""
       done
       ;;
    2) # User wants to delete patterns from file
       # Read file name from user
       echo "Enter the file name:"
       read file
       
       # Loop through all patterns provided as command line arguments
       for pattern in "${@:2}"; do
         # Call delete_pattern function to delete pattern from file
         delete_pattern "$pattern" "$file"
       done
       echo "Patterns deleted from file."
       ;;
    3) # User wants to exit
       exit
       ;;
    *) # User entered an invalid choice
       echo "Invalid choice. Please enter a valid choice."
       ;;
  esac
done

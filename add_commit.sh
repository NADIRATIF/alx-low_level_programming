
#!/bin/bash

# Get the directory path and commit message from command line arguments
directory=$1
message=$2

# Change to the specified directory
cd $directory

# Add all changes to the Git repository
git add .

# Commit the changes with the specified message
git commit -m "$message"

# push chages
git push

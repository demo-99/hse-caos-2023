#!/bin/bash

name="Alice";

# $# - amount of arguments
# lt less than
if [ $# -lt 2 ]; then
    echo "wrong amount of arguments"
    exit 1
fi

for arg in "$@"; do
    echo $arg
done

# This is a comment
echo "Hello world!"
echo $name

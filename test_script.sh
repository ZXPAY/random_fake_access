#!/bin/bash
# Filename: test_script.sh
# Evaluate the execution file return value

eval "./build/test/test_float_integer"

# $?: previous execution exit code
if [ $? -eq 0 ];
then
    echo "$CMD executed successfully"
else
    echo "$CMD terminated unsuccessfully"
fi


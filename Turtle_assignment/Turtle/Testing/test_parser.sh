#!/bin/bash

# Run the makefile (assumes 'make' both compiles and runs the tests)
make run

# Capture the exit status
exit_status=$?

# Check if the exit status is greater than 0
if [ $exit_status -ne 0 ]; then
    echo "Error: One or more tests failed with status $exit_status"
else
    echo "Success: All tests executed without errors"
fi

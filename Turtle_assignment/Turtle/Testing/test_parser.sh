#!/bin/bash

cd ..
make interp_s

exit_status=$?

if [ $exit_status -ne 0 ]; then
    echo "Error: One or more tests failed with status $exit_status"
else
    echo "Success: All tests executed without errors"
fi

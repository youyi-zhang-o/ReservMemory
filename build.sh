#!/bin/bash

set -e
cmake -S . -B temp
cmake --build temp -j64
./temp/test/test_exe
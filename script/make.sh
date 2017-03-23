#!/bin/bash

set -e
set -u

realpath=$(realpath "${BASH_SOURCE[0]}")
script_directory=$(dirname "${realpath}")
script_directory=$(cd "${script_directory}" && pwd)
build_directory="${script_directory}/../build"

# Build
cd "$build_directory"
cmake ..
make


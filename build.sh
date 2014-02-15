#!/bin/sh

BUILD_DIR="build"
SRC_DIR="$( cd "$( dirname "$0" )" && pwd )"
BUILD_TYPE=Release
ENABLE_TESTS=ON

set +x

mkdir -p $BUILD_DIR && \
cd $BUILD_DIR

echo "Running in $SRC_DIR :"
cmake $SRC_DIR

make
#Disabling ctest for now, as the test are not build by default
#The reason is that if tinythreadpp is included as dependency, the tests are not needed.
#ctest

 

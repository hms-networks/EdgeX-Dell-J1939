#!/bin/sh
set -e -x

# Dependencies
if [ ! -d deps ]
then
  mkdir deps

# get c-sdk from edgexfoundry
  cd  deps
  wget https://github.com/edgexfoundry/device-sdk-c/archive/0.7.1.tar.gz
  tar -xzf 0.7.1.tar.gz
  cd device-sdk-c-0.7.1
  ./scripts/build.sh
  cp -rf include/* /usr/include/
  cp build/release/c/libcsdk.so /usr/lib/
  cd ../..
  rm -rf deps
fi

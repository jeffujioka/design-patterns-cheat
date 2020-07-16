#!/usr/bin/env bash

BOOST_VERSION=1.73.0
BOOST_VER_PATH=boost_1_73_0
BOOST_URL=https://dl.bintray.com/boostorg/release/$BOOST_VERSION/source/$BOOST_VER_PATH.tar.bz2

pushd . > /dev/null 2>&1

mkdir -p 3rd-party && cd 3rd-party

if [ -d $BOOST_VER_PATH ]; then
  echo "Boost is already installed!"
else
  wget $BOOST_URL
  echo "Extracting $BOOST_VER_PATH.tar.bz2..."
  tar xf $BOOST_VER_PATH.tar.bz2
  rm $BOOST_VER_PATH.tar.bz2
fi

popd > /dev/null 2>&1
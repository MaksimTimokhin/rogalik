#!/bin/env/sh

set -e -x

apt-get update

apt-get install -y \
        make \
        cmake \
        clang-12 \
        libncurses5-dev \
        libncursesw5-dev \
        kitty \
        xterm
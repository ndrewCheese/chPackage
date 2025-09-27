#!/bin/bash

g++ main.cpp installUtils.h -o chPkg `pkg-config --libs --cflags gtkmm-3.0`
echo "Done. If you want to open chPkg anywhere, make sure it is in your PATH"



#!/bin/bash
[[ -d build ]] || mkdir build
/usr/bin/clang++ -g -std=c++17 -Wall -Werror -I. -o build/view  view.cpp qdbmp.cpp color.cpp light.cpp triangle.cpp sphere.cpp -lgmock -lgtest -lgtest_main -lpthread

#!/bin/bash

g++ gen.cpp -o gen -O2
g++ std.cpp -o std -O2
g++ d.cpp -o d -O2
while true; do
    ./gen > data.in
    ./std < data.in > std.out
    ./d < data.in > d.out
    if diff std.out d.out; then
        printf "AC\n"
    else
        printf "Wa\n"
        exit 0
    fi
done
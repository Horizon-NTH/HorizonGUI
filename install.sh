#!/bin/bash

erase=false
for arg in "$@"
do
    case $arg in
        -e|--erase)
        erase=true
        ;;
    esac
done

if [ -d "build" ]
then
    rm -rf build
fi
mkdir build
cmake -S . -B build
cmake --build build
echo "Build completed."
if [ "$erase" = true ]
then
	rm -rf build
	echo "Build files erased."
fi

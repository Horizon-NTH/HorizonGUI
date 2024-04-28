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
cd build
cmake ..
cmake --build .
echo "Build completed."
cd ..
if [ "$erase" = true ]
then
	rm -rf build
	echo "Build files erased."
fi

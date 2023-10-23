#!/bin/bash

type=OFF
erase=false
while getops ":d:s:-:" opt;
do
	case $opt in
		d)
			type=OFF
			;;
		s)
			type=ON
			;;
		e)
			erase=true
			;;
		-)
			case "$OPTARG" in
				dynamic)
					type=OFF
					;;
				static)
					type=ONN
					;;
				erase)
					erase=true
					;;
				*)
					echo "Invalid option: --$OPTARG" >&2
					;;
			esac
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			;;
	esac	
done

mkdir build
cd build
cmake .. -DAPI_TYPE=$type
cmake --build .
cd ..
if [ "$erase" ]
then
	rm -rf build
fi

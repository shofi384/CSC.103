#!/bin/bash

echo "@" > output
# test the character version:
for f in tdata/char* ; do
	./main < $f >> output
	echo "@" >> output
done
# test the integer version:
for f in tdata/int* ; do
	./main --int < $f >> output
	echo "@" >> output
done

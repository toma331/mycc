#! /bin/sh

make
make run 
gcc ./build/out.o -o result

echo "RESULT IS: "

./result

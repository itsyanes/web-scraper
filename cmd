docker run --rm -v ${PWD}:/dev/test -w  /dev/test gcc:9.2 gcc main.c -o main
docker run --rm -v ${PWD}:/dev/test -w /dev/test debian:10.1 ./main
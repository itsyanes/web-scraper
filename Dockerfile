FROM debian:10.1
WORKDIR /dev/test
RUN apt update && apt install -y libcurl4-openssl-dev valgrind
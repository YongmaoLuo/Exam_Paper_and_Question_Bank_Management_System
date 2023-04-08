FROM ubuntu:bionic AS build

RUN add-apt-repository ppa:ubuntu-toolchain-r/test

RUN apt-get update && \
	apt-get install -y build-essential git g++-10 cmake autoconf libtool pkg-config

WORKDIR /home/mh4116/CPlusPlus_General_Management_System/Back-end

RUN git clone https://github.com/fmtlib/fmt.git
RUN git clone https://github.com/nlohmann/json.git
RUN git clone https://github.com/rindeal/SQLite3-Encryption.git

COPY CMakeLists.txt server_unencrypted.cpp ./
RUN cmake . && make

FROM ubuntu:bionic
WORKDIR bin
CMD ["./cplusplusproject2022fall"]
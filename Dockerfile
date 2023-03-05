FROM ubuntu:bionic AS build

RUN add-apt-repository ppa:ubuntu-toolchain-r/test

RUN apt-get update && \
	apt-get install -y build-essential git g++-10 cmake autoconf libtool pkg-config

WORKDIR /Back-end

RUN git clone https://github.com/fmtlib/fmt
RUN git clone https://github.com/nlohmann/json
RUN git clone https://github.com/SRombauts/SQLiteCpp/tree/master/sqlite3

COPY CMakeLists.txt server_unencrypted.cpp ./
RUN cmake . && make

FROM ubuntu:bionic
WORKDIR /bin
CMD ["./cplusplusproject2022fall"]
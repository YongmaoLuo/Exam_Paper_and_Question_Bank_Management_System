FROM ubuntu:bionic AS build

RUN apt-get update && apt install -y build-essential manpages-dev software-properties-common ca-certificates

RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN wget -no-check-certificate -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 42D5A192B819C5DA
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'

RUN apt-get update && \
	apt-get install -y git gcc-11 g++-11 cmake autoconf libtool pkg-config libssl-dev libsqlite3-dev

WORKDIR /root/CPlusPlus_General_Management_System/Back-end/
COPY ./Back-end .
RUN cd Back-end/

RUN rm -rf fmt/ && git clone https://github.com/fmtlib/fmt.git
RUN rm -rf glaze/ && git clone https://github.com/stephenberry/glaze.git
RUN rm -rf SQLite3-Encryption/ && git clone https://github.com/rindeal/SQLite3-Encryption.git

RUN mkdir build && cd build && cmake .. 
RUN make
EXPOSE 9999

FROM ubuntu:bionic
WORKDIR bin
ENTRYPOINT ["./cplusplusproject2022fall"]
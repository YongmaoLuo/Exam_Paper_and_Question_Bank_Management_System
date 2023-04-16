## Introduction

We developed a complicated full stack application with socket-based single-server-multi-client connection. The front-end of this application is window-based Qt6 and back-end is SQLite3/MongoDB(experimental). Serveral highlights of this application are:

* Modern **C++20**
* Multiplexing with epoll (unix-based system only) to achieve pseudo-concurrency
* Multi-threading & vectorization
* A variety of database selection
* API for user customization



## Goal & Vision

The aim of this full-stack application is to provide a smooth and robust (high scalability & low latency) user experience while maintaining low memory occupation at the same time. We leveraged unix-domain socket(We don't wish to use asio at this stage as we don't want to have boost library involved.) and epoll connection to achieve faster pseudo-concurrency and lots of move(forward) operations to avoid unnecessary copy and reduce memory cost. We applied vectorization to process messages faster. We explicitly added clustered indexes in our relational database to achieve faster queries.

Other than performance, we also take safety into consideration. We had pragma key credentials in the database to avoid sensitive information leakage. We also had encrypted TCP connection with digital certificate and private key verification. 



## Dependencies & Requirements

* CMake 3.25
* g++-10
* Ninja (Optional)

* String formatting tool: [fmt](https://github.com/fmtlib/fmt)
* JSON formatting tool: [json](https://github.com/nlohmann/json), [glaze(faster)](https://github.com/stephenberry/glaze)
* Database: Install with `sudo apt-get install libsqlite3-dev`, and optionally, [SQLite3 Encryption](https://github.com/rindeal/SQLite3-Encryption) (Only accessible on Windows system, MSVC)
* Parallelism: [openmp](https://www.openmp.org/resources/)
* Security: Install with `sudo apt install libssl-dev`



## Quick Start

In the front-end part, install Qt6 on your local operating system, navigate to front-end directory compile with cmake.

In the back-end part, compile server with CMakeLists.txt.

If you are working with Ninja, execute the following commands:

```bash
cmake -G Ninja
ninja
```

Otherwise,

```bash
cmake CMakeLists.txt
make
```

If activate without openssl, on the server side,

```bash
cd bin/
./cplusplusproject2022fall
```

On the client side, after compiled with C++20,

```bash
./client_unencrypted.cpp SERVER_IP
```

If activate with openssl (after quick modification on the CMakeLists.txt), additionally, you need CA certificate and private key,

```bash
cd bin/
./cplusplusproject2022fall PATH_TO_CA_CERTIFICATE PATH_TO_UNSECURED_PRIVATE_KEY
```

On the client side, after compiled with C++20,

```bash
./client.cpp SERVER_IP PATH_TO_CA_CERTIFICATE PATH_TO_UNSECURED_PRIVATE_KEY
```



## Memory Check with Valgrind

To install Valgrind, please follow the steps
```bash
wget https://sourceware.org/pub/valgrind/valgrind-3.20.0.tar.bz2
tar xvf valgrind-3.20.0.tar.bz2
cd valgrind-3.20.0
./configure
make
sudo make install
```

For memcheck
```bash
cd bin/
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./cplusplusproject2022fall
```



## Part of C++ new features

* Concept & Requires & template
* Vectorization
* Structural binding
* Chrono
* Constexpr & Lambda
* Smart pointers
* Const transformation
* Final
* Variant
* Explicit
* Variadic Template



## Acknowledge

We thank the assistance and guidance from Prof. [Bjarne Stroustrup](https://www.stroustrup.com/).
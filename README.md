## Introduction

We intend to develop a complicated full stack application based on socket-based server-client connection. The front-end of this application is Qt6 and back-end is SQLite3/MongoDB(experimental). Serveral highlights of this application are:

* Modern C++20
* Multiplexing with epoll (linux only) to achieve pseudo-concurrency
* Multi-threading
* A variety of database selection



## Dependencies & Requirements

* CMake 3.25
* g++-10

* String formatting tool: [fmt](https://github.com/fmtlib/fmt)
* JSON formatting tool: [json](https://github.com/nlohmann/json)
* Database: [SQLite3](https://github.com/SRombauts/SQLiteCpp/tree/master/sqlite3)
* Parallelism: [openmp](https://www.openmp.org/resources/)



## Quick Start

Compile server with CMakeLists.txt.

```bash
cmake CMakeLists.txt
make
```

Execute with

```bash
cd bin/
./cplusplusproject2022fall
```




## C++ new features

* Concept & Requires & template
* Structural binding
* Chrono
* Constexpr
* Smart pointers
* std::as_const()
* Final
* Variant
* Explicit
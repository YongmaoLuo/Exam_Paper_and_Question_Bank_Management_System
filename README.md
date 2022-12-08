## Introduction

The repository archives a full-stack demo application, concentrating on exam paper management system. The front-end is based on Qt6 and back-end leverages modern C++ features. The database is implemented with SQLite3. 

This is a server-client style application and the connection is based on socket.



## Dependencies & Requirements

* CMake 3.25
* g++-10

* String formatting tool: [fmt](https://github.com/fmtlib/fmt)
* JSON formatting tool: [json](https://github.com/nlohmann/json)
* Database: [SQLite3](https://github.com/SRombauts/SQLiteCpp/tree/master/sqlite3)
* Parallelism: openmp



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

* Concept & template
* Structural binding
* Chrono
* Constexpr
* Smart pointers
* std::as_const()
* Final
* Variant
* ...
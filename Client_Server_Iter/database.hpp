#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <vector>
#include <set>
#include <variant>
#include <optional>
#include <iostream>
#include <cstddef>
#include <concepts>
#include <cctype>
#include <cassert>

using namespace std;

class database{
    private:
        sqlite3 *db;
        sqlite3_stmt *stmt;
    public:
        virtual void create(bool, const char*) = 0;
        virtual int update(string primary_val, vector<pair<string, variant<string, int, double>>> changelist) = 0;
        virtual int count() = 0;
        virtual int delet(string primary_val, pair<string, variant<string, int, double>> deleted_info) = 0;
        virtual void clean() = 0;
        virtual void close(){
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
};
#endif
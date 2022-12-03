#ifndef DB_HPP
#define DB_HPP
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <vector>
#include <set>
#include <optional>
#include <iostream>
using namespace std;

#define FMT_HEADER_ONLY
#include "fmt/format.h"

struct UserInfo {
            string account;
            string password;
            string identity;
            string status;
            UserInfo operator=(UserInfo newuser){
                account = newuser.account;
                password = newuser.password;
                identity = newuser.identity;
                status = newuser.status;
                return *this;
            }
        };

class db_user{
    private:
        sqlite3 *db;
        sqlite3_stmt *stmt;
        char *zErrMsg;
        int rc;
        string sql;
        vector<string>attrs;
        
    public:
        db_user(vector<string>&attrs);
        db_user(const db_user& database);
        virtual ~db_user(); //drop the table?

        void create();
        int insert(vector<UserInfo> users);
        int update(auto primary_val, vector<pair<string, string>> changelist);
        bool find(optional<pair<string, string>> constraint, auto primary_val);
        void delet(auto primary_val);
        void drop();
};

#endif
#ifndef DB_HPP
#define DB_HPP
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

class db_user{
    private:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        string *sql;
        db_user();
        db_user(const db_user& database);
        virtual ~db_user(); //drop the table?
    public:
        struct UserInfo{
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
        void create(vector<UserInfo userinfo> users);
        void update(auto key, auto val);
        bool find(auto key, auto val);
        void delet(auto key);
        void drop();
};
#endif
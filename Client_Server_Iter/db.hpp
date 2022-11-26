#ifndef DB_HPP
#define DB_HPP
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <vector>
#include <set>
#include <variant>
#include <optional>
#include <iostream>
using namespace std;

#define FMT_HEADER_ONLY
#include "fmt/format.h"

inline string custom_to_string(variant<string, int, double> const& value) {
    if(int const* pval = std::get_if<int>(&value))
    return std::to_string(*pval);
    
    if(double const* pval = std::get_if<double>(&value))
    return std::to_string(*pval);
    
    return std::get<string>(value);
}

template<hashable T>
struct UserInfo{
            string username;
            string password;
            T identity;
            T status;
            int activity = 0; // no boolean inside sqlite
            UserInfo<T> operator=(UserInfo<T> newuser){
                username = newuser.username;
                password = newuser.password;
                identity = newuser.identity;
                status = newuser.status;
                activity = newuser.activity;
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
        
    public:
        db_user();
        db_user(const db_user& database);
        virtual ~db_user(); //drop the table?

        void create(bool = false, const char* = "userinfo.db");
        int insert(UserInfo<string>& user);
        int update(string primary_val, vector<pair<string, variant<string, int, double>>> changelist);
        
        template<hashable T>
        T findUserAttribute(optional<pair<string, variant<string, int, double>>> constraint, string primary_val, string target_attribute){
            if(constraint){
                auto constraint_val = constraint.value();
                string key = constraint_val.first;
                auto value = constraint_val.second;
                sql = fmt::format("SELECT {} FROM USER "  \
                            "WHERE USERNAME = '{}' AND {} = '{}'; ", target_attribute, primary_val, key, custom_to_string(value));
            }
            else sql = fmt::format("SELECT {} FROM USER " \
                            "WHERE USERNAME = '{}'; ", target_attribute, primary_val);
            // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
            sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
            // if(sqlite3_step(stmt) != SQLITE_DONE){
            //    fprintf(stderr, "SQL error");
            //    return false;
            // }
            int num_cols;
            vector<T> output;
            while(sqlite3_step(stmt) != SQLITE_DONE){
                vector<T> row;
                num_cols = sqlite3_column_count(stmt);
                for(int i = 0; i < num_cols; i++){
                    switch(sqlite3_column_type(stmt, i)){
                        case(SQLITE3_TEXT):
                        row.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
                        break;
                        case(SQLITE_INTEGER):
                        row.push_back(sqlite3_column_int(stmt, i));
                        break;
                        case(SQLITE_FLOAT):
                        row.push_back(sqlite3_column_double(stmt, i));
                        break;
                        default:
                        break;
                    }
                }
                output.insert(output.end(), row.begin(), row.end());
            }
            
            if(output.empty()) {
                cout<<"User attribute not found"<<endl;
                return {};
            }
            return output[0];
        }

        template<hashable T>
        vector<T> getUserAttributes(string target_attribute, string constraint_key, string constraint_val){
            sql = fmt::format("SELECT {} FROM USER " \
                            "WHERE {} = '{}'; ", target_attribute, constraint_key, constraint_val);
            // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
            sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
            // if(sqlite3_step(stmt) != SQLITE_DONE){
            //    fprintf(stderr, "SQL error");
            //    return false;
            // }
            int num_cols;
            vector<T> output;
            while(sqlite3_step(stmt) != SQLITE_DONE){
                vector<T> row;
                num_cols = sqlite3_column_count(stmt);
                for(int i = 0; i < num_cols; i++){
                    switch(sqlite3_column_type(stmt, i)){
                        case(SQLITE3_TEXT):
                        row.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
                        break;
                        case(SQLITE_INTEGER):
                        row.push_back(sqlite3_column_int(stmt, i));
                        break;
                        case(SQLITE_FLOAT):
                        row.push_back(sqlite3_column_double(stmt, i));
                        break;
                        default:
                        break;
                    }
                }
                output.insert(output.end(), row.begin(), row.end());
            }
            
            if(output.empty()) {
                cout<<"User attribute not found"<<endl;
                return {};
            }
            return output;
        }

        int count();
        vector<string> getUsers();
        int delet(string primary_val, pair<string, variant<string, int, double>> deleted_info);
        void clean();
        void close();
};
#endif
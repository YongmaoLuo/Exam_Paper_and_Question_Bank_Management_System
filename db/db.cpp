// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the L
#include <iostream>
// #include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <string.h>
#include <sqlite3.h>
#include "fmt/format.h"

// #include "tagged_sqlite.h"
 

using namespace std;


// string check_username(sqlite3* db, string query) {
//     auto client_lookup = ftsd::prepared_statement<
//         "select password/*:text*/ from clients "
//         "where username = ? /*:name:text*/;"
//         >
//         {sqldb}.execute_single_row({bind<"username">(query)});

//     if (!client_lookup) {
//         std::cerr << "Unable to find username\n";
//     }
//     return client_lookup.value()
// }
/*
struct {
  int id;
  string username;
  string password;
} userinfo;
*/

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for (i=0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

class db_user {
  private:
    vector<string>attrs = {"USERNAME", "PASSWORD"};
    char* zErrMsg = 0;
    int rc;
    char *sql;
  public:
    sqlite3 *db;
    db_user();
    db_user(const db_user& database);
    virtual ~db_user();

    // void create(vector<string> attributes) {
    void create() {
      int i,a = attrs.size();
      string s = "CREATE TABLE CLIENTS(";
      s += fmt.format("{} TEXT NOT NULL PRIMARY KEY, ", attrs[0]);
      for (i=1; i<a-1; i++) {
        s += fmt.format("{} TEXT NOT NULL, ", attrs[i]);
      }
      s += fmt.format("{} TEXT NOT NULL );", attrs[a-1]);

      sql = &s[0];
      // sql = "CREATE TABLE CLIENTS("
      //       "USERNAME TEXT NOT NULL PRIMARY KEY, "
      //       "PASSWORD TEXT NOT NULL "
      //       ");" ;

      rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

      if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      } else {
          fprintf(stdout, "Table created successfully\n");
      }
    }
    void insert(vector<vector<string>>elems) {

      // string s = "INSERT INTO CLIENTS (ID, USERNAME, PASSWORD) ");
      string ins = "INSERT INTO CLIENTS (", vals;
      int i, j, a = attrs.size(), n=elems.size();

      if (!elems.size()) {
        fprintf(stderr, "SQL insertion can't be empty\n");
      }

      int m=elems[0].size();

      if (a != elems[0].size()) {
          fprintf(stderr, "SQL inserted attribute number not matched\n");
      }

      for (i=0; i<a-1; i++) {
        ins += fmt.format("{}, ", attrs[i]);
      }
      ins += fmt.format("{}) ", attrs[a-1]);

      string s = "";

      for (i=0; i<n; i++) {
        s += ins;
        vals = "VALUES (";
        for (j=0; j<m-1; j++) {
          vals += fmt.format("'{}', ", elems[i][j]);
        }
        vals += fmt.format("'{}'); ", elems[i][m-1]);
        s += vals;
      }

      sql = &s[0];

      // sql = "INSERT INTO CLIENTS (USERNAME, PASSWORD) "  \
      //       "VALUES ('Batman', '123456'); " \
      //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) "  \
      //       "VALUES ('Nightwing', 'nasdj23rf'); "     \
      //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) " \
      //       "VALUES ('Redhood', '3287dy78'); " \
      //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) " \
      //       "VALUES ('Redrobin', 'sd89ufe'); " \
      //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) " \
      //       "VALUES ('Damian', 'u9dw3u88'); " ;

      rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      } else {
          fprintf(stdout, "Inserted into table successfully\n");
      }
    }
    void update(string key1, string key2, string val1, string val2) {
      string s = "UPDATE CLIENTS set "+key1+"="+val1+" where "+key2+"="+val2+"; " \
                 "SELECT * from CLIENTS";
      sql = &s[0];
      rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      } else {
          fprintf(stdout, "Table created successfully\n");
      }
    }
    void find(string key) {
      string s = "SELECT PASSWORD FROM CLIENTS"
                 "WHERE USERNAME = " + key;
      sql = &s[0];
      rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      } else {
          fprintf(stdout, "Table created successfully\n");
      }
    }
    void del(string key, string val) {
      string s= fmt::format("DELETE from CLIENTS where {}={}; \
                             SELECT * from COMPANY", key, val);
      sql = &s[0];
      rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      } else {
          fprintf(stdout, "Element(s) deleted successfully\n");
      }      
    }
    void drop();
};



// char* check_username(db_user dbobj, string query) {
//   char* sql;
//   string s = "SELECT PASSWORD FROM CLIENTS"
//              "WHERE USERNAME = " + query;
//   sql = &s[0];

//   int rc = sqlite3_exec(dbobj.db, sql, callback, 0, &dbobj.zErrMsg);

//   if (rc != SQLITE_OK) {
//       fprintf(stderr, "SQL error: %s\n", dbobj.zErrMsg);
//       sqlite3_free(dbobj.zErrMsg);
//   } else {
//       fprintf(stdout, "Table created successfully\n");
//   }
  
//   return sql;
// }


int main() {
  db_user dbObj;
  /* Open database */
  int rc = sqlite3_open("test.db", &dbObj.db);
  
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbObj.db));
    return(0);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }

  vector<vector<string>>items = {{"Batman", "123456"},
                                 {"Nightwing", "nasdj23rf"},
                                 {"Redhood", "3287dy78"},
                                 {"Redrobin", "sd89ufe"},
                                 {"Damian", "u9dw3u88"}};

  /* Create SQL Table */
  dbObj.create();
  /* Create SQL statement */
  dbObj.insert(items);

  /* Find password given username */
  string query="Batman";
  cout<<dbObj.find(query)<<endl;
        
  sqlite3_close(dbObj.db);
  return 0;
}


// #include <iostream>
// int main() {
//     using ftsd::bind;
//     using ftsd::field;

//     sqlite3 *sqldb;
//     sqlite3_open(":memory:", &sqldb);

//     ftsd::prepared_statement<
//         "CREATE TABLE clients("
//         "username TEXT NOT NULL PRIMARY KEY, "
//         "password TEXT NOT NULL"
//         ");"  //
//         >{sqldb}
//         .execute();



//     // auto client_id = field<"id">(customer_id_or.value());

//     ftsd::prepared_statement<
//         "INSERT INTO clients(username , password ) "
//         "VALUES (?/*:username:text*/, ?/*:password:text*/);"  //
//         >
//         insert_order{sqldb};

//     insert_order.execute({bind<"username">("batman"), bind<"password">("123456")});
//     insert_order.execute({bind<"username">("nightwing"), bind<"password">("nasdj23rf")});
//     insert_order.execute({bind<"username">("redhood"), bind<"password">("3287dy78")});
//     insert_order.execute({bind<"username">("redrobin"), bind<"password">("sd89ufe")});
//     insert_order.execute({bind<"username">("damian"), bind<"password">("u9dw3u88")});

//     cout<<check_username(sqldb, "batman")<<endl;
//     return 0;
// } 


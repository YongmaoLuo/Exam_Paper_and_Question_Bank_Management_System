#include "db.hpp"


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i=0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

db_user::db_user(vector<string>&attrs) {
   db = 0;
   stmt = 0;
   zErrMsg = 0;
   rc = 0;
   attrs=attrs; // {"IDENTITY", "ACCOUNT", "PASSWORD", "STATUS"}
   // sql = NULL;
}

db_user::db_user(const db_user& database) {

}

db_user::~db_user(){
   sqlite3_finalize(stmt);
   sqlite3_close(db);
}

void db_user::create(){
   // rc = sqlite3_open("userinfo.db", &db);
   // CREATE/OPEN
   rc = sqlite3_open_v2("userinfo.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 
                        NULL);
   
   if(rc != SQLITE_OK) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
   /* Create SQL statement */

   sql = "CREATE TABLE USER( \
            IDENTITY TEXT NOT NULL,  \
            ACCOUNT TEXT NOT NULL PRIMARY KEY, \
            PASSWORD TEXT NOT NULL, \
            STATUS TEXT NOT NULL \
            );" ;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if(rc != SQLITE_OK){
      drop();
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
}


int db_user::insert(vector<UserInfo> users){
  int i, j, a = attrs.size(), n=users.size();

  if (!users.size()) {
    fprintf(stderr, "SQL insertion can't be empty\n");
  }

  string ins = "INSERT INTO USERS (", identity, account, password, status;
  for (i=0; i<a-1; i++) {
    ins += fmt.format("{}, ", attrs[i]);
  }
  ins += fmt.format("{}) ", attrs[a-1]);

  sql = "";

  for (i=0; i<n; i++) {
    sql += ins;
    identity = user.identity;
    account = user.account;
    password = user.password;
    status = user.status;
    // vals = "VALUES (";
    // for (j=0; j<m-1; j++) {
    //   vals += fmt.format("'{}', ", elems[i][j]);
    // }
    // vals += fmt.format("'{}'); ", elems[i][m-1]);
    // s += vals;
    sql += fmt::format("VALUES ('{}', '{}', '{}', '{}'); ", identity, account, password, status);
  }

  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
  
  if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
  } else {
        fprintf(stdout, "Inserted into table successfully\n");
  }
  return rc;
}

int db_user::update(auto primary_val, vector<pair<string, string>> changelist){
   std::set<string> keys;
   string key;
   string value;
   while(!changelist.empty()){
      auto changed = changelist.back();
      key = changed.first;
      value = changed.second;
      changelist.pop_back();
      if(keys.count(key)){
         continue;
      }
      keys.insert(key);
      
      if(key == "ACCOUNT") return -1;
      sql = fmt::format("UPDATE USER set {} = '{}' where ACCOUNT = '{}'; " \
                  "SELECT * from USER", key, value, primary_val);
      cout<<sql<<endl;
      rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
      if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
      } else {
            fprintf(stdout, "Table updated successfully\n");
      }
   }
   return rc;
}

bool db_user::find(optional<vector<pair<string, string>>> constraint, auto primary_val){
   if (constraint){
      auto constraint_val = constraint.value();
      int i, n = constraint_val.size();
      string key;
      string val;
      sql = fmt::format("SELECT COUNT (*) FROM USER WHERE ACCOUNT = '{}'", primary_val);
      for (i=0; i<n; i++) {
        key = constraint_val[i].first;
        val = constraint_val[i].second;
        sql += fmt::format(" AND {} = '{}'", key, val);
      }
      sql += "; "

      // sql = fmt::format("SELECT COUNT (*) FROM USER " \
      //             "WHERE ACCOUNT = '{}' AND {} = '{}'; ", primary_val, key, value);

   } else sql = fmt::format("SELECT COUNT (*) FROM USER " \
                  "WHERE ACCOUNT = '{}'; ", primary_val);
   // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
   // if(sqlite3_step(stmt) != SQLITE_DONE){
   //    fprintf(stderr, "SQL error");
   //    return false;
   // }
   int num_cols;
   vector<vector<char* >> output;
   while(sqlite3_step(stmt) != SQLITE_DONE){
      vector<char*> row;
      num_cols = sqlite3_column_count(stmt);
      for(int i=0; i<num_cols; i++){
         switch(sqlite3_column_type(stmt, i)){
            case(SQLITE3_TEXT):
               row.push_back((char*) sqlite3_column_text(stmt, i));
               break;
            case(SQLITE_INTEGER):
               row.push_back((char*) to_string(sqlite3_column_int(stmt, i)).data());
               break;
            case(SQLITE_FLOAT):
               row.push_back((char*) to_string(sqlite3_column_double(stmt, i)).data());
               break;
            default:
               break;
         }
      }
      output.push_back(row);
   }
   
   if(atoi(output[0][0]) == 0) return false;
   return true;
}

void db_user::delet(auto primary_val){
   sql = fmt::format("DELETE from USER where ACCOUNT = '{}'; \
                SELECT * from USER", primary_val);
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Element(s) deleted successfully\n");
   }
}

void db_user::drop(){
   fprintf(stderr, "SQL dropped: %s\n", zErrMsg);
   sqlite3_free(zErrMsg);
}

int main(int argc, char* argv[]) {
  vector<string>attrs = {"IDENTITY", "ACCOUNT", "PASSWORD", "STATUS"};
  db_user user = db_user(attrs);
  user.create();

  vector<struct UserInfo> users_example = {{"admin",  "Alvin", "123456", "valid"}, 
                                           {"client", "Batman", "ew9fyw8", "valid"}};
  user.insert(users_example);
  string primekey_val = "admin";

  vector<pair<string, string>> changelist; // (key, value pair)
  changelist.emplace_back("STATUS", "expired");
  changelist.emplace_back("STATUS", "valid");
  int status = user.update(primekey_val, changelist);
  cout<<"update status "<<status<<endl;

  string db_key = "IDENTITY";
  auto identity_val = "admin";
  optional<pair<string, string>> constraint;
  constraint = std::make_pair(db_key, identity_val);
  bool found = user.find(constraint, primekey_val);
  cout<<"find status "<<found<<endl;

  user.delet(primekey_val);
  return 0;
}


// class db_user {
//   private:
//     vector<string>attrs = {"USERNAME", "PASSWORD"};
//     char* zErrMsg = 0;
//     int rc;
//     char *sql;
//   public:
//     sqlite3 *db;
//     db_user();
//     db_user(const db_user& database);
//     virtual ~db_user();

//     // void create(vector<string> attributes) {
//     void create() {
//       int i,a = attrs.size();
//       string s = "CREATE TABLE CLIENTS(";
//       s += fmt.format("{} TEXT NOT NULL PRIMARY KEY, ", attrs[0]);
//       for (i=1; i<a-1; i++) {
//         s += fmt.format("{} TEXT NOT NULL, ", attrs[i]);
//       }
//       s += fmt.format("{} TEXT NOT NULL );", attrs[a-1]);

//       sql = &s[0];
//       // sql = "CREATE TABLE CLIENTS("
//       //       "USERNAME TEXT NOT NULL PRIMARY KEY, "
//       //       "PASSWORD TEXT NOT NULL "
//       //       ");" ;

//       rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

//       if (rc != SQLITE_OK) {
//           fprintf(stderr, "SQL error: %s\n", zErrMsg);
//           sqlite3_free(zErrMsg);
//       } else {
//           fprintf(stdout, "Table created successfully\n");
//       }
//     }

//     void insert(vector<vector<string>>elems) {

//       // string s = "INSERT INTO CLIENTS (ID, USERNAME, PASSWORD) ");
//       string ins = "INSERT INTO CLIENTS (", vals;
//       int i, j, a = attrs.size(), n=elems.size();

//       if (!elems.size()) {
//         fprintf(stderr, "SQL insertion can't be empty\n");
//       }

//       int m=elems[0].size();

//       if (a != elems[0].size()) {
//           fprintf(stderr, "SQL inserted attribute number not matched\n");
//       }

//       for (i=0; i<a-1; i++) {
//         ins += fmt.format("{}, ", attrs[i]);
//       }
//       ins += fmt.format("{}) ", attrs[a-1]);

//       string s = "";

//       for (i=0; i<n; i++) {
//         s += ins;
//         vals = "VALUES (";
//         for (j=0; j<m-1; j++) {
//           vals += fmt.format("'{}', ", elems[i][j]);
//         }
//         vals += fmt.format("'{}'); ", elems[i][m-1]);
//         s += vals;
//       }

//       sql = &s[0];

//       // sql = "INSERT INTO CLIENTS (USERNAME, PASSWORD) "  \
//       //       "VALUES ('Batman', '123456'); " \
//       //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) "  \
//       //       "VALUES ('Nightwing', 'nasdj23rf'); "     \
//       //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) " \
//       //       "VALUES ('Redhood', '3287dy78'); " \
//       //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) " \
//       //       "VALUES ('Redrobin', 'sd89ufe'); " \
//       //       "INSERT INTO CLIENTS (USERNAME, PASSWORD) " \
//       //       "VALUES ('Damian', 'u9dw3u88'); " ;

//       rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//       if (rc != SQLITE_OK) {
//           fprintf(stderr, "SQL error: %s\n", zErrMsg);
//           sqlite3_free(zErrMsg);
//       } else {
//           fprintf(stdout, "Inserted into table successfully\n");
//       }
//     }
//     void update(string key1, string key2, string val1, string val2) {
//       string s = "UPDATE CLIENTS set "+key1+"="+val1+" where "+key2+"="+val2+"; " \
//                  "SELECT * from CLIENTS";
//       sql = &s[0];
//       rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//       if (rc != SQLITE_OK) {
//           fprintf(stderr, "SQL error: %s\n", zErrMsg);
//           sqlite3_free(zErrMsg);
//       } else {
//           fprintf(stdout, "Table created successfully\n");
//       }
//     }
    
//     string find(string key) {
//       string s = "SELECT PASSWORD FROM CLIENTS"
//                  "WHERE USERNAME = " + key;
//       sql = &s[0];
//       rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//       if (rc != SQLITE_OK) {
//           fprintf(stderr, "SQL error: %s\n", zErrMsg);
//           sqlite3_free(zErrMsg);
//       } else {
//           fprintf(stdout, "Table created successfully\n");
//       }
//     }


//     void del(string key, string val) {
//       string s= fmt::format("DELETE from CLIENTS where {}={}; \
//                              SELECT * from COMPANY", key, val);
//       sql = &s[0];
//       rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//       if (rc != SQLITE_OK) {
//           fprintf(stderr, "SQL error: %s\n", zErrMsg);
//           sqlite3_free(zErrMsg);
//       } else {
//           fprintf(stdout, "Element(s) deleted successfully\n");
//       }      
//     }
//     void drop();
// };



// // char* check_username(db_user dbobj, string query) {
// //   char* sql;
// //   string s = "SELECT PASSWORD FROM CLIENTS"
// //              "WHERE USERNAME = " + query;
// //   sql = &s[0];

// //   int rc = sqlite3_exec(dbobj.db, sql, callback, 0, &dbobj.zErrMsg);

// //   if (rc != SQLITE_OK) {
// //       fprintf(stderr, "SQL error: %s\n", dbobj.zErrMsg);
// //       sqlite3_free(dbobj.zErrMsg);
// //   } else {
// //       fprintf(stdout, "Table created successfully\n");
// //   }
  
// //   return sql;
// // }


// int main() {
//   db_user dbObj;
//   /* Open database */
//   int rc = sqlite3_open("test.db", &dbObj.db);
  
//   if (rc) {
//     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbObj.db));
//     return(0);
//   } else {
//     fprintf(stdout, "Opened database successfully\n");
//   }

//   vector<vector<string>>items = {{"Batman", "123456"},
//                                  {"Nightwing", "nasdj23rf"},
//                                  {"Redhood", "3287dy78"},
//                                  {"Redrobin", "sd89ufe"},
//                                  {"Damian", "u9dw3u88"}};

//   /* Create SQL Table */
//   dbObj.create();
//   /* Create SQL statement */
//   dbObj.insert(items);

//   /* Find password given username */
//   string query="Batman";
//   cout<<dbObj.find(query)<<endl;
        
//   sqlite3_close(dbObj.db);
//   return 0;
// }


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


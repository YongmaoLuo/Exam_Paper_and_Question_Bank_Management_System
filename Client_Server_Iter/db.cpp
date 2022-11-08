#include "db.hpp"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

db_user::db_user(){
   db = 0;
   stmt = 0;
   zErrMsg = 0;
   rc = 0;
   // sql = NULL;
}

db_user::db_user(const db_user& database){

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
            IDENTITY TEXT NOT NULL PRIMARY KEY,  \
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

int db_user::insert(UserInfo user){
   string identity = user.identity;
   string account = user.account;
   string password = user.password;
   string status = user.status;
   sql = fmt::format("INSERT INTO USER (IDENTITY, ACCOUNT, PASSWORD, STATUS) "  \
            "VALUES ('{}', '{}', '{}', '{}'); ", identity, account, password, status);
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

int db_user::update(auto key, auto value, auto primary_val){
   if(key == "ACCOUNT") return -1;
   string s = fmt::format("UPDATE USER set {} = {} where ACCOUNT = {}; " \
               "SELECT * from USER", key, value, primary_val);
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
         sqlite3_free(zErrMsg);
         return -1;
   } else {
         fprintf(stdout, "Table updated successfully\n");
   }
   return rc;
}

bool db_user::find(auto key, auto value, auto primary_val){
   sql = fmt::format("COUNT * FROM USER"
                 "WHERE ACCOUNT = {} && {} = {}", primary_val, key, value);
   // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   // if(sqlite3_step(stmt) != SQLITE_DONE){
   //    fprintf(stderr, "SQL error");
   //    return false;
   // }
   int num_cols = sqlite3_column_count(stmt);
   vector<vector<char* >> output;
   while(sqlite3_step(stmt) != SQLITE_DONE){
      vector<char*> row;
      for(int i = 0; i < num_cols; i++){
         switch(sqlite3_column_type(stmt, i)){
            case(SQLITE3_TEXT):
               row.push_back((char*) sqlite3_column_text(stmt, i));
               break;
            case(SQLITE_INTEGER):
               row.push_back((char*) sqlite3_column_int(stmt, i));
               break;
            case(SQLITE_FLOAT):
               row.push_back((char*) sqlite3_column_double(stmt, i));
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
   string s= fmt::format("DELETE from USER where ACCOUNT = {}; \
                SELECT * from COMPANY", primary_val);
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
   db_user user = db_user();
   return 0;
}
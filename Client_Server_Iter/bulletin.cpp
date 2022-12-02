#include "bulletin.hpp"


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
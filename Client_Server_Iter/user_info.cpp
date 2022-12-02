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

void db_user::create(bool clear/*= false*/, const char* database_name/*= "userinfo.db"*/){
   // rc = sqlite3_open(database_name, &db);
   // CREATE/OPEN
   rc = sqlite3_open_v2(database_name, &db, SQLITE_OPEN_READWRITE, 
                        NULL);
   
   if(rc != SQLITE_OK) {
      fprintf(stderr, "No such database, creating a new one: %s\n", sqlite3_errmsg(db));
      rc = sqlite3_open_v2(database_name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 
                     NULL);

   } else {
      if(clear) clean();
      fprintf(stdout, "Opened database successfully\n");
   }
   /* Create SQL statement */

   sql = "CREATE TABLE IF NOT EXISTS USER( \
            USERNAME TEXT NOT NULL PRIMARY KEY,  \
            PASSWORD TEXT NOT NULL, \
            IDENTITY VARCHAR(15) CHECK(IDENTITY IN ('admin', 'rule maker', 'teacher')), \
            STATUS VARCHAR(10) DEFAULT valid, \
            ACTIVITY BOOLEAN DEFAULT 0 CHECK(ACTIVITY IN (0, 1))\
            );" ;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if(rc != SQLITE_OK){
      fprintf(stderr, "SQL dropped: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
}

int db_user::insert(UserInfo<string>& user){
   string identity = user.identity;
   string username = user.username;
   string password = user.password;
   string status = user.status;
   int activity = user.activity;
   if(status.empty()) status = "valid";
   sql = fmt::format("INSERT INTO USER (USERNAME, PASSWORD, IDENTITY, STATUS, ACTIVITY) "  \
            "VALUES ('{}', '{}', '{}', '{}', '{}'); SELECT * FROM USER", username, password, identity, status, activity);
   cout<<sql<<endl;
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

int db_user::update(string primary_val, vector<pair<string, variant<string, int, double>>> changelist){
   std::set<string> keys;
   string key;
   while(!changelist.empty()){
      auto changed = changelist.back();
      key = changed.first;
      auto value = changed.second;
      changelist.pop_back();
      if(keys.count(key)){
         continue;
      }
      keys.insert(key);
      
      if(key == "USERNAME") return -1;
      sql = fmt::format("UPDATE USER set {} = '{}' where USERNAME = '{}'; SELECT * FROM USER", key, custom_to_string(value), primary_val);

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

string db_user::checkType(string target_attribute){
   sql = fmt::format("SELECT typeof({}) FROM USER LIMIT 1;", target_attribute);
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
   int num_cols;
   int bytes;
   char* row_content_raw;
   string res;
   while(sqlite3_step(stmt) != SQLITE_DONE){
         num_cols = sqlite3_column_count(stmt);
         for(int i = 0; i < num_cols; i++){
            row_content_raw = const_cast<char*>(static_cast<const char *>(sqlite3_column_blob(stmt, i)));
            bytes = sqlite3_column_bytes(stmt, i);
            res = string(row_content_raw, bytes);
         }
   }
   transform(res.begin(), res.end(), res.begin(), ::toupper);
   return res;
}


string db_user::getUserAttribute(optional<pair<string, variant<string, int, double>>> constraint, string primary_val, string target_attribute)
{
   if(constraint){
         auto constraint_val = constraint.value();
         string key = constraint_val.first;
         auto value = constraint_val.second;
         sql = fmt::format("SELECT {} FROM USER "  \
                     "WHERE USERNAME = '{}' AND {} = '{}' LIMIT 1; ", target_attribute, primary_val, key, custom_to_string(value));
   }
   else sql = fmt::format("SELECT {} FROM USER " \
                     "WHERE USERNAME = '{}' LIMIT 1; ", target_attribute, primary_val);
   cout<<sql<<endl;
   // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
   int num_cols;
   int bytes = 0;
   char* row_content_raw;
   string res;
   
   while(sqlite3_step(stmt) != SQLITE_DONE){
         num_cols = sqlite3_column_count(stmt);
         for(int i = 0; i < num_cols; i++){
            row_content_raw = const_cast<char*>(static_cast<const char *>(sqlite3_column_blob(stmt, i)));
            bytes = sqlite3_column_bytes(stmt, i);
            res = string(row_content_raw, bytes);
         }
   }
   if(bytes) return res;
   else return {};
}


// vector<string> db_user::getUserAttributes(string target_attribute, string constraint_key, string constraint_val)
// {
//    sql = fmt::format("SELECT {} FROM USER " \
//                      "WHERE {} = '{}'; ", target_attribute, constraint_key, constraint_val);
//    // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
//    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

//    int num_cols;
//    int bytes;
//    vector<string> output;
//    char* row_content_raw;
//    string res;
//    while(sqlite3_step(stmt) != SQLITE_DONE){
//          vector<string> row;
//          num_cols = sqlite3_column_count(stmt);
//          for(int i = 0; i < num_cols; i++){
//             row_content_raw = const_cast<char*>(static_cast<const char *>(sqlite3_column_blob(stmt, i)));
//             bytes = sqlite3_column_bytes(stmt, i);

//             res = string(row_content_raw, bytes);
            
//             row.push_back(res);
//          }
//          output.insert(output.end(), row.begin(), row.end());
//    }
   
//    if(output.empty()) {
//          cout<<"User attribute not found"<<endl;
//          return {};
//    }
//    return output;
// }


int db_user::count(){
   sql = "SELECT COUNT (*) from USER;"; 
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
   int num_cols;
   vector<char* > output;
   while(sqlite3_step(stmt) != SQLITE_DONE){
      vector<char*> row;
      num_cols = sqlite3_column_count(stmt);
      for(int i = 0; i < num_cols; i++){
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
      output.insert(output.end(), row.begin(), row.end());
   }
   if(output.empty()) return -1;
   return atoi(output[0]);
}

int db_user::delet(string primary_val, pair<string, variant<string, int, double>> authenticated_info){
   string key = authenticated_info.first;
   auto value = authenticated_info.second;
   sql = fmt::format("DELETE from USER where USERNAME = '{}' AND {} = '{}'; \
                SELECT * from USER", primary_val, key, custom_to_string(value));
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return -1;
   } else {
      fprintf(stdout, "Element(s) deleted successfully\n");
   }
   return rc;
}

void db_user::clean(){
   sql = "DROP TABLE IF EXISTS USER;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table dropped successfully\n");
   }
}

// int main(int argc, char* argv[]) {
//    std::shared_ptr<db_user> user = std::make_shared<db_user>();
//    bool clear = true;
//    user->create(clear);

//    UserInfo<string> user_example = {username: string("admin"), 
//                             password: string("123456"),
//                             identity: "admin",
//                             status: "valid"
//                             };
//    user->insert(user_example);
//    string primekey_val = "admin";

//    vector<pair<string, variant<string, int, double>>> changelist; // (key, value pair)
//    changelist.emplace_back("STATUS", "expired");
//    changelist.emplace_back("STATUS", "valid");
//    int status = user->update(primekey_val, changelist);
//    cout<<"update status "<<status<<endl;

//    optional<pair<string, string>> constraint2;
//    vector<string> usernames = user->getUserAttributes(constraint2, "USERNAME");
//    for(int i=0; i<std::ssize(usernames); i++) cout<<usernames[i]<<"\t";
//    cout<<endl;
//    int user_num = user->count();
//    cout<<user_num<<endl;

//    string db_key = "IDENTITY";
//    auto identity_val = "admin";
//    optional<pair<string, variant<string, int, double>>> constraint;
//    constraint = std::make_pair(db_key, identity_val);
//    string target_attributes = "ACTIVITY";
//    string activity = user->getUserAttribute(constraint, primekey_val, target_attributes);

//    int a = stoi(activity);
//    cout<<"find status "<<a<<endl;

//    // target_attributes = "PASSWORD";
//    vector<pair<string, string>> constraint3;
//    constraint3.emplace_back(std::make_pair("ACTIVITY", "0"));
//    constraint3.emplace_back(std::make_pair("IDENTITY", "admin"));
//    vector<int> activity_int = user->getUserAttributes<int>(constraint3, target_attributes);
//    cout<<*activity_int.begin()<<endl;

//    string key = "password";
//    auto val = static_cast<string>("123456");
//    pair<string, variant<string, int, double>> deleted_info = std::make_pair("password", "123456");

//    // status = user->delet(primekey_val, deleted_info);
//    // cout<<"delete status "<<status<<endl;
//    user->close();
//    return 0;
// }
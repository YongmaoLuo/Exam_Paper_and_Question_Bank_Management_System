#include "bulletin.hpp"


bulletinto::bulletinfo(){
   db = 0;
   stmt = 0;
   zErrMsg = 0;
   rc = 0;
   // sql = NULL;
}

bulletinto::bulletinfo(const bulletinfo& database){

}

bulletinto::~bulletinto(){
   sqlite3_finalize(stmt);
   sqlite3_close(db);
}

void bulletinto::create(bool clear/*= false*/, const char* database_name/*= "bulletin.db"*/){
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

   sql = "CREATE TABLE IF NOT EXISTS BULLETIN( \
            PATH varchar(20) NOT NULL,  \
            CONTENT TEXT, \
            RUBRIC INTEGER CHECK(RUBRIC >= 0),\
            PRIMARY KEY (PATH)\
            ) WITHOUT ROWID" ; // without rowid means using clustered index

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if (rc != SQLITE_OK){
      fprintf(stderr, "SQL dropped: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
}

int bulletinfo::insert(std::shared_ptr<BulletInfo<string>> bulletin){
   // string path = bulletin->path;
   // string content = bulletin->content;
   // string teacher = bulletin->teacher;
   // int rubric = bulletin->rubric;
   auto [path, content, teacher, rubric] = bulletin->getElements();
   sql = fmt::format("INSERT INTO QUESTIONS (PATH, CONTENT, TEACHER, RUBRIC) "  \
            "VALUES ('{}', '{}', '{}', '{}'); SELECT * FROM QUESTIONS", path, content, teacher, rubric);
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

int bulletinfo::update(vector<pair<string, string>> primary_pairs, vector<pair<string, variant<string, int, double>>> changelist){
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

      transform(key.begin(), key.end(), key.begin(), ::toupper);

      auto primary_keys = std::to_array<string>({"PATH", "TEACHER"});
      if(std::find(primary_keys.begin(), primary_keys.end(), key) != primary_keys.end()) return -1;
      
      sql = fmt::format("UPDATE BULLETIN set {} = '{}' where ", key, custom_to_string(value));
      for(int i=0; i<primary_pairs.size()-1; i++) sql += fmt::format("{} = '{}' AND ", primary_pairs[i].first, primary_pairs[i].second);
      sql += fmt::format("{} = '{}';", primary_pairs[primary_pairs.size()-1].first, primary_pairs[primary_pairs.size()-1].second);

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

vector<string> bulletinfo::getBulletins(){
   
   sql = fmt::format("SELECT PATH FROM BULLETIN;");
   
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

   int num_cols;
   vector<string> output;
   while (sqlite3_step(stmt) != SQLITE_DONE){
      vector<string> row;
      num_cols = sqlite3_column_count(stmt);
      for(int i=0; i<num_cols; i++){
         switch(sqlite3_column_type(stmt, i)){
            case(SQLITE3_TEXT):
               row.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
               break;
            case(SQLITE_INTEGER):
               row.push_back(to_string(sqlite3_column_int(stmt, i)));
               break;
            case(SQLITE_FLOAT):
               row.push_back(to_string(sqlite3_column_double(stmt, i)));
               break;
            default:
               break;
         }
      }
      output.insert(output.end(), row.begin(), row.end());
   }
   
   if (!output.empty()) return output;
   cout<<"path not found"<<endl;
   return output;
}

string bulletinfo::readBulletins(string primary_val) {

   sql = fmt::format("SELECT CONTENT FROM BULLETIN " \
                  "WHERE PATH = '{}'; ", primary_val);
   // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
   // if(sqlite3_step(stmt) != SQLITE_DONE){
   //    fprintf(stderr, "SQL error");
   //    return false;
   // }
   int num_cols;
   vector<string> output;
   while(sqlite3_step(stmt) != SQLITE_DONE){
      vector<string> row;
      num_cols = sqlite3_column_count(stmt);
      for(int i = 0; i < num_cols; i++){
         switch(sqlite3_column_type(stmt, i)){
            case(SQLITE3_TEXT):
               row.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
               break;
            case(SQLITE_INTEGER):
               row.push_back(to_string(sqlite3_column_int(stmt, i)));
               break;
            case(SQLITE_FLOAT):
               row.push_back(to_string(sqlite3_column_double(stmt, i)));
               break;
            default:
               break;
         }
      }
      output.insert(output.end(), row.begin(), row.end());
   }
   
   if(!output.empty()) return output[0];
   cout<<"question not found"<<endl;
   return {};
}

int bulletinfo::count(){
   sql = "SELECT COUNT (*) from BULLETIN LIMIT 1;"; 
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
   int num_cols;
   vector<int> output;
   while(sqlite3_step(stmt) != SQLITE_DONE){
      vector<int> row;
      num_cols = sqlite3_column_count(stmt);
      for(int i = 0; i < num_cols; i++){
         assert(sqlite3_column_type(stmt, i) == SQLITE_INTEGER);
         row.push_back(sqlite3_column_int(stmt, i));
      }
      output.insert(output.end(), row.begin(), row.end());
   }
   if(output.empty()) return -1;
   return output[0];
}



int bulletin::delet(vector<pair<string, string>> primary_pairs){
   sql = fmt::format("DELETE from BULLETIN where ");
   for(int i=0; i<primary_pairs.size(); i++){
      if(i < primary_pairs.size()-1)  sql += fmt::format("{} = '{}' AND ", primary_pairs[i].first, primary_pairs[i].second);
      else sql += fmt::format("{} = '{}' ;", primary_pairs[i].first, primary_pairs[i].second);
   }
    
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

void question_bank::clean(){
   sql = "DROP TABLE IF EXISTS BULLETIN;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table dropped successfully\n");
   }
}
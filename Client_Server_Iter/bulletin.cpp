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

   if(rc != SQLITE_OK){
      fprintf(stderr, "SQL dropped: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
}

int bulletinfo::insert(std::shared_ptr<BulletInfo<string>> bulletin){
   // string path = question->path;
   // string content = question->content;
   // string chapter = question->chapter;
   // string category = question->category;
   // int rubric = question->rubric;
   auto [path, content, category, rubric] = bulletin->getElements();
   if(category.empty()) category = "undefined";
   sql = fmt::format("INSERT INTO QUESTIONS (PATH, CONTENT, CHAPTER, SUBJECT, RUBRIC) "  \
            "VALUES ('{}', '{}', '{}', '{}', '{}'); SELECT * FROM QUESTIONS", path, content, chapter, category, rubric);
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

int question_bank::update(vector<pair<string, string>> primary_pairs, vector<pair<string, variant<string, int, double>>> changelist){
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

      // std::array<string, 3> primary_keys({"PATH", "CHAPTER", "SUBJECT"});
      auto primary_keys = std::to_array<string>({"PATH", "CHAPTER", "SUBJECT"});
      if(std::find(primary_keys.begin(), primary_keys.end(), key) != primary_keys.end()) return -1;
      
      sql = fmt::format("UPDATE QUESTIONS set {} = '{}' where ", key, custom_to_string(value));
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

string question_bank::getQuestion(optional<pair<string, variant<string, int, double>>> constraint, string primary_val){
   if(constraint){
      auto constraint_val = constraint.value();
      string key = constraint_val.first;
      auto value = constraint_val.second;
      sql = fmt::format("SELECT CONTENT FROM QUESTIONS "  \
                  "WHERE PATH = '{}' AND {} = '{}'; ", primary_val, key, custom_to_string(value));
   }
   else sql = fmt::format("SELECT CONTENT FROM QUESTIONS " \
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

string question_bank::getQuestionAttribute(optional<pair<string, variant<string, int, double>>> constraint, vector<pair<string, string>> primary_pairs, string target_attribute)
{
   if(constraint){
         auto constraint_val = constraint.value();
         string key = constraint_val.first;
         auto value = constraint_val.second;
         sql = fmt::format("SELECT {} FROM QUESTIONS WHERE {} = '{}' ", target_attribute, key, custom_to_string(value));
         for(int i=0; i<primary_pairs.size(); i++){
            sql += fmt::format("AND {} = '{}' ", primary_pairs[i].first, primary_pairs[i].second);
         }
   }
   else {
      sql = fmt::format("SELECT {} FROM QUESTIONS WHERE ", target_attribute);
      for(int i=0; i<primary_pairs.size(); i++) {
         if(i<primary_pairs.size()-1) sql += fmt::format("{} = '{}' AND ", primary_pairs[i].first, primary_pairs[i].second);
         else sql += fmt::format("{} = '{}' ", primary_pairs[i].first, primary_pairs[i].second);
      }
   }
   sql += "LIMIT 1; ";
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

int question_bank::count(){
   sql = "SELECT COUNT (*) from QUESTIONS LIMIT 1;"; 
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

int question_bank::countDistinct(const string target_attribute, vector<pair<string, string>> count_info) {
   sql = fmt::format("select count(DISTINCT {}) from QUESTIONS WHERE ", target_attribute);
   string constraint_key;
   string constraint_val;
   for(int i=0; i<count_info.size(); i++){
      constraint_key = count_info[i].first;
      constraint_val = count_info[i].second;
      if(i<count_info.size())  sql += fmt::format("{} = '{}' AND ", constraint_key, constraint_val);
   }
   sql += fmt::format("{} != 'placeholder' LIMIT 1;", target_attribute);
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

int question_bank::countDistinct(const string target_attribute, optional<pair<string, variant<string, int, double>>> count_info) {
   if(count_info){
      auto count_info_detail = count_info.value();
      string countKey = count_info_detail.first;
      auto countValue =  count_info_detail.second;
      //SELECT COUNT((SELECT DISTINCT path FROM QUESTIONS)) from QUESTIONS WHERE subject='English' and chapter='chapter1' LIMIT 1;
      sql = fmt::format("select count(DISTINCT {}) from QUESTIONS WHERE {}='{}' AND {} != 'placeholder' LIMIT 1;", target_attribute, countKey, custom_to_string(countValue), target_attribute);
   } else {
      sql = fmt::format("select count(DISTINCT {}) from QUESTIONS where {} != 'placeholder' LIMIT 1;", target_attribute, target_attribute);
   }
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

vector<string> question_bank::getQuestionPaths(){
   sql = "SELECT PATH from QUESTIONS;";
   sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
   sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
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
   return output;
}

int question_bank::delet(vector<pair<string, string>> primary_pairs){
   sql = fmt::format("DELETE from QUESTIONS where ");
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
   sql = "DROP TABLE IF EXISTS QUESTIONS;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table dropped successfully\n");
   }
}
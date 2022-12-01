#include "question_bank.hpp"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

question_bank::question_bank(){
   db = 0;
   stmt = 0;
   zErrMsg = 0;
   rc = 0;
   // sql = NULL;
}

question_bank::question_bank(const question_bank& database){

}

question_bank::~question_bank(){
   sqlite3_finalize(stmt);
   sqlite3_close(db);
}

void question_bank::create(bool clear/*= false*/, const char* database_name/*= "questions.db"*/){
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

   sql = "CREATE TABLE IF NOT EXISTS QUESTIONS( \
            PATH varchar(20) NOT NULL,  \
            CONTENT TEXT NOT NULL, \
            CATEGORY varchar(20) default undefined, \
            RUBRIC INTEGER CHECK(RUBRIC >= 0),\
            PRIMARY KEY (PATH, CONTENT)\
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

int question_bank::insert(QuestionInfo<string>& question){
   string path = question.path;
   string content = question.content;
   string category = question.category;
   int rubric = question.rubric;
   if(category.empty()) category = "undefined";
   sql = fmt::format("INSERT INTO QUESTIONS (PATH, CONTENT, CATEGORY, RUBRIC) "  \
            "VALUES ('{}', '{}', '{}', '{}'); SELECT * FROM QUESTIONS", path, content, category, rubric);
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

int question_bank::update(string primary_val, vector<pair<string, variant<string, int, double>>> changelist){
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
      
      if(key == "PATH") return -1;
      sql = fmt::format("UPDATE QUESTIONS set {} = '{}' where PATH = '{}'; SELECT * FROM QUESTIONS", key, custom_to_string(value), primary_val);

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

int question_bank::count(){
   sql = "SELECT COUNT (*) from QUESTIONS;"; 
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

int question_bank::delet(string primary_val, pair<string, variant<string, int, double>> authenticated_info){
   string key = authenticated_info.first;
   auto value = authenticated_info.second;
   sql = fmt::format("DELETE from QUESTIONS where PATH = '{}' AND {} = '{}'; \
                SELECT * from QUESTIONS", primary_val, key, custom_to_string(value));
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

// int main(int argc, char* argv[]) {
//    question_bank question = question_bank();
//    bool clear = true;
//    question.create(clear);

//    QuestionInfo<string> question_example = {path: "http://123.com", 
//                             content: "123456",
//                             category: "multiple choice",
//                             rubric: 10 
//                             };
//    question.insert(question_example);
//    string primekey_val = "http://123.com";

//    vector<pair<string, variant<string, int, double>>> changelist; // (key, value pair)
//    changelist.emplace_back("category", "normal");
//    changelist.emplace_back("category", "multiple choice");
//    int status = question.update(primekey_val, changelist);
//    cout<<"update status "<<status<<endl;

//    int question_num = question.count();
//    cout<<question_num<<endl;

//    optional<pair<string, variant<string, int, double>>> constraint;
//    // constraint = std::make_pair(db_key, identity_val);
//    string found = question.getQuestion(constraint, primekey_val);
//    cout<<"find status "<<found<<endl;

//    string key = "CONTENT";
//    auto val = static_cast<string>("123456");
//    pair<string, variant<string, int, double>> deleted_info = std::make_pair(key, "123456");

//    status = question.delet(primekey_val, deleted_info);
//    cout<<"delete status "<<status<<endl;
//    return 0;
// }
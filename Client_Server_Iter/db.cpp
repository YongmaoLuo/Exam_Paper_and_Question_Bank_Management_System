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

}

db_user::~db_user(){
    sqlite3_close(db);
}

void db_user::create(vector<UserInfo userinfo> users){
    rc = sqlite3_open("userinfo.db", &db);
   
    if(rc) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return(0);
    } else {
       fprintf(stdout, "Opened database successfully\n");
    }
    /* Create SQL statement */

    sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
}

void db_user::update(auto key, auto value){

}

bool db_user::find(auto key, auto value){
    return true;
}

void db_user::delet(auto key){

}

void db_user::drop(){
    fprintf(stderr, "SQL dropped: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
}
int main(int argc, char* argv[]) {

    db_user user = db_user();
   
   if(rc != SQLITE_OK){
      user.drop();
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   
   return 0;
}
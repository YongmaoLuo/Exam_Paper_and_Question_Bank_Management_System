#ifndef BULLETIN_HPP
#define BULLETIN_HPP
#include "database.hpp"
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


template<hashtable T>
struct BulletInfo {
        private:
            string path;
            string content;
            string teacher;
            int activity = 0; // no boolean inside sqlite
            int rubric;
        public:
            BulletInfo<T>(string path_, string content_, string teacher_): path(path_), content(content_), teacher(teacher_) {};
            QuestionInfo<T>(string path_, string content_, string teacher_, int rubric_): path(path_), content(content_),  teacher(teacher_), rubric(rubric_) {};
            std::tuple<string, string, T, int> getElements() const {return std::make_tuple(path, content, teacher, rubric);};
        };

class bulletinfo: public database {
    private:
        // sqlite3 *db;
        // sqlite3_stmt *stmt;
        char *zErrMsg;
        int rc;
        string sql;
        
    public:
        bulletinfo();
        bulletinfo(const bulletinfo& database);
        virtual ~bulletinfo(); //drop the table?

        void create(bool = false, const char* = "bulletin.db");
        int insert(std::shared_ptr<BulletInfo<string>>);
        int update(vector<pair<string, string>>, vector<pair<string, string>> changelist);

        string getBulletin(string primary_val);
        string readBulletin(string primary_val, string bulletinname);
        string writeBulletin(string primary_val, string bulletinname, string teacher, string text);

        int count();
        int delet(string primary_val, pair<string, string> deleted_info);
        void clean();
};
#endif
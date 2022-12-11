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
            T status;
            int activity = 0; // no boolean inside sqlite
        public:
            BulletInfo<T>(string path_, string content_, T category_): path(path_), content(content_), chapter(chapter_), category(category_), rubric(0) {};
            BulletInfo<T>(string path_, string content_, T category_, int rubric_): path(path_), content(content_), chapter(chapter_), category(category_), rubric(rubric_) {};
            std::tuple<string, string, string, T, int> getElements() const {return std::make_tuple(path, content, chapter, category, rubric);};
        };

class bulletinfo: public database {
    private:
        sqlite3 *db;
        sqlite3_stmt *stmt;
        char *zErrMsg;
        int rc;
        string sql;
        
    public:
        bulletinfo();
        bulletinfo(const bulletinfo& database);
        virtual ~bulletinfo(); //drop the table?

        void create(bool = false, const char* = "bulletin.db");
        int insert(bulletInfo<string>&);
        int update(string primary_val, vector<pair<string, variant<string, int, double>>> changelist);
        string getQuestion(optional<pair<string, variant<string, int, double>>> constraint, string primary_val);
        int count();
        vector<string> getQuestionPaths();
        int delet(string primary_val, pair<string, variant<string, int, double>> deleted_info);
        void clean();
};
#endif
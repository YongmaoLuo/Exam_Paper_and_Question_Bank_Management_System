#ifndef QUESTION_BANK_HPP
#define QUESTION_BANK_HPP
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <vector>
#include <set>
#include <variant>
#include <optional>
#include <iostream>
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


template <hashable T>
struct QuestionInfo{
            string path;
            string content;
            T category;
            int rubric;
        };

class question_bank{
    private:
        sqlite3 *db;
        sqlite3_stmt *stmt;
        char *zErrMsg;
        int rc;
        string sql;
        
    public:
        question_bank();
        question_bank(const question_bank& database);
        virtual ~question_bank(); //drop the table?

        void create(bool = false, const char* = "questions.db");
        int insert(QuestionInfo<string>&);
        int update(string primary_val, vector<pair<string, variant<string, int, double>>> changelist);
        string getQuestion(optional<pair<string, variant<string, int, double>>> constraint, string primary_val);
        int count();
        vector<string> getQuestionPaths();
        int delet(string primary_val, pair<string, variant<string, int, double>> deleted_info);
        void clean();
        void close();
};
#endif
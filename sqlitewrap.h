#ifndef SQLITEWRAP_H_INCLUDED
#define SQLITEWRAP_H_INCLUDED
//For more info on the SQLite3 API, visit http://www.sqlite.org/c3ref/intro.html!

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "data_base.h"
#include "sqlkeywords.h"

class SQLiteWrap : public SQLGenerator
{
public:
    SQLiteWrap(const char* file);
    int openConnection(const char* file);
    void closeConnection();
    int query(const std::string& query);
    std::vector<fuzzy_obj> GetResults() const;
    void ClearResults();
    ~SQLiteWrap();
private:
    sqlite3 *hDB; //Database handle!
    std::vector<fuzzy_obj> result;

    //private methods
    void log_error(int err);
};


#endif // SQLITEWRAP_H_INCLUDED

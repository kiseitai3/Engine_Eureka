#ifndef SQLITEWRAP_H_INCLUDED
#define SQLITEWRAP_H_INCLUDED
//For more info on the SQLite3 API, visit http://www.sqlite.org/c3ref/intro.html!

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "game.h"
#include "data_base.h"
#include "sqlkeywords.h"
#include "sqlite_error.h"
#include "sqlite_row.h"

class SQLiteWrap : public SQLGenerator, public SQLiteError
{
public:
    SQLiteWrap(const char* file);
    size_t openConnection(const char* file);
    size_t closeConnection();
    size_t query(const std::string& query);
    /*Getter methods. These methods are used to extract the result
    from the query. Each method calls the appropriate conversion
    function from the internal conversion API!*/
    void getResult(int& response, size_t col) const;
    void getResult(char& response, size_t col) const;
    void getResult(std::string& response, size_t col) const;
    void getResult(bool& response, size_t col) const;
    void getResult(double& response, size_t col) const;
    std::vector<fuzzy_obj> getResults() const;
    size_t getColCount();
    //Clearing methods
    void popRow();
    void popRows();
    void ClearResults();
    /*Ask for the validity of a database file!*/
    static bool isSQLiteDB(const char* file);
    ~SQLiteWrap();
private:
    sqlite3 *hDB; //Database handle!
    std::stack<SQLiteRow> result;
    /*The following stack is used to keep track of which rows are the results of which query statement!
    */
    std::stack<size_t> res_by_statement;
    size_t rowsPopped;


    //private methods
    size_t saveResult(sqlite3_stmt* stmt);
    size_t stepThroughRow(sqlite3_stmt* stmt);
};


#endif // SQLITEWRAP_H_INCLUDED

#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include "sqlitewrap.h"
#include <string>

//Engine name space macro
//ENGINE_NAMESPACE
class MySQL;

class DataBase : public SQLGenerator
{
public:
    DataBase(const char* file = "");
    void connect(const char* file);
    void disconnect();
    void query(const std::string& query);
    /*Getters*/
    void GetResult(int& response, size_t col = 0);
    void GetResult(size_t& response, size_t col = 0);
    void GetResult(char& response, size_t col = 0);
    void GetResult(bool& response, size_t col = 0);
    void GetResult(std::string& response, size_t col = 0);
    void GetResult(std::vector<fuzzy_obj>& response, size_t dataType);
    size_t GetDBType() const;
    bool isConnected() const;
    /*End of Getters*/
    ~DataBase();
private:
    SQLiteWrap* db_lite;
    MySQL* db;
    size_t db_type;
    bool connected;
};

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // DATABASE_H_INCLUDED

#include "database.h"
#include "data_base.h"

//Engine name space macro
//ENGINE_NAMESPACE


DataBase::DataBase(const char* file)
{
    db_lite = NULL;
    db = NULL;
    connect(file);
}

void DataBase::connect(const char* file)
{
    //variables
    std::string username, password, database, host;
    data_base dbDOM;
    //Make sure we are disconnected
    disconnect();
    //Let's see if the file is a valid SQLite Database. Otherwise, assume it's a settings file with the credentials
    //to access a MySQL Database!
    if(SQLiteWrap::isSQLiteDB(file))
        db_type = SQLITE;
    else
        db_type = MYSQL;

    //Now, let's open/connect the right database!
    switch(db_type)
    {
    case SQLITE:
        db_lite = new SQLiteWrap(file);
        connected = true;
        break;
    case MYSQL:
        dbDOM.OpenFile(file);//Open settings file with database credentials
        /*Load credentials!*/
        username = dbDOM.GetStrFromData("username");
        password = dbDOM.GetStrFromData("password");
        host = dbDOM.GetStrFromData("host");
        database = dbDOM.GetStrFromData("database");
        /*Create database*/
        db = new MySQL(database.c_str(), username.c_str(), password.c_str(), host.c_str());
        connected = true;
        break;
    }
}

void DataBase::disconnect()
{
    switch(db_type)
    {
    case SQLITE:
        if(db_lite)
            delete db_lite;
        db_lite = NULL;
        break;
    case MYSQL:
        if(db)
            delete db;
        db = NULL;
        break;
    }
}

void DataBase::query(const std::string& query)
{
    switch(db_type)
    {
    case SQLITE:
        db_lite->query(query);
        break;
    case MYSQL:
        db->queryDB(query);
    }
}

void DataBase::GetResult(bool& response, size_t col)
{
    switch(db_type)
    {
    case SQLITE:
        db_lite->getResult(response, col);
        break;
    case MYSQL:
        db->getResult(response);
        break;
    }
}

void DataBase::GetResult(int& response, size_t col)
{
    switch(db_type)
    {
    case SQLITE:
        db_lite->getResult(response, col);
        break;
    case MYSQL:
        db->getResult(response);
        break;
    }
}

void DataBase::GetResult(char& response, size_t col)
{
    switch(db_type)
    {
    case SQLITE:
        db_lite->getResult(response, col);
        break;
    case MYSQL:
        db->getResult(response);
        break;
    }
}

void DataBase::GetResult(std::string& response, size_t col)
{
    switch(db_type)
    {
    case SQLITE:
        db_lite->getResult(response, col);
        break;
    case MYSQL:
        db->getResult(response);
        break;
    }
}

void DataBase::GetResult(std::vector<fuzzy_obj>& response, size_t dataType)
{
    switch(db_type)
    {
    case SQLITE:
        response = db_lite->getResults();
        break;
    case MYSQL:
        response = db->getResults();
        break;
    }
}

size_t DataBase::GetDBType() const
{
    return db_type;
}

bool DataBase::isConnected() const
{
    return connected;
}

DataBase::~DataBase()
{
    disconnect();
}

//End of namespace macro
//ENGINE_NAMESPACE_END

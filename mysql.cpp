/*
    Copyright (C) 2014 Luis M. Santos
    Contact: luismigue1234@hotmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "mysql.h"


MySQL::cstr MySQL::DEFAULT_HOST = "localhost";
<<<<<<< HEAD
=======
const int MySQL::DEFAULT_COL_INDEX = 1;
>>>>>>> TheIllusiveMan

MySQL::MySQL(cstr database, cstr username, cstr password, cstr host)
{
    conn = NULL;
    driver = NULL;
    statement = NULL;
    res = NULL;
    if(!database || !username || !password)
<<<<<<< HEAD
        std::cout << "Warning: One or more pieces of information is missing. The program can't connect to the database without its name, "
=======
        std::cerr << "Warning: One or more pieces of information is missing. The program can't connect to the database without its name, "
>>>>>>> TheIllusiveMan
            << "username, or password! Optionally, a host name should be specified for remote databases! Please, make sure this "
            << "information is present!" << std::endl;
    else
        connect(database, username, password, host);
<<<<<<< HEAD
=======

>>>>>>> TheIllusiveMan
    status = false;//False = everything is fine
}

void MySQL::connect(cstr database, cstr username, cstr password, cstr host)
{
    try
    {
        /*Create a connection to MySQL! */
        driver = get_driver_instance();//Init driver
        conn = driver->connect(host, username, password);//connect to MySQL
        /*Connect to specific database within MySQL server.*/
        conn->setSchema(database);
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
    }
}

<<<<<<< HEAD
=======
void MySQL::reconnect(cstr database, cstr username, cstr password, cstr host)
{
    disconnect();
    connect(database, username, password, host);
}

>>>>>>> TheIllusiveMan
void MySQL::disconnect()
{
    try
    {
        if(res)
            delete res;
        if(statement)
            delete statement;
        delete conn;
        conn = NULL;
        res = NULL;
        statement = NULL;
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
    }
}

<<<<<<< HEAD
void MySQL::queryDB(const std::string& query)
=======
void MySQL::queryDB(const std::string& query, bool clearRes)
>>>>>>> TheIllusiveMan
{
    try
    {
        /*Let's check if a previous instance of statement exists*/
        if(statement)
            delete statement;//Clean it in preparation for the new query!
        statement = NULL;
        /*Let's set up an instance of statement!*/
        statement = conn->createStatement();
        //Reset results
<<<<<<< HEAD
        CleanResults();
=======
        if(clearRes)
           CleanResults();
>>>>>>> TheIllusiveMan
        //Execute query and get results!
        res = statement->executeQuery(query);
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
    }
}

void MySQL::CleanResults()
{
    try
    {
<<<<<<< HEAD
        if(res)
            delete res;
=======
        if(res){
            delete res;
         }
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
    }
}

bool MySQL::hasResults()
{
    try
    {
        if(!res)
        {
            std::cerr << "Error: the table does not exist in the current database!"
            << " Check your syntax!" << std::endl;
            return false;
        }
       else{
            return res->rowsCount();
         }
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
        return false;
    }
}

size_t MySQL::rowCount()
{
    try
    {
        if(res){
            return res->rowsCount();
         }
	return 0;
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
    }

}

bool MySQL::validConnection(const std::string& query)
{
    try
    {
       /*Let's check if a previous instance of statement exists*/
        if(statement)
            delete statement;//Clean it in preparation for the new query!
        statement = NULL;
        /*Let's set up an instance of statement!*/
        statement = conn->createStatement();
        //Execute query and get results!
        sql::ResultSet *tmp_res = statement->executeQuery(query);
        if(tmp_res)
           delete tmp_res;
        return true;
>>>>>>> TheIllusiveMan
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
<<<<<<< HEAD
=======
        return false;
>>>>>>> TheIllusiveMan
    }
}

void MySQL::error_log(sql::SQLException& err)
{
<<<<<<< HEAD
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line "
    << __LINE__ << std::endl;
    std::cout << "# ERR: " << err.what();
    std::cout << " (MySQL error code: " << err.getErrorCode();
    std::cout << ", SQLState: " << err.getSQLState() << " )" << std::endl;
    //Raise the status flag!
    status = true; //Things are bad!
=======
    std::cerr << "# ERR: SQLException in " << __FILE__;
    std::cerr << "(" << __FUNCTION__ << ") on line "
    << __LINE__ << std::endl;
    std::cerr << "# ERR: " << err.what();
    std::cerr << " (MySQL error code: " << err.getErrorCode();
    std::cerr << ", SQLState: " << err.getSQLState() << " )" << std::endl;
    //Raise the status flag!
    status = true; //Things are bad!
    res = NULL;
>>>>>>> TheIllusiveMan
}

bool MySQL::getStatus() const
{
    return status;
}

<<<<<<< HEAD
void MySQL::ClearStatus()
{
    status = false;
}

void MySQL::getResult(bool& response)
=======
void MySQL::getResult(bool& response, const std::string& col_name)
>>>>>>> TheIllusiveMan
{
    bool tmp;
    try
    {
<<<<<<< HEAD
        tmp = res->getBoolean("_reply");
=======
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getBoolean(col_name);
>>>>>>> TheIllusiveMan
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }
    response = tmp;
}

<<<<<<< HEAD
void MySQL::getResult(int& response)
=======
void MySQL::getResult(int& response, const std::string& col_name)
>>>>>>> TheIllusiveMan
{
    int tmp;
    try
    {
<<<<<<< HEAD
        tmp = res->getInt("_reply");
=======
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getInt(col_name);
>>>>>>> TheIllusiveMan
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

<<<<<<< HEAD
void MySQL::getResult(std::string& response)
=======
void MySQL::getResult(std::string& response, const std::string& col_name)
>>>>>>> TheIllusiveMan
{
    std::string tmp;
    try
    {
<<<<<<< HEAD
        tmp = res->getString("_reply");
=======
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getString(col_name);
>>>>>>> TheIllusiveMan
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

<<<<<<< HEAD
void MySQL::getResult(char& response)
=======
void MySQL::getResult(char& response, const std::string& col_name)
>>>>>>> TheIllusiveMan
{
    char tmp;
    try
    {
<<<<<<< HEAD
        tmp = res->getString("_reply")[0];
=======
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getString(col_name)[0];
>>>>>>> TheIllusiveMan
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

<<<<<<< HEAD
std::vector<fuzzy_obj> MySQL::getResults(size_t dataType)
{
    std::vector<fuzzy_obj> resList;//Place holder
    while(res->next())
    {
        fuzzy_obj tmp;
        switch(dataType)
        {
        case INT:
            getResult(tmp.number);
            break;
        case DOUBLE:
            getResult(tmp.decimal);
            break;
        case STRING:
            getResult(tmp.str);
            break;
        case BOOL:
            getResult(tmp.answer);
            break;
        case CHAR:
            getResult(tmp.c);
            break;
        default:
            std::cout << "Error: MySQL object was asked to prepare a list of results, but the type specified is incorrect! ";
            std::cout << "Error in getResults()." << std::endl;
        }
        resList.push_back(tmp);//Add result to the list
    }
    return resList; //Return the list of results
}

void MySQL::getResult(double& response)
=======
void MySQL::getResult(double& response, const std::string& col_name)
{
    double tmp;
    try
    {
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getDouble(col_name);
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

void MySQL::getResult(bool& response, size_t col_index)
{
    bool tmp;
    try
    {
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getBoolean(col_index);
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }
    response = tmp;
}

void MySQL::getResult(int& response, size_t col_index)
{
    int tmp;
    try
    {
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getInt(col_index);
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

void MySQL::getResult(std::string& response, size_t col_index)
{
    std::string tmp;
    try
    {
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getString(col_index);
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

void MySQL::getResult(char& response, size_t col_index)
{
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
    char tmp;
    try
    {
        tmp = res->getString(col_index)[0];
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

void MySQL::getResult(double& response, size_t col_index)
>>>>>>> TheIllusiveMan
{
    double tmp;
    try
    {
<<<<<<< HEAD
        tmp = res->getDouble("_reply");
=======
        if(!res || !res->next())
        {
            std::cerr << "Error: Either the resultset is empty or something is wrong with the query string!"
            << " No results were obtained from the previous query!" << std::endl;
            return;
        }
        tmp = res->getDouble(col_index);
>>>>>>> TheIllusiveMan
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

<<<<<<< HEAD
=======
std::vector<fuzzy_obj> MySQL::getResults()
{
    fuzzy_obj tmp;
    std::vector<fuzzy_obj> results;
    for(size_t i = 0; i < rowCount(); i++)
    {
        getResult(tmp.blob);
        tmp.flag = 'l';
        results.push_back(tmp);
    }
    return results;
}

>>>>>>> TheIllusiveMan
MySQL::~MySQL()
{
    disconnect();
    CleanResults();
    if(conn)
        delete conn;

}

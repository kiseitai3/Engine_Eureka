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

MySQL::MySQL(cstr database, cstr username, cstr password, cstr host)
{
    conn = NULL;
    driver = NULL;
    statement = NULL;
    res = NULL;
    if(!database || !username || !password)
        std::cout << "Warning: One or more pieces of information is missing. The program can't connect to the database without its name, "
            << "username, or password! Optionally, a host name should be specified for remote databases! Please, make sure this "
            << "information is present!" << std::endl;
    else
        connect(database, username, password, host);
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

void MySQL::queryDB(const std::string& query)
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
        CleanResults();
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
        if(res)
            delete res;
    }
    catch(sql::SQLException& e)
    {
        error_log(e);
    }
}

void MySQL::error_log(sql::SQLException& err)
{
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line "
    << __LINE__ << std::endl;
    std::cout << "# ERR: " << err.what();
    std::cout << " (MySQL error code: " << err.getErrorCode();
    std::cout << ", SQLState: " << err.getSQLState() << " )" << std::endl;
    //Raise the status flag!
    status = true; //Things are bad!
}

bool MySQL::getStatus() const
{
    return status;
}

void MySQL::ClearStatus()
{
    status = false;
}

void MySQL::getResult(bool& response)
{
    bool tmp;
    try
    {
        tmp = res->getBoolean("_reply");
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }
    response = tmp;
}

void MySQL::getResult(int& response)
{
    int tmp;
    try
    {
        tmp = res->getInt("_reply");
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

void MySQL::getResult(std::string& response)
{
    std::string tmp;
    try
    {
        tmp = res->getString("_reply");
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

void MySQL::getResult(char& response)
{
    char tmp;
    try
    {
        tmp = res->getString("_reply")[0];
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

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
{
    double tmp;
    try
    {
        tmp = res->getDouble("_reply");
    }
    catch (sql::SQLException& e)
    {
        error_log(e);
    }

    response = tmp;
}

MySQL::~MySQL()
{
    disconnect();
    CleanResults();
    if(conn)
        delete conn;

}

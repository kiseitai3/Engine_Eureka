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
#ifndef MYSQL_H_INCLUDED
#define MYSQL_H_INCLUDED

#include <iostream>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "sqlkeywords.h"


class MySQL : public SQLGenerator
{
public:
    typedef const char* cstr;
    static cstr DEFAULT_HOST;
    MySQL(cstr database = NULL, cstr username = NULL, cstr password = NULL, cstr host = MySQL::DEFAULT_HOST);
    /*Connection methods*/
    void connect(cstr database, cstr username, cstr password, cstr host);
    void disconnect();
    void queryDB(const std::string& query);
    void CleanResults();
    void ClearStatus();
    /*Getter methods. These methods are used to extract the result
    from the query. Each method calls the appropriate conversion
    function from the MySQL API!*/
    void getResult(int& response);
    void getResult(char& response);
    void getResult(std::string& response);
    void getResult(bool& response);
    void getResult(double& response);
    /*Status of the class.*/
    bool getStatus() const;
    ~MySQL();
private:
    bool status;
    sql::Connection* conn;
    sql::Driver* driver;
    sql::ResultSet* res;
    sql::Statement* statement;

    //methods
    void error_log(sql::SQLException& err);// This method outputs the specific error.
};

#endif // MYSQL_H_INCLUDED

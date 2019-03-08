#define UTF8_NEEDED
#include "sqlitewrap.h"
#include "conversion.h"
<<<<<<< HEAD
=======
#include <cstdlib>

//Engine name space macro
//ENGINE_NAMESPACE

>>>>>>> TheIllusiveMan

SQLiteWrap::SQLiteWrap(const char* file)
{
    hDB = NULL;
    rowsPopped = 0;
    openConnection(file);//Create a connection
}

size_t SQLiteWrap::openConnection(const char* file)
{
    //Attempt to open a connection and return the result code. Also, as a just in case, log this error into standard output!
    size_t err = sqlite3_open(file, &hDB);
<<<<<<< HEAD
    log_error(err, hDB);
=======
    if(isError(err))
    {
        log_error(err, hDB);
    }
>>>>>>> TheIllusiveMan
    return err;
}

size_t SQLiteWrap::closeConnection()
{
    //Attempt to close the connection, log the result, and return the result code
    size_t err = sqlite3_close(hDB);
<<<<<<< HEAD
    log_error(err, hDB);
=======
    if(isError(err))
    {
        log_error(err, hDB);
    }
>>>>>>> TheIllusiveMan
    return err;
}

size_t SQLiteWrap::query(const std::string& query)
{
    //Attempt to query the database, log the result, and return the result code
    //First, I build a byte-code statement
    sqlite3_stmt* stmt = NULL;
    const char* tail = NULL;
    size_t err = 0;
    std::string utf8 = convertASCIItoUTF8(query);//Make sure the string is in UTF-8!

    //Clean the result place holder
    ClearResults();
    //Begin queries.
    do
    {
        err = sqlite3_prepare_v2(hDB, utf8.c_str(), utf8.size(), &stmt, &tail);
        //Let's log the result of the statement if an error has ocurred!
<<<<<<< HEAD
        if(err)
=======
        if(isError(err))
>>>>>>> TheIllusiveMan
        {
            log_error(err, hDB);
            return err;
        }
        //Let's query the database and save the results!
        err = stepThroughRow(stmt);
<<<<<<< HEAD
        if(err)
=======
        if(isError(err))
>>>>>>> TheIllusiveMan
        {
            log_error(err, hDB);
            return err;
        }

        //Let's cleanup the statement
        err = sqlite3_finalize(stmt);
<<<<<<< HEAD
        if(err)
=======
        if(isError(err))
>>>>>>> TheIllusiveMan
        {
            log_error(err, hDB);
            return err;
        }
        res_by_statement.push(result.size());
        utf8 = tail;
<<<<<<< HEAD
    }while(tail);//Keep processing the query until no statements are left!
=======
    }
    while(std::string(tail).size() > 0); //Keep processing the query until no statements are left!
>>>>>>> TheIllusiveMan

    //Let's reverse the stack
    result = reverseStackOrder(result);
    res_by_statement = reverseStackOrder(res_by_statement);

    //Finally, let the caller obtain a copy of the result code!
    return err;
}

void SQLiteWrap::getResult(int& response, size_t col) const
{
    fuzzy_obj tmp = result.top().GetResultFromCol(col);
    if(tmp.flag == 'i')//Check type
    {
        response = tmp.number;
<<<<<<< HEAD
    }
    response = std::string::npos;
=======
        return;
    }
    response = convert(tmp).number;
>>>>>>> TheIllusiveMan
}

void SQLiteWrap::getResult(char& response, size_t col) const
{
    fuzzy_obj tmp = result.top().GetResultFromCol(col);
    if(tmp.flag == 's')//Check type
    {
        response = tmp.str[0];
<<<<<<< HEAD
    }
    response = '\0';
=======
        return;
    }
    response = convert(tmp).c;
>>>>>>> TheIllusiveMan
}

void SQLiteWrap::getResult(std::string& response, size_t col) const
{
    fuzzy_obj tmp = result.top().GetResultFromCol(col);
<<<<<<< HEAD
    if(tmp.flag == 's' || tmp.flag == 'l')//Check type
    {
        response = tmp.str;
=======
    if(tmp.flag == 's')//Check type
    {
        response = tmp.str;
        return;
>>>>>>> TheIllusiveMan
    }
    else if(tmp.flag == 'l')//Check type
    {
        response = tmp.blob;
<<<<<<< HEAD
    }
    response = "";
=======
        return;
    }
    response = convert(tmp).str;
>>>>>>> TheIllusiveMan
}

void SQLiteWrap::getResult(bool& response, size_t col) const
{
    fuzzy_obj tmp = result.top().GetResultFromCol(col);
    if(tmp.flag == 'i')//Check type
    {
        response = tmp.number;
<<<<<<< HEAD
    }
    response = std::string::npos;
=======
        return;
    }
    response = convert(tmp).answer;
>>>>>>> TheIllusiveMan
}

void SQLiteWrap::getResult(double& response, size_t col) const
{
    fuzzy_obj tmp = result.top().GetResultFromCol(col);
    if(tmp.flag == 'd')//Check type
    {
        response = tmp.decimal;
<<<<<<< HEAD
    }
    response = std::string::npos;
}

std::vector<fuzzy_obj> SQLiteWrap::getResults() const
=======
        return;
    }
    response = convert(tmp).decimal;
}

std::vector<fuzzy_obj> SQLiteWrap::getResults()
>>>>>>> TheIllusiveMan
{
    size_t rowCount = res_by_statement.top() - rowsPopped;
    std::vector<fuzzy_obj> tmp;//Where we temporarily save the individual objects.
    while(rowCount--)
    {
        SQLiteRow row = result.top();
        tmp.reserve(tmp.size() + row.GetNumCol());
        tmp.insert(tmp.end(), row.GetFullRow().begin(), row.GetFullRow().end());
<<<<<<< HEAD
=======
        result.pop();
>>>>>>> TheIllusiveMan
    }
    return tmp;
}

void SQLiteWrap::popRows()
{
    //This method deletes the full results from the top statement!
    size_t size = res_by_statement.top() + rowsPopped;
    while(size--)
    {
        //pop rows!
        result.pop();
    }
}

size_t SQLiteWrap::getColCount()
{
    return result.top().GetNumCol();
}

void SQLiteWrap::popRow()
{
    result.pop();
    rowsPopped++;
}

size_t SQLiteWrap::saveResult(sqlite3_stmt* stmt)
{
    //Check stmt is a valid pointer!
    if(!stmt)
        return SQLITE_ABORT;

    SQLiteRow row;
<<<<<<< HEAD
    for(int i = 0; i < sqlite3_column_count(stmt); i++)
=======
    size_t count = sqlite3_column_count(stmt);
    for(int i = 0; i < count; i++)
>>>>>>> TheIllusiveMan
    {
        fuzzy_obj s_result;//Now, let's allocate memory for the result
        s_result.flag = 'n';
        //Let's ask the SQLite engine what is the type of the result.
        switch(sqlite3_column_type(stmt, i))
        {
        /*Now, we store the result with its proper data type into our fuzzy object structure*/
        case SQLITE_INTEGER:
            s_result.number = sqlite3_column_int(stmt, i);
            s_result.flag = 'i';
            break;
        case SQLITE_FLOAT:
            s_result.decimal = sqlite3_column_double(stmt, i);
            s_result.flag = 'd';
            break;
        case SQLITE_TEXT:
<<<<<<< HEAD
            s_result.str = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            s_result.flag = 's';
            break;
        case SQLITE_BLOB:
            s_result.str = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            s_result.flag = 'l';
            break;
        default:
            std::cerr << "Error: The SQLite interface received an unexpected data type code from the SQLite engine!"
                    << std::endl;
=======
            s_result.str = (const char*)(sqlite3_column_text(stmt, i));
            s_result.flag = 's';
            break;
        case SQLITE_BLOB:
            s_result.blob = (const char*)sqlite3_column_text(stmt, i);
            s_result.flag = 'l';
            break;
        case SQLITE_NULL:
            s_result.str = "End of SQLite row!";
            s_result.flag = 's';
            break;
        default:
            std::cerr << "Error: The SQLite interface received an unexpected data type code from the SQLite engine!"
                      << " Type requested: " << sqlite3_column_type(stmt, i) << std::endl;
>>>>>>> TheIllusiveMan
        }
        //Now, we add the result to the row.
        row.insertCol(s_result);
    }

    //Once the row is built, we push it to the stack!
    result.push(row);
    return SQLITE_OK;
}

void SQLiteWrap::ClearResults()
{
    while(result.size())
    {
        result.pop();
    }
}

size_t SQLiteWrap::stepThroughRow(sqlite3_stmt* stmt)
{
    //Check stmt is a valid pointer!
    if(!stmt)
        return SQLITE_ABORT;

<<<<<<< HEAD
    size_t err = 0;
    do
    {
        //Step through each row and log any errors
        err = sqlite3_step(stmt);
        if(err)
=======
    size_t err = sqlite3_step(stmt);
    while(err == SQLITE_ROW)
    {
        if(isError(err))
>>>>>>> TheIllusiveMan
        {
            log_error(err, hDB);
            return err;
        }
        //Let's save the returned data!
        saveResult(stmt);
<<<<<<< HEAD
    }while(err == SQLITE_ROW);
    return err;
}

=======
        //Step through each row and log any errors
        err = sqlite3_step(stmt);
    }
    return err;
}

bool SQLiteWrap::isSQLiteDB(const char* file)
{
    sqlite3* DB;
    int err = sqlite3_open(file, &DB);
    if(err == SQLITE_OK)//See if the database engine opened the file without issues
    {
        sqlite3_close(DB);//Close the database
        return true;
    }

    sqlite3_close(DB);//Close the database
    return false;
}

bool SQLiteWrap::isError(size_t err) const
{
    if(err >= SQLITE_ROW || err == SQLITE_OK)
        return false;
    return true;
}

void SQLiteWrap::printRows()
{
    while(!result.empty())
    {
        SQLiteRow row = result.top();
        for(size_t i = 0; i < row.GetNumCol(); i++)
        {
            fuzzy_obj tmp = row.GetResultFromCol(i);
            std::cout << "Result type: " << tmp.flag << std::endl;
            switch(tmp.flag)
            {
            case 's':
                std::cout << "Result data: " << tmp.str << std::endl;
                break;
            case 'i':
                std::cout << "Result data: " << tmp.number << std::endl;
                break;
            case 'd':
                std::cout << "Result data: " << tmp.decimal << std::endl;
                break;
            case 'l':
                std::cout << "Result data: " << tmp.blob << std::endl;
                break;
            }
        }

        result.pop();
    }
}

>>>>>>> TheIllusiveMan
SQLiteWrap::~SQLiteWrap()
{
    closeConnection();
}
<<<<<<< HEAD
=======

fuzzy_obj convert(const fuzzy_obj& src)
{
    fuzzy_obj tmp;

    switch(src.flag)
    {
    case 'i':
    {
        tmp.answer = (bool)src.number;
        tmp.str = intToStr(src.number);
        tmp.decimal = (double)src.number;
        tmp.uNumber = (size_t)src.number;
        tmp.c = (char)src.number;
        break;
    }
    case 'd':
    {
        tmp.answer = (bool)tmp.decimal;
        tmp.str = numToStr(tmp.decimal);
        tmp.number = numToInt(tmp.decimal);
        tmp.uNumber = (size_t)tmp.decimal;
        tmp.c = (char)numToInt(tmp.decimal);
        break;
    }
    case 's':
    {
        tmp.answer = (bool)atoi(src.str.c_str());
        tmp.number = atoi(src.str.c_str());
        tmp.decimal = atof(src.str.c_str());
        tmp.uNumber = (size_t)atoi(src.str.c_str());
        tmp.c = (char)atoi(src.str.c_str());
        break;
    }
    case 'b':
    {
        tmp.str = intToStr(src.answer);
        tmp.number = (int)src.answer;
        tmp.decimal = (double)src.answer;
        tmp.uNumber = (size_t)src.answer;
        tmp.c = (char)src.answer;
        break;
    }
    case 'c':
    {
        tmp.answer = (bool)src.c;
        tmp.number = (int)src.c;
        tmp.decimal = (double)src.c;
        tmp.uNumber = (size_t)src.c;
        tmp.str = intToStr((src.c));
        break;
    }
    }

    return tmp;
}

//End of namespace macro
//ENGINE_NAMESPACE_END
>>>>>>> TheIllusiveMan

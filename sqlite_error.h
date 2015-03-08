#ifndef SQLITE_ERROR_H_INCLUDED
#define SQLITE_ERROR_H_INCLUDED

#include <sqlite3.h>
#include <iostream>
#include "typedefs.h"


//Engine name space macro
//ENGINE_NAMESPACE


typedef sqlite3* sqlite3_ptr;

struct SQLiteError
{
    static sqlite3_ptr NULL_SQLITE3_PTR;
    void log_error(size_t error, sqlite3_ptr& dbHandle = NULL_SQLITE3_PTR);
    void printNotice();
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // SQLITE_ERROR_H_INCLUDED

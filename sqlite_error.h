#ifndef SQLITE_ERROR_H_INCLUDED
#define SQLITE_ERROR_H_INCLUDED

#include <sqlite3.h>
#include <iostream>
<<<<<<< HEAD
=======
#include "typedefs.h"


//Engine name space macro
//ENGINE_NAMESPACE

>>>>>>> TheIllusiveMan

typedef sqlite3* sqlite3_ptr;

struct SQLiteError
{
    static sqlite3_ptr NULL_SQLITE3_PTR;
    void log_error(size_t error, sqlite3_ptr& dbHandle = NULL_SQLITE3_PTR);
    void printNotice();
};


<<<<<<< HEAD
=======
//End of namespace macro
//ENGINE_NAMESPACE_END
>>>>>>> TheIllusiveMan
#endif // SQLITE_ERROR_H_INCLUDED

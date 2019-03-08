#include "sqlite_error.h"

<<<<<<< HEAD
=======
//Engine name space macro
//ENGINE_NAMESPACE


>>>>>>> TheIllusiveMan
sqlite3_ptr SQLiteError::NULL_SQLITE3_PTR = NULL;

void SQLiteError::log_error(size_t err, sqlite3_ptr& dbHandle)
{
    size_t errNumber = 0;
    //First, we check what kind of result code we have and output the appropriate message!
    switch(err)
    {
    case SQLITE_OK:
        std::cerr << "Notice: the connection to the database was successful or the operation ocurred without issues!" << std::endl;
        break;
    case SQLITE_IOERR:
    case SQLITE_CANTOPEN:
        std::cerr << "Error: Can't access database! An I/O error probably occurred or the file is missing!" << std::endl;
        std::cerr << "This error may have ocurred while attempting to read or write the database." << std::endl;
<<<<<<< HEAD
    case SQLITE_ERROR:
        std::cerr << "Error: An internal error ocurred in the SQlite engine!" << std::endl;
        std::cerr << "Hint: Something got really f'ed up if you are getting this error!" << std::endl;
    case SQLITE_PERM:
        std::cerr << "Error: Requested access mode for a newly created database could not be provided." << std::endl;
=======
        break;
    case SQLITE_ERROR:
        std::cerr << "Error: An internal error ocurred in the SQlite engine!" << std::endl;
        std::cerr << "Hint: Something got really f'ed up if you are getting this error!" << std::endl;
        break;
    case SQLITE_PERM:
        std::cerr << "Error: Requested access mode for a newly created database could not be provided." << std::endl;
        break;
>>>>>>> TheIllusiveMan
    case SQLITE_BUSY:
        std::cerr << "Error: the database file could not be written (or in some cases read) because of";
        std::cerr << " concurrent activity by some other database connection, usually a database ";
        std::cerr << "connection in a separate process." << std::endl;
<<<<<<< HEAD
    case SQLITE_ABORT:
    case SQLITE_INTERRUPT:
        std::cerr << "An operation was aborted prior to completion, usually by application request." << std::endl;
=======
        break;
    case SQLITE_ABORT:
    case SQLITE_INTERRUPT:
        std::cerr << "An operation was aborted prior to completion, usually by application request." << std::endl;
        break;
>>>>>>> TheIllusiveMan
    case SQLITE_LOCKED:
        std::cerr << "a write operation could not continue because of a conflict within the same";
        std::cerr << " database connection or a conflict with a different database connection that uses a shared cache.";
        std::cerr << std::endl;
<<<<<<< HEAD
    case SQLITE_NOMEM:
        std::cerr << "SQLite was unable to allocate all the memory it needed to complete the operation." << std::endl;
    case SQLITE_READONLY:
        std::cerr << "An attempt is made to alter some data for which the current database connection ";
        std::cerr << "does not have write permission." << std::endl;
    case SQLITE_CORRUPT:
        std::cerr << "The database file has been corrupted." << std::endl;
    case SQLITE_FULL:
        std::cerr << "A write operation could not complete because the disk is full." << std::endl;
=======
        break;
    case SQLITE_NOMEM:
        std::cerr << "SQLite was unable to allocate all the memory it needed to complete the operation." << std::endl;
        break;
    case SQLITE_READONLY:
        std::cerr << "An attempt is made to alter some data for which the current database connection ";
        std::cerr << "does not have write permission." << std::endl;
        break;
    case SQLITE_CORRUPT:
        std::cerr << "The database file has been corrupted." << std::endl;
        break;
    case SQLITE_FULL:
        std::cerr << "A write operation could not complete because the disk is full." << std::endl;
        break;
>>>>>>> TheIllusiveMan
    default:
        std::cerr << "I did not write or copied error messages for all error codes from SQLite!";
        std::cerr << " As a result, all codes without explicit error messages will only output its value!";
        std::cerr << " You can read about the specific error from the SQLite documentation!";
        std::cerr << std::endl << std::endl << "The error code is: " << err << std::endl;
    }

    if(dbHandle)//Let's check if the caller wants to output a more specific error message.
    {
        errNumber = sqlite3_extended_errcode(dbHandle);
        std::cerr << std::endl << "Extended Error code is: " << errNumber << std::endl;
        std::cerr << sqlite3_errmsg(dbHandle) << std::endl;;
    }
}

void SQLiteError::printNotice()
{
    std::cout << "The user of SQLiteError requested to print the following notice: " << std::endl;
    std::cout << "All error codes outputed by the application during its database operations can ";
    std::cout << "be found in the SQLite3 documentation. You may find the documentation webpage useful!";
    std::cout << "The page is located at http://www.sqlite.org/rescode.html." << std::endl;
}
<<<<<<< HEAD
=======

//End of namespace macro
//ENGINE_NAMESPACE_END
>>>>>>> TheIllusiveMan

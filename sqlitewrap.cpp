#include "sqlitewrap.h"

SQLiteWrap::SQLiteWrap(const char* file)
{
    hDB = NULL;
    log_error(sqlite3_open(file, &hDB));

}

void SQLiteWrap::log_error(int err)
{
    int errNumber = 0;
    switch(err)
    {
    case SQLITE_OK:
        std::cout << "Notice: the connection to the data base was successful!" << std::endl;
        break;
    case SQLITE_IOERR:
        errNumber = sqlite3_extended_errcode(hDB);
        std::cout << "Error: Can't access database!" << std::endl;
        std::cout << "";
    default:
        std::cout << "Error";
    }
}

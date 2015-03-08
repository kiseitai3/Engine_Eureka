#ifndef SQLITE_ROW_H_INCLUDED
#define SQLITE_ROW_H_INCLUDED

#include <vector>
#include <iostream>
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class SQLiteRow
{
public:
    fuzzy_obj GetResultFromCol(size_t col) const;
    std::vector<fuzzy_obj> GetFullRow() const;
    void insertCol(fuzzy_obj col);
    size_t GetNumCol() const;
    void CleanData();
private:
    std::vector<fuzzy_obj> row;
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // SQLITE_ROW_H_INCLUDED

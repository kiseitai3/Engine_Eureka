#include "sqlite_row.h"

fuzzy_obj SQLiteRow::GetResultFromCol(size_t col) const
{
    return row[col];
}

std::vector<fuzzy_obj> SQLiteRow::GetFullRow() const
{
    return row;
}

void SQLiteRow::insertCol(fuzzy_obj col)
{
    row.push_back(col);
}

size_t SQLiteRow::GetNumCol() const
{
    return row.size();
}

void SQLiteRow::CleanData()
{
    row.clear();
}

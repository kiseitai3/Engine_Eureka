#include <iostream>
#include <string>
#include "../sqlitewrap.h"

int main()
{
    int res;

    SQLiteWrap db("save");

    std::cout << "Is the database a valid SQLite3 database? " << std::endl;
    std::cout << (SQLiteWrap::isSQLiteDB("save") ? "Yes" : "No") << std::endl;
    std::cout << "Connecting to database..." << std::endl;
    std::string query = db.prepareStatement("UserAccount", "email", "username='pandora'","","",SELECT|WHERE);
    std::cout << "Query: " << query << std::endl;
    std::string email;
    std::cout << "Querying database!" << std::endl;
    db.query(query);
    std::cout << "Printing contents!" << std::endl;
    db.printRows();
    std::cout << "Querying database!" << std::endl;
    db.query(query);
    std::cout << "Obtaining results!" << std::endl;
    db.getResult(email, 0);
    std::cout << "Email: " << email << std::endl;
    std::cin >> res;
    return 0;
}

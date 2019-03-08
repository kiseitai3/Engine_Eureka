#include <iostream>
#include <string>
#include <vector>
#include "../database.h"

int main()
{
    int res;
    DataBase db("save");
    std::string query = db.prepareStatement("UserAccount", "email", "username='pandora'","","",SELECT|WHERE);
    std::string result;
    std::cout << "Is database connected? " << (db.isConnected() ? "Yes" : "No") << std::endl;
    db.query(query);
    db.GetResult(result, 0);
    std::cout << "The email for pandora is: " << result << std::endl;

    std::cin >> res;
    return 0;
}

#include <iostream>
#include <vector>
#include "../data_base.h"

/*This class is highly tested since my thesis project and open source project.
What I am testing here is mostly the new feature of loading a file by passing
a const char pointer that is tagged with the buffer directive. Normally, passing
the const char* to the constructor meant passing a file path, but the new feature
allows loading a file by passing the the contents from a memory buffer!*/
int main()
{
    std::string contents = data_base::BUFFER;
     contents += "test = 1; test2 = 2.1; test3 = Hello World!;\0";
     std::string buff = "test = ;\ntest2 = ;\ntest3 = ;\n\0";
    data_base tmp(contents.c_str());
    data_base::CreateNewFile_static("test_data.txt");
    data_base writer("test_data.txt", false);

    //Let's display contents
    std::cout << "Displaying contents of virtual file!" << std::endl;
    std::cout << tmp.GetIntFromData("test") << std::endl;
    std::cout << tmp.GetValueFromData("test2") << std::endl;
    std::cout << tmp.GetStrFromData("test3") << std::endl;

    //Let's write contents to a test file
    std::cout << "Dumping virtual file into real file!" << std::endl;
    writer.WriteValue(buff);
    writer.WriteValue(intToStr(tmp.GetIntFromData("test")), "test");
    writer.WriteValue(numToStr(tmp.GetValueFromData("test2")), "test2");
    writer.WriteValue(tmp.GetStrFromData("test3"), "test3");
    writer.CloseFile();

    //Let's read and display the contents of this file
    std::cout << "===============Reading real test file and displaying contents! Data should match what was displayed!===============" << std::endl;
    tmp.CloseFile();
    tmp.OpenFile("test_data.txt", true);
    std::cout << tmp.GetIntFromData("test") << std::endl;
    std::cout << tmp.GetValueFromData("test2") << std::endl;
    std::cout << tmp.GetStrFromData("test3") << std::endl;
    std::cout << "End of test!" << std::endl;

    return 0;
}

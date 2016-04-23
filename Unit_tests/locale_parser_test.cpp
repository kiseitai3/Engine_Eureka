#include "../localesystem.h"
#include "../data_base.h"

#include <iostream>
#include <string>


int main()
{
    std::string locale_path, target_file, path, output;
    char operation;
    LocaleReader* locale_reader;

    std::cout << "Path to locale file:" << std::endl;
    std::cin >> locale_path;
    std::cout << locale_path << std::endl;
    std::cout << "Filepath of the file you wish to process!" << std::endl;
    std::cin >> target_file;
    std::cout << target_file << std::endl;
    std::cout << "What do you want to do? (C for condense, E for expand)" << std::endl;
    std::cin >> operation;


    //operation = capitalizeChar(operation);
    path = (target_file + ".out");
    if(operation == 'E')
    {
        locale_reader = new LocaleReader(locale_path.c_str());
        std::cout << "Using locale: " << locale_reader->GetLocaleName() << std::endl;
        data_base::CreateNewFile_static(path.c_str());
        data_base f(path.c_str(), false);
        data_base fin(target_file.c_str());
        output = fin.GetStrBuffer();
        output = locale_reader->ExpandInputString(output);
        f.WriteValue(output, "");
        f.CloseFile();
    }
    else if(operation == 'C')
    {
        locale_reader = new LocaleReader(locale_path.c_str());
        std::cout << "Using locale: " << locale_reader->GetLocaleName() << std::endl;
        data_base::CreateNewFile_static(path.c_str());
        data_base f(path.c_str(), false);
        data_base fin(target_file.c_str());
        output = fin.GetStrBuffer();
        output = locale_reader->CondenseInputString(output);
        f.WriteValue(output, "");
        f.CloseFile();
    }

    delete locale_reader;
}

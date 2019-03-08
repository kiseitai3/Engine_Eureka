#include "../localesystem.h"
#include "../data_base.h"
#include <cmd_utils.h>

#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    std::string locale_path, target_file, path = "out.out", output;
    char operation;
    LocaleReader* locale_reader;

    if(argc <= 1)
    {
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
    }
    else
    {
        char no_argument_options[] = "help,E,C;";
        cmd_init(no_argument_options, 10);
        cmd_process(argc, argv);
        for(size_t i = 0; i < cmd_get_argc(); i++)
        {
            size_t hash = cmd_get_option();
            if(hash == cmd_generate_hash("-locale", 7))
                locale_path = cmd_get_argument();
            else if(hash == cmd_generate_hash("-file", 5))
                target_file = cmd_get_argument();
            else if(hash == cmd_generate_hash("-E", 2))
                operation = 'E';
            else if(hash == cmd_generate_hash("-C", 2))
                operation = 'C';
            else if(hash == cmd_generate_hash("-o", 2))
                path = cmd_get_argument();
            else
                std::cout << "Unknown argument!" << std::endl;
            cmd_next_arg();
        }
        printf("%s \n", cmd_get_appdir());
        printf("%s \n", cmd_get_appname());
        printf("%s \n", cmd_get_fullpath());
    }




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

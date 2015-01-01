#include "modadapter.h"

ModAdapter::ModAdapter(const char* file, Game& owner)
{
    std::string tmp = file;
    dlModule = NULL;
    sModule = NULL;
    if(tmp.rfind(".dll") || tmp.rfind(".so") || tmp.rfind(".dylib") || tmp.rfind(".plg"))//Check if we have a binary plugin
        dlModule = new Plugin(file);//Initialize the plugin loader
    else
        sModule = new ScriptWrap(file);//Otherwise, initialize the plugin as a regular script. Good for scripted plugins.

    if(!owner_ref && !(owner_ref == &owner))
        owner_ref = &owner;
}

bool ModAdapter::isFuncRegistered(const std::string& name) const
{
    /*This method checks if the function name matches any in the function list. If it does, bingo, we already registered
    the plugin and nothing else should be done!
    */
    for(size_t i = 0; i < fList.size(); i++)
    {
        if(fList[i].Name == name)
            return true;
    }
    return false;
}

void ModAdapter::RegisterFunction(const std::string& name)
{
    //Register a single function
    if(isFuncRegistered(name))
    {
        std::cout << "Warning: Function is already registered. Skipping execution! Function Name: " << name << std::endl;
        return;
    }

    if(sModule)
        fList.push_back(func(name, NULL));
    else if(dlModule)
        fList.push_back(func(name, dlModule->GetFunction(name)));
}

void ModAdapter::RegisterFunctionFromFile(const char* file)
{
    //Read a settings file that has a series of functions to register! These functions must be present in the plugin!
    data_base settings(file);
    size_t fCount = settings.GetIntFromData("func_count");
    for(size_t i = 0; i < fCount; i++)
    {
        if(sModule)
            fList.push_back(Node(settings.GetStrFromData("func_" + intToStr(i) + "_name"), NULL));
        else if(dlModule)
            fList.push_back(Node(settings.GetStrFromData("func_" + intToStr(i) + "_name"), dlModule->GetFunction(settings.GetStrFromData("func_" + intToStr(i) + "_name"))));
    }
}

int ModAdapter::RunFunctions() const
{
    //Execute functions!
    for(size_t i = 0; i < fList.size(); i++)
    {
        if(sModule)
        {
            sModule->AddArgument(owner_ref);
            sModule->executeFunction(fList[i].Name, ScriptWrap::NO_ARGS);
            return EXIT_SUCCESS;
        }
        else if(dlModule)
        {
            fList[i].Ptr(owner_ref);
            return EXIT_SUCCESS;
        }
    }
    std::cout << "Error: The plugin function failed to execute!" << std::endl;
    return EXIT_FAILURE;
}

ModAdapter::~ModAdapter()
{
    if(sModule)
        delete sModule;
    if(dlModule)
        delete dlModule;
}

Node::Node(const std::string& name, func_ptr ptr)
{
    Name = name;
    Ptr = ptr;
}

void_ptr helperModFunction(void_ptr obj)
{
    ((ModAdapter*)obj)->RunFunctions();
}

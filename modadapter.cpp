<<<<<<< HEAD
#include "modadapter.h"

ModAdapter::ModAdapter(const char* file)
=======
#define EUREKA_EXPORT
#include "modadapter.h"

//Engine name space macro
//ENGINE_NAMESPACE


ModAdapter::ModAdapter(const char* file, Game* owner)
>>>>>>> TheIllusiveMan
{
    std::string tmp = file;
    dlModule = NULL;
    sModule = NULL;
    if(tmp.rfind(".dll") || tmp.rfind(".so") || tmp.rfind(".dylib") || tmp.rfind(".plg"))//Check if we have a binary plugin
        dlModule = new Plugin(file);//Initialize the plugin loader
    else
        sModule = new ScriptWrap(file);//Otherwise, initialize the plugin as a regular script. Good for scripted plugins.
<<<<<<< HEAD
=======

    if(!owner_ref && !(owner_ref == owner))
        owner_ref = owner;
>>>>>>> TheIllusiveMan
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
<<<<<<< HEAD
        fList.push_back(func(name, NULL));
    else if(dlModule)
        fList.push_back(func(name, dlModule->GetFunction(name)));
=======
        fList.push_back(Node(name, NULL));
    else if(dlModule)
        fList.push_back(Node(name, dlModule->GetFunction(name)));
>>>>>>> TheIllusiveMan
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

<<<<<<< HEAD
int ModAdapter::RunFunctions(Game* owner) const
=======
void ModAdapter::UnregisterFunction(const std::string& name)
{
    for(std::vector<Node>::iterator itr = fList.begin(); itr != fList.end(); itr++)
    {
        if(itr->Name == name)
            fList.erase(itr);
    }
}

int ModAdapter::RunFunctions() const
>>>>>>> TheIllusiveMan
{
    //Execute functions!
    for(size_t i = 0; i < fList.size(); i++)
    {
        if(sModule)
        {
<<<<<<< HEAD
            sModule->AddArgument(owner);
=======
            sModule->AddArgument(owner_ref);
>>>>>>> TheIllusiveMan
            sModule->executeFunction(fList[i].Name, ScriptWrap::NO_ARGS);
            return EXIT_SUCCESS;
        }
        else if(dlModule)
        {
<<<<<<< HEAD
            fList[i].Ptr(owner);
=======
            fList[i].Ptr(owner_ref);
>>>>>>> TheIllusiveMan
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

<<<<<<< HEAD
=======
void_ptr helperModFunction(void_ptr obj)
{
    ((ModAdapter*)obj)->RunFunctions();
}

//End of namespace macro
//ENGINE_NAMESPACE_END
>>>>>>> TheIllusiveMan

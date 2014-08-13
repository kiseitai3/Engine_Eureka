#include "modadapter.h"

ModAdapter::ModAdapter(const char* file)
{
    std::string tmp = file;
    dlModule = NULL;
    sModule = NULL;
    if(tmp.rfind(".dll") || tmp.rfind(".so") || tmp.rfind(".dylib") || tmp.rfind(".plg"))
        dlModule = new Plugin(file);
    else
        sModule = new ScriptWrap(file);
}

bool ModAdapter::isFuncRegistered(const std::string& name) const
{
    for(size_t i = 0; i < fList.size(); i++)
    {
        if(fList[i].Name == name)
            return true;
    }
    return false;
}

void ModAdapter::RegisterFunction(const std::string& name)
{
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

int ModAdapter::RunFunctions(Game* owner) const
{
    for(size_t i = 0; i < fList.size(); i++)
    {
        if(sModule)
        {
            sModule->AddArgument(owner);
            sModule->executeFunction(fList[i].Name, ScriptWrap::NO_ARGS);
        }
        else if(dlModule)
        {
            fList[i].Ptr(owner);
        }

    }
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


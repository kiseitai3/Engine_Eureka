#include "scriptwrap.h"

ScriptWrap::ScriptWrap(const char* file)
{
    //Set variables to propper default values
    pyScript = NULL;
    luaScript = NULL;
    scriptMode = NONE;

    std::string File = file;

    //Let's decide the kind of file we have to load and therefore the scripting mode!
    //The scripting mode is a flag to decide whether to execute the Pywrap or LuaWrap APIs.
    if(File.rfind(".lua") || File.rfind(".luo"))
        scriptMode = LUA;
    else if(File.rfind(".py") || File.rfind(".pyc"))
        scriptMode = PYTHON;

    //Now, let's load the correct script object based on the scripting mode!
    switch(scriptMode)
    {
    case LUA:
        luaScript = new LuaWrap(file);
        break;
    case PYTHON:
        pyScript = new Pywrap(file);
        break;
    default:
        //Throw an error to cout for later reference!
        std::cout << "Error: script failed to initialize! "
            << "Program execution has not been interrupted but execution will result in undefined behavior!"
            << "Error loading script: " << file << std::endl;
    }
}

bool ScriptWrap::isInitialized() const
{
    return scriptMode != NONE;
}

void ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        luaScript->executeFunction(name);
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        pyScript->executeNoReturnF(name.c_str());
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
        << "Program will continue as normal but may result in undefined behavior!"
        << std::endl;
        execSuccess = false;
    }
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        if(luaScript->executeFunction(name))
            return luaScript->lua_extractInt(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        return 0;
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        return pyScript->py_extractInt(pyScript->executeReturnF(name.c_str()));
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execSuccess = false;
        return 0;
    }
}

double ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        if(luaScript->executeFunction(name))
            return luaScript->lua_extractDouble(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        return 0;
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        return pyScript->py_extractDouble(pyScript->executeReturnF(name.c_str()));
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execSuccess = false;
        return 0;
    }
}

char ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        if(luaScript->executeFunction(name))
            return luaScript->lua_extractChar(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        return 0;
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        return pyScript->py_extractChar(pyScript->executeReturnF(name.c_str()));
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execSuccess = false;
        return 0;
    }
}

bool ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        if(luaScript->executeFunction(name))
            return luaScript->lua_extractBool(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        return false;
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        return pyScript->py_extractBool(pyScript->executeReturnF(name.c_str()));
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execSuccess = false;
        return false;
    }
}

std::string ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        if(luaScript->executeFunction(name))
            return luaScript->lua_extractStr(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        return "";
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        return pyScript->py_extractStr(pyScript->executeReturnF(name.c_str()));
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execSuccess = false;
        return "";

    }
}

void* ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        if(luaScript->executeFunction(name))
            return luaScript->lua_extractPtr(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        return NULL;
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        return pyScript->py_extractPtr(pyScript->executeReturnF(name.c_str()));
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execSuccess = false;
        return NULL;
    }
}

std::vector<fuzzy_obj> ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    execSuccess = true;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
    std::vector<fuzzy_obj> tmp;
    switch(scriptMode)
    {
    case LUA:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    luaScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    luaScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    luaScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    luaScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    luaScript->AddArgument(args[i].c);
                    break;
                case 's':
                    luaScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        luaScript->executeFunction(name.c_str()));
        return luaScript->GenerateListFromLuaTable();
        break;

    case PYTHON:
        if(argCount)
        {
            for(size_t i = 0; i < argCount; i++)
            {
                switch(args[i].flag) //Send right argument!
                {
                case 'i':
                    pyScript->AddArgument(args[i].number);
                    break;
                case 'd':
                    pyScript->AddArgument(args[i].decimal);
                    break;
                case 'u':
                    pyScript->AddArgument(args[i].uNumber);
                    break;
                case 'b':
                    pyScript->AddArgument(args[i].answer);
                    break;
                case 'c':
                    pyScript->AddArgument(args[i].c);
                    break;
                case 's':
                    pyScript->AddArgument(args[i].str);
                    break;
                default:
                    std::cout << "Warning: The program received arguments but this argument does not conform to the specified overloads! "
                        << "The program did not pass this argument to the script function! Execution will continue but may result in "
                        << "undefined behavior! Argument Flag:" << args[i].flag << " Argument Values: " << args[i].number << "; "
                        << args[i].uNumber << "; " << args[i].c << "; " << args[i].answer << "; " << args[i].str << "; "
                        << std::endl;
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str()));
        size_t s = pyScript->GetSizeOfResult(obj);
        for(size_t i = 0; i < s; i++)
        {
            fuzzy_obj n;
            n.flag = pyScript->GetResultType(pyScript->GetItemFromResultList(obj, i));
            switch(n.flag)
            {
            case 'i':
                 tmp.push_back(pyScript->py_extractIntFromList(obj, i));
                 break;
            case 'd':
                tmp.push_back(pyScript->py_extractDoubleFromList(obj, i));
                break;
            case 'b':
                tmp.push_back(pyScript->py_extractBoolFromList(obj, i));
                break;
            case 'c':
                tmp.push_back(pyScript->py_extractCharFromList(obj, i));
                break;
            case 's':
                tmp.push_back(pyScript->py_extractStrFromList(obj, i));
                break;
            case 'v':
                tmp.push_back(pyScript->py_extractPtrFromList(obj, i));
                break;
            default:
                std::cout << "Error: Argument from array returned by script function is not a valid type! "
                    << "Wow, the cake is a lie!" << std::endl;
            }
        }
        return tmp;
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execSuccess = false;
        return tmp;
    }
}

ScriptWrap::~ScriptWrap()
{
    if(pyScript)
        delete pyScript;
    if(luaScript)
        delete luaScript;
}


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

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                    execStatus = ERROR_UNKNOWN_ARG;
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        pyScript->executeNoReturnF(name.c_str());
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
        << "Program will continue as normal but may result in undefined behavior!"
        << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, int& response)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        if(luaScript->executeFunction(name))
            response = luaScript->lua_extractInt(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        execStatus = ERROR_EXEC_FAILURE;
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str());
        response = pyScript->py_extractInt(obj);
        pyScript->DecreaseRef(obj);
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, double& response)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        if(luaScript->executeFunction(name))
            response = luaScript->lua_extractDouble(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        execStatus = ERROR_EXEC_FAILURE;
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str());
        response = pyScript->py_extractDouble(obj);
        pyScript->DecreaseRef(obj);
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, char& response)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        if(luaScript->executeFunction(name))
            response = luaScript->lua_extractChar(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        execStatus = ERROR_EXEC_FAILURE;
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str());
        response = pyScript->py_extractChar(obj);
        pyScript->DecreaseRef(obj);
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, bool& response)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        if(luaScript->executeFunction(name))
            response = luaScript->lua_extractBool(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        execStatus = ERROR_EXEC_FAILURE;
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str());
        response = pyScript->py_extractBool(obj);
        pyScript->DecreaseRef(obj);
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::string& response)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        if(luaScript->executeFunction(name))
            response = luaScript->lua_extractStr(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        execStatus = ERROR_EXEC_FAILURE;
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str());
        response = pyScript->py_extractStr(obj);
        pyScript->DecreaseRef(obj);
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, void_ptr& response)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                        execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        if(luaScript->executeFunction(name))
            response = luaScript->lua_extractPtr(luaScript->GetInternalState());
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        execStatus = ERROR_EXEC_FAILURE;
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
                    execStatus = ERROR_UNKNOWN_ARG
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str());
        response = pyScript->py_extractPtr(obj);
        pyScript->DecreaseRef(obj);
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

int ScriptWrap::executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::vector<fuzzy_obj>& response)
{
    size_t argCount = args.size();
    size_t execStatus = EXIT_SUCCESS;//Set the flag here in anticipation of success. It will be changed if the method fails to execute the script!
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        if(luaScript->executeFunction(name.c_str()))
            response = luaScript->GenerateListFromLuaTable();
        std::cout << "Error: Function failed to execute! Check the logs for more information!" << std::endl;
        execStatus = ERROR_EXEC_FAILURE;
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
                    execStatus = ERROR_UNKNOWN_ARG;
                }
            }
        }
        PyObject* obj = pyScript->executeReturnF(name.c_str()));
        pyScript->GenerateListFromPyTuple(obj, response);
        pyScript->DecreaseRef(obj);
        break;

    default:
        std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
        execStatus = ERROR_NOT_A_SCRIPT;
    }
    return execStatus;
}

ScriptWrap::~ScriptWrap()
{
    if(pyScript)
        delete pyScript;
    if(luaScript)
        delete luaScript;
}


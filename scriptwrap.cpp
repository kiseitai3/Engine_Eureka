#include "scriptwrap.h"


//Static methods/ vars
const std::vector<fuzzy_obj> ScriptWrap::NO_ARGS;

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

void ScriptWrap::ClearArgs(size_t arg_size)
{
    /* This method is tricky to understand and set propperly because clearing arguments in lua is different from python 2.7
    Basically, I have to create a PyTuple with the expected number of arguments in the python side, which clashes with the
    stack notion of lua since it uses the arg_size to know how many items to pop in the first place! To make everything nicely
    encapsulated, I will assume the number means how many items you want to eventually put in the argument container after it is
    cleared. As a result, I have to make this method clear the lua side completely and only pass arg_size when we are executing
    the python side!
    */
    switch(scriptMode)
    {
    case LUA:
        luaScript->ClearArgs(LUA_ERASE_ALL);
        break;
    case PYTHON:
        pyScript->ClearArgs(arg_size);
        break;
    default:
        std::cout << "Warning, this script is not initialized and set up properly, so no argument container was cleaned!"
            << std::endl;
    }
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
        {
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
        }

    default:
        {
            std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
            execStatus = ERROR_NOT_A_SCRIPT;
        }
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
        {
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
        }

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
        {
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
        }

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
        {
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
        }

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
        {
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
        }

    default:
        {
            std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
            execStatus = ERROR_NOT_A_SCRIPT;
        }
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
        {
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
            response = pyScript->py_extractPtr(obj);
            pyScript->DecreaseRef(obj);
            break;
        }

    default:
        {
           std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
            execStatus = ERROR_NOT_A_SCRIPT;
        }
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
        {
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
            pyScript->GenerateListFromPyTuple(obj, response);
            pyScript->DecreaseRef(obj);
            break;
        }
    default:
        {
            std::cout << "Warning: Program tried to execute function when no script was initialized! "
            << "Program will continue as normal but may result in undefined behavior!"
            << std::endl;
            execStatus = ERROR_NOT_A_SCRIPT;
        }
    }
    return execStatus;
}

//Argument methods
void ScriptWrap::AddArgument(int argument)
{
    /*Note:  If you are a developer, you may want to double check that you are passing a basic data type
    or a general void pointer to your custom structure instance!
    */
    switch(scriptMode)//Check who to send the argument to
    {
    case LUA:
        luaScript->AddArgument(argument);
        break;
    case PYTHON:
        pyScript->AddArgument(argument);
        break;
    default:
         std::cout << "Warning: Method received a request to pass an argument to a script but no scripts were loaded!"
            << std::endl;
    }
}

void ScriptWrap::AddArgument(char argument)
{
    /*Note:  If you are a developer, you may want to double check that you are passing a basic data type
    or a general void pointer to your custom structure instance!
    */
    switch(scriptMode)//Check who to send the argument to
    {
    case LUA:
        luaScript->AddArgument(argument);
        break;
    case PYTHON:
        pyScript->AddArgument(argument);
        break;
    default:
         std::cout << "Warning: Method received a request to pass an argument to a script but no scripts were loaded!"
            << std::endl;
    }
}

void ScriptWrap::AddArgument(bool argument)
{
    /*Note:  If you are a developer, you may want to double check that you are passing a basic data type
    or a general void pointer to your custom structure instance!
    */
    switch(scriptMode)//Check who to send the argument to
    {
    case LUA:
        luaScript->AddArgument(argument);
        break;
    case PYTHON:
        pyScript->AddArgument(argument);
        break;
    default:
        std::cout << "Warning: Method received a request to pass an argument to a script but no scripts were loaded!"
            << std::endl;
    }
}

void ScriptWrap::AddArgument(unsigned int argument)
{
    /*Note:  If you are a developer, you may want to double check that you are passing a basic data type
    or a general void pointer to your custom structure instance!
    */
    switch(scriptMode)//Check who to send the argument to
    {
    case LUA:
        luaScript->AddArgument(argument);
        break;
    case PYTHON:
        pyScript->AddArgument(argument);
        break;
    default:
        std::cout << "Warning: Method received a request to pass an argument to a script but no scripts were loaded!"
            << std::endl;
    }
}

void ScriptWrap::AddArgument(void_ptr argument)
{
    /*Note:  If you are a developer, you may want to double check that you are passing a basic data type
    or a general void pointer to your custom structure instance!
    */
    switch(scriptMode)//Check who to send the argument to
    {
    case LUA:
        luaScript->AddArgument(argument);
        break;
    case PYTHON:
        pyScript->AddArgument(argument);
        break;
    default:
        std::cout << "Warning: Method received a request to pass an argument to a script but no scripts were loaded!"
            << std::endl;
    }
}

void ScriptWrap::AddArgument(const std::string& argument)
{
    /*Note:  If you are a developer, you may want to double check that you are passing a basic data type
    or a general void pointer to your custom structure instance!
    */
    switch(scriptMode)//Check who to send the argument to
    {
    case LUA:
        luaScript->AddArgument(argument);
        break;
    case PYTHON:
        pyScript->AddArgument(argument);
        break;
    default:
        std::cout << "Warning: Method received a request to pass an argument to a script but no scripts were loaded!"
            << std::endl;
    }
}

void ScriptWrap::AddArgument(double argument)
{
    /*Note:  If you are a developer, you may want to double check that you are passing a basic data type
    or a general void pointer to your custom structure instance!
    */
    switch(scriptMode)//Check who to send the argument to
    {
    case LUA:
        luaScript->AddArgument(argument);
        break;
    case PYTHON:
        pyScript->AddArgument(argument);
        break;
    default:
        std::cout << "Warning: Method received a request to pass an argument to a script but no scripts were loaded!"
            << std::endl;
    }
}

ScriptWrap::~ScriptWrap()
{
    if(pyScript)
        delete pyScript;
    if(luaScript)
        delete luaScript;
}


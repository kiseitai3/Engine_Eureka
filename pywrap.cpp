#include <Python.h>
#include "pywrap.h"
#include <string>
#include "conversion.h"
#include <iostream>

void Pywrap::exec_pycode(const char* code)
{
    PyRun_SimpleString(code);
}

void Pywrap::SetFilePath(const char* file)
{
    path = file;
}

Pywrap::Pywrap(const char* file, unsigned int arg_size)
{
    if(file != "")
    {
        if(findString(".py",file)>= 0)
        {
            file = sliceStr(file,0,std::string(file).size() - 3).c_str();
        }
        SetFilePath(file);
        name_space = PyString_FromString(file);
        module = PyImport_Import(name_space);
        PyErr_Print();//get error output if import fails :).
        Py_DECREF(name_space);
        fileLoaded = true;
    }
    else
    {
        fileLoaded = false;
    }
    args = PyTuple_New(arg_size);
    sizeT = arg_size;
    index = 0;
}

bool Pywrap::isFileLoaded() const
{
    return fileLoaded;
}

bool Pywrap::isResultVoid(PyObject* result) const
{
    return result == Py_None;
}

char Pywrap::getReturnType(PyObject* result, size_t& length = 0) const
{
    if(PyFloat_Check(result))
        return 'd';
    if(PyInt_Check(result))
        return 'i';
    if(PyBool_Check(result))
        return 'b';
    if(PyString_Check(result))
        return 's';
    return 'v';
}

void Pywrap::DecreaseRef(PyObject *obj)
{
        Py_CLEAR(obj);
}

void Pywrap::DisplayInternalVars()
{
    /*This method is for debugging purposes. It simply outputs the pointer addresses. A 0 means some process that should have set
    the pointer to something > 0 failed to return an address to an object in the heap (i.e. PyImport_Import()).*/
    std::cout<<module<<"--module5"<<std::endl;
    std::cout<<func<<std::endl;
    std::cout<<result<<std::endl;
    std::cout<<args<<std::endl;
    std::cout<<value<<"--value5"<<std::endl;
}

void Pywrap::executeNoReturnF(const char* funcName)//all arguments that will be passed to a Python function have to be added to a string literal with the type letter at the beginning and a ; ending each entry (i.e. i1;f23.4;sLove and Peace;)
{
    /*Like executeReturnF, this method extracts a function from the loaded python module and calls it thanks to the
    defined () operator in boost*/
    func =  PyObject_GetAttrString(module, funcName);
    PyErr_Print();//get error output if import fails :).
    if (func && PyCallable_Check(func))
    {
        if(PyTuple_GET_SIZE(args) < 1)
        {
            std::cout<<"Argument list is 0 items in size. Do not panic if you get an empty return!\n\r";
        }
        PyObject_CallObject(func, args);//Execute function.
    }
    DecreaseRef(func);//Small cleanup.
}

PyObject *Pywrap::exec_FullFile(const char file[], PyObject *argsI)
{
    /*This method will take a filepath and a tuple containing the arguments, and will execute a main function
    within the script. I am assuming here that the module contains a main function that I can use as the
    entrypoint. I am not using the standard if __namespace__ == Python entrypoint!*/
    if(findString(".py",file)>= 0)//Check and delete the .py extension as it is not necessary and makes the Python API crash.
        {
            file = sliceStr(file,0,std::string(file).size() - 3).c_str();
        }
    PyObject *nameI = PyString_FromString(file);//Create Python object from our C string
    PyObject *moduleI = PyImport_Import(nameI);//Import the module.
    PyErr_Print();//get error output if import fails :).
    Py_DECREF(nameI);//Small cleanup.
    PyObject *funcI = PyObject_GetAttrString(moduleI, "main");
    PyErr_Print();//get error output if import fails :).
    if (funcI && PyCallable_Check(funcI))
    {
        if(PyTuple_GET_SIZE(args) < 1)
        {
            std::cout<<"Argument list is 0 items in size. Do not panic if you get an empty return!\n\r";
        }
        result = PyObject_CallObject(funcI, argsI);//save the reference inside this class' object so we don't lose it for when we have to decrease its reference count. :)
        //Always remember to do some cleanup.
        Py_CLEAR(moduleI);
        Py_CLEAR(funcI);
        Py_CLEAR(argsI);
        //return our internal reference. The final cleanup has to be done elsewhere. I assume in this function that
        //I can overwrite our internal copy of the pointer because the cleanup will occur at the caller side.
        return result;
    }
    return 0;
}

void Pywrap::ClearArgs(unsigned arg_size)
{
    /*This method resets the state of the args object by creating a new PyTuple. All of the methods in this class assume that all instances of this
    class will have their PyObject management enclosed. In other words, no references in one instance shall be copied more than once
    without having its reference count increased.*/
    CleanCPyObjInArgs();
    Py_CLEAR(args);//Make sure the previous object had its reference count lowered (and hopefully the object was deleted altogether)
    args = PyTuple_New(arg_size);
    sizeT = arg_size;
    index = 0;
}

void Pywrap::IncreaseRef(PyObject *obj)
{
    Py_INCREF(obj);
}

PyObject *Pywrap::executeReturnF(const char* funcName)
{
    /*Like executeNoReturnF, this method extracts a function from the loaded python module and calls it thanks to the
    defined () operator in boost. However, I return the resulting boost py object since it contains the results of the
    function.*/
    func =  PyObject_GetAttrString(module, funcName);
    PyErr_Print();//get error output if import fails :).
    if (func && PyCallable_Check(func))
    {
        if(PyTuple_GET_SIZE(args) < 1)
        {
            std::cout<<"Argument list is 0 items in size. Do not panic if you get an empty return!\n\r";
        }
        value = PyObject_CallObject(func, args);//Execute function
        return value;
    }
    return func;
}

void InitPy()
{
    Py_Initialize();
}

void EndPy()
{
    Py_Finalize();
}

void Pywrap::ClearPyObjects()
{
    //Cleanup PyCObjects
    CleanCPyObjInArgs();
    //Clear internal PyObjects.
    if(!name_space)
    {
        Py_CLEAR(name_space);
    }
        if(!module)
    {
        Py_CLEAR(module);
    }
        if(!func)
    {
        Py_CLEAR(func);
    }
        if(!args)
    {
        Py_CLEAR(args);
    }
        if(!dict)
    {
        Py_CLEAR(dict);
    }
        if(!result)
    {
        Py_CLEAR(result);
    }
        if(!value)
    {
        Py_CLEAR(value);
    }
}

Pywrap::~Pywrap()
{
    ClearPyObjects();
}

unsigned int Pywrap::GetSizeOfArgs() const
{
    return sizeT;
}

PyObject *Pywrap::CreateObjFromPtr(void *classT)
{
    return PyCObject_FromVoidPtr(classT, NULL);
}

void Pywrap::CleanCPyObjInArgs()
{
    for(int i = 0; i < PyTuple_GET_SIZE(args); i++)
    {
        if(PyCObject_Check(PyTuple_GetItem(args, i)))
        {
            PyObject *obj = PyTuple_GetItem(args, i);
            Py_CLEAR(obj);
        }
    }
}
//Overloads
void Pywrap::AddArgument (int argument)
{
    PyTuple_SetItem(args, index, PyInt_FromSize_t(argument));
    index++;
}

void Pywrap::AddArgument (unsigned int argument)
{
    PyTuple_SetItem(args, index, PyInt_FromSize_t(argument));
    index++;
}

void Pywrap::AddArgument (std::string argument)
{
    PyTuple_SetItem(args, index, PyString_FromString(argument.c_str()));
    index++;
}

void Pywrap::AddArgument (char argument)
{
    AddArgument(args, index, argument);
    index++;
}

void Pywrap::AddArgument (double argument)
{
    PyTuple_SetItem(args, index, PyFloat_FromDouble(argument));
    index++;
}

void Pywrap::AddArgument (PyObject *argument)
{
    PyTuple_SetItem(args, index, argument);
    index++;
}
//Py Conversion Functions with overloads
int Pywrap::py_extractInt(PyObject *results) const
{
    if(PyInt_Check(results))
    {
        return PyInt_AsSsize_t(results);
    }
    std::cout << "Warning: PyObject is not Integer. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

char Pywrap::py_extractChar(PyObject *results) const
{
    if(PyString_Check(results))
    {
        return PyString_AsString(results)[0];
    }
    std::cout << "Warning: PyObject is not Char. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

std::string Pywrap::py_extractStr(PyObject *results) const
{
    if(PyString_Check(results))
    {
        return std::string(PyString_AsString(results));
    }
    std::cout << "Warning: PyObject is not String. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return "";
}

double Pywrap::py_extractDouble(PyObject *results) const
{
    if(PyFloat_Check(results))
    {
        return PyFloat_AsDouble(results);
    }
    std::cout << "Warning: PyObject is not Double. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

bool Pywrap::py_extractBool(PyObject *results) const
{
    if(PyBool_Check(results))
        return PyObject_IsTrue(results);
    std::cout << "Warning: PyObject is not boolean. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return false;
}

void *Pywrap::py_extractPtr(PyObject *results) const
{
    if(PyCObject_Check(results))
    {
        return PyCObject_AsVoidPtr(results);
    }
    std::cout << "Warning: PyObject is not a C object. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

int Pywrap::py_extractIntFromList(PyObject *results, unsigned int index) const
{
    if(PyTuple_Check(results))
    {
        return py_extractInt(PyTuple_GetItem(results, index));
    }
    std::cout << "Warning: PyObject is not a Tuple. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

std::string Pywrap::py_extractStrFromList(PyObject *results, unsigned int index) const
{
    if(PyTuple_Check(results))
    {
        return py_extractStr(PyTuple_GetItem(results, index));
    }
    std::cout << "Warning: PyObject is not a Tuple. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return "";
}

char Pywrap::py_extractCharFromList(PyObject *results, unsigned int index) const
{
    if(PyTuple_Check(results))
    {
        return py_extractStr(PyTuple_GetItem(results, index))[0];
    }
    std::cout << "Warning: PyObject is not a Tuple. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

double Pywrap::py_extractDoubleFromList(PyObject *results, unsigned int index) const
{
    if(PyTuple_Check(results))
    {
        return py_extractDouble(PyTuple_GetItem(results, index));
    }
    std::cout << "Warning: PyObject is not a Tuple. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

void *Pywrap::py_extractPtrFromList(PyObject *results, unsigned int index) const
{
    if(PyTuple_Check(results))
    {
        return py_extractPtr(PyTuple_GetItem(results, index));
    }
    std::cout << "Warning: PyObject is not a Tuple. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

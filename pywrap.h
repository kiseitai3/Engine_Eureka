#ifndef PYWRAP_H_INCLUDED
#define PYWRAP_H_INCLUDED
//Includes
#include <Python.h>
#include <string>

//class
class Pywrap
{
    private:
        //vars
    PyObject *module, *name_space, *dict, *func;
    PyObject *args, *value, *result;
    unsigned int sizeT;
    size_t index;
    std::string path;
    bool fileLoaded;
    //methods


    public:
        //methods
    Pywrap(const char* file = "", unsigned int arg_size = 0);//constructor
    void SetFilePath(const char* file);
    void executeNoReturnF(const char* funcName);
    PyObject *executeReturnF(const char* funcName);
    void exec_pycode(const char* code);
    PyObject *exec_FullFile(const char file[], PyObject *argsI = Py_None);
    void ClearArgs(unsigned arg_size = 0);
    void ClearPyObjects();
    void DecreaseRef(PyObject *obj);
    void IncreaseRef(PyObject *obj);
    void DisplayInternalVars();
    unsigned int GetSizeOfArgs() const;
    PyObject *CreateObjFromPtr(void *classT);
    void CleanCPyObjInArgs();
    bool isFileLoaded() const;
    bool isResultVoid(PyObject* result) const;
    char getReturnType(PyObject* result, size_t& length = 0) const;//Returns i, b, d, s for int, boolean, double, and string. Use the length parameter to distinguish between char and string.
    ~Pywrap();//destructor
    //Oveloads
    void AddArgument (int argument, unsigned int index);
    void AddArgument (std::string argument, unsigned int index);
    void AddArgument (char argument, unsigned int index);
    void AddArgument (double argument, unsigned int index);
    void AddArgument (PyObject *argument, unsigned int index);
    void AddArgument(unsigned int argument, unsigned int index);

    //Py Conversion Functions with overloads
    /*All functions in this block take care of the extraction of a C type from a generalized object
    or list! :D*/
    int py_extractInt(PyObject *results) const;
    char py_extractChar(PyObject *results) const;
    std::string py_extractStr(PyObject *results) const;
    double py_extractDouble(PyObject *results) const;
    bool py_extractBool(PyObject *results) const;
    void *py_extractPtr(PyObject *results) const;
    int py_extractIntFromList(PyObject *results, unsigned int index) const;
    std::string py_extractStrFromList(PyObject *results, unsigned int index) const;
    char py_extractCharFromList(PyObject *results, unsigned int index) const;
    double py_extractDoubleFromList(PyObject *results, unsigned int index) const;
    void *py_extractPtrFromList(PyObject *results, unsigned int index) const;
    bool py_extractBoolFromList(PyObject *results, unsigned int index) const;
};
void InitPy();
void EndPy();

#endif // PYWRAP_H_INCLUDED

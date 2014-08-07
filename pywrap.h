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
    int py_extractInt(PyObject *results);
    char py_extractChar(PyObject *results);
    std::string py_extractStr(PyObject *results);
    double py_extractDouble(PyObject *results);
    void *py_extractPtr(PyObject *results);
    int py_extractIntFromList(PyObject *results, unsigned int index);
    std::string py_extractStrFromList(PyObject *results, unsigned int index);
    char py_extractCharFromList(PyObject *results, unsigned int index);
    double py_extractDoubleFromList(PyObject *results, unsigned int index);
    void *py_extractPtrFromList(PyObject *results, unsigned int index);
};
void InitPy();
void EndPy();

#endif // PYWRAP_H_INCLUDED

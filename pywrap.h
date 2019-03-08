#ifndef PYWRAP_H_INCLUDED
#define PYWRAP_H_INCLUDED
//Includes
#include <Python.h>
#include <string>
#include <vector>
<<<<<<< HEAD
#include "game.h"
=======
#include <queue>
#include "typedefs.h"
>>>>>>> TheIllusiveMan

//class
class Pywrap
{
    private:
        //vars
    PyObject *module, *name_space, *dict, *func;
    PyObject *args, *value, *result;
<<<<<<< HEAD
    unsigned int sizeT;
    size_t index;
=======
    PyGILState_STATE gstate;
>>>>>>> TheIllusiveMan
    std::string path;
    std::queue<fuzzy_obj> argQueue;
    bool fileLoaded;
    static bool initialized;
    //methods
<<<<<<< HEAD

=======
    void prepArgs();
>>>>>>> TheIllusiveMan

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
    PyObject *CreateObjFromPtr(void_ptr classT);
    void CleanCPyObjInArgs();
    bool isFileLoaded() const;
    bool isResultVoid(PyObject* result) const;
    char GetResultType(PyObject* result, size_t length = 0) const;//Returns i, b, d, s for int, boolean, double, and string. Use the length parameter to distinguish between char and string.
    size_t GetSizeOfResult(PyObject* result);
    PyObject *GetItemFromResultList(PyObject* result, size_t i);
    int GenerateListFromPyTuple(PyObject* obj, std::vector<fuzzy_obj>& response);//This method is not as dangerous as the one in the Lua API!
    ~Pywrap();//destructor
    //Oveloads
    void AddArgument (int argument);
    void AddArgument (std::string argument);
    void AddArgument (char argument);
    void AddArgument (double argument);
<<<<<<< HEAD
    void AddArgument (PyObject *argument);
    void AddArgument(unsigned int argument);
    void AddArgument (void_ptr argument);
=======
    void AddArgument(unsigned int argument);
    void AddArgument (void_ptr argument);

    //Thread Protection
    void LockInterpreter();
    void ReleaseInterpreter();
>>>>>>> TheIllusiveMan

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

#ifndef IOMANAGER_H_INCLUDED
#define IOMANAGER_H_INCLUDED
#include "BST.h"

#include <iostream>
#include <string>
#include "data_base.h"
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class DataBase;
class Game;

class IONode
{
public:
    IONode(bool inputMode, size_t id, cstr file_path, bool database = false);
    ~IONode();
    //Setters
    void DecCount();
    void IncCount();
    //Getters
    size_t GetCount() const;
    size_t GetID() const;
    std::string GetPath() const;
    data_base& GetFile();
    DataBase* GetDataBase();

private:
    data_base* fileHandle;
    DataBase* db;
    std::string filePath;
    size_t refCount, node_id;
};

class IOManager
{
public:
    IOManager(Game* owner);
    ~IOManager();
    void initIOSys();

    //Getters
    //Be careful with manipulation of objects below. The engine will crash if someone deletes objects directly!
    data_base& GetFile(size_t file_id);//Returns reference to data_base object
    DataBase* GetDataBase(size_t db_id);//Returns reference to Database object

    //Setters
    size_t RegisterFile(cstr file_path, bool inputMode = true);
    size_t RegisterDataBase(cstr file);
    void CloseFile(size_t file_id);
    void CloseDBConnection(size_t db_id);

private:
    BinarySearchTree<size_t, IONode*> files;//Storage of file instances
    BinarySearchTree<size_t, IONode*> databases;//Storage of database connections
    Game* owner_ref;
    size_t mutex_io_id, mutex_db_id;
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // IOMANAGER_H_INCLUDED

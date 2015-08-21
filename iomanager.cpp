#include "iomanager.h"
#include "eureka.h"
#include "database.h"
#include "rand_generators.h"

//Engine name space macro
//ENGINE_NAMESPACE


IONode::IONode(bool inputMode, size_t id, cstr file_path, bool database)
{
    db = NULL;
    fileHandle = NULL;
    if(database)
        db = new DataBase(file_path);
    else
        fileHandle = new data_base(file_path, inputMode);
    filePath = file_path;
    refCount = 1;
    node_id = id;
}

IONode::~IONode()
{
    if(fileHandle)
        delete fileHandle;
    if(db)
        delete db;
}

void IONode::DecCount()
{
    if(refCount > 0)
        refCount--;
    else
        std::cout << "Warning: More calls to close the file were made than calls to open it. Check the scripts. File: " << __FILE__
            << " Line: " << __LINE__ << std::endl;
}

void IONode::IncCount()
{
    refCount++;
    if(refCount == 0)
        std::cout << "Warning: More calls to open the file were made than calls to close it. Check the scripts for excessive "
            << "attempts to open the same file. File: " << __FILE__
            << " Line: " << __LINE__ << std::endl;
}

size_t IONode::GetCount() const
{
    return refCount;
}

size_t IONode::GetID() const
{
    return node_id;
}

std::string IONode::GetPath() const
{
    return filePath;
}

data_base& IONode::GetFile()
{
    return *fileHandle;
}

DataBase* IONode::GetDataBase()
{
    return db;
}

IOManager::IOManager(Game* owner)
{
    owner_ref = owner;
    //Create mutexes and obtain their ids
    mutex_io_id = owner->SpawnMutex();
    mutex_db_id = owner->SpawnMutex();
}

IOManager::~IOManager()
{
    //Let's manually delete the nodes
    IONode* tmp = NULL;
    //start with file buffers
    //Lock mutex
    owner_ref->LockMutex(mutex_io_id);
    owner_ref->LockMutex(mutex_db_id);

    std::vector<IONode*> tmpObjs = files.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)//Linearly search for the prescence
    {
        tmp = tmpObjs[i];
        if(tmp)
        {
            tmp->GetFile().CloseFile();
            delete tmp;
        }
        tmp = NULL;
    }
    //Then delete the databases
    tmpObjs = files.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)//Linearly search for the prescence
    {
        tmp = tmpObjs[i];
        if(tmp)
        {
            delete tmp;
        }
        tmp = NULL;
    }
    //Unlock appropriate mutex
    owner_ref->UnlockMutex(mutex_io_id);
    owner_ref->UnlockMutex(mutex_db_id);
    //Unregister mutexes
    owner_ref->DeleteMutex(mutex_io_id);
    owner_ref->DeleteMutex(mutex_db_id);
}

size_t IOManager::RegisterFile(cstr file_path, bool inputMode)
{
    //Get a hash
    size_t id = hasher();
    //Lock appropriate mutexes
    owner_ref->LockMutex(mutex_io_id);
    //Check if the file path was already opened
    if(file_path)
    {
        IONode* tmp = NULL;
        std::vector<IONode*> tmpObjs = files.getContents();
        for(size_t i = 0; i < tmpObjs.size(); i++)//Linearly search for the prescence
        {
            if(std::string(file_path) == tmpObjs[i]->GetPath())
            {
                tmp = tmpObjs[i];
            }
        }

        if(tmp)//If the file is already opened, increase its refCount and return its id
        {
            id = tmp->GetID();
            tmp->IncCount();
        }
        else//Otherwise, open the file and return the id generated by the hasher
        {
            files.insert(id, new IONode(inputMode, id, file_path));
        }
    }
    //Unlock appropriate mutex
    owner_ref->UnlockMutex(mutex_io_id);
    return id;
}

size_t IOManager::RegisterDataBase(cstr file)
{
    //Get a hash
    size_t id = hasher();
    //Lock appropriate mutexes
    owner_ref->LockMutex(mutex_db_id);
    //Check if the file path was already opened
    if(file)
    {
        IONode* tmp = NULL;
        std::vector<IONode*> tmpObjs = databases.getContents();
        for(size_t i = 0; i < tmpObjs.size(); i++)//Linearly search for the prescence
        {
            if(std::string(file) == tmpObjs[i]->GetPath())
            {
                tmp = tmpObjs[i];
            }
        }

        if(tmp)//If the file is already opened, increase its refCount and return its id
        {
            id = tmp->GetID();
            tmp->IncCount();
        }
        else//Otherwise, open the file and return the id generated by the hasher
        {
            databases.insert(id, new IONode(true, id, file, true));
        }
    }
    //Unlock appropriate mutex
    owner_ref->UnlockMutex(mutex_db_id);
    return id;
}

data_base& IOManager::GetFile(size_t file_id)
{
    IONode* tmp = NULL;
    //Lock appropriate mutexes
    owner_ref->LockMutex(mutex_io_id);
    //Grab object
    files.search(file_id, tmp);
    //Unlock appropriate mutex
    owner_ref->UnlockMutex(mutex_io_id);
    return tmp->GetFile();
}

DataBase* IOManager::GetDataBase(size_t db_id)
{
    IONode* tmp = NULL;
    //Lock appropriate mutexes
    owner_ref->LockMutex(mutex_db_id);
    //Grab object
    databases.search(db_id, tmp);
    //Unlock appropriate mutex
    owner_ref->UnlockMutex(mutex_db_id);
    return tmp->GetDataBase();
}

void IOManager::CloseFile(size_t file_id)
{
    IONode* tmp = NULL;
    //Lock appropriate mutexes
    owner_ref->LockMutex(mutex_io_id);
    //Grab object
    files.search(file_id, tmp);
    //Check if it is "alive"
    if(tmp->GetCount() > 0)
        tmp->DecCount();//Decrease its reference count
    else
    {
        delete tmp;//Delete the object
        files.remove(file_id);//Unregister the object
    }
    //Unlock appropriate mutex
    owner_ref->UnlockMutex(mutex_io_id);
}

void IOManager::CloseDBConnection(size_t db_id)
{
    IONode* tmp = NULL;
    //Lock appropriate mutexes
    owner_ref->LockMutex(mutex_db_id);
    //Grab object
    databases.search(db_id, tmp);
    //Check if it is "alive"
    if(tmp->GetCount() > 0)
        tmp->DecCount();//Decrease its reference count
    else
    {
        delete tmp;//Delete the object
        databases.remove(db_id);//Unregister the object
    }
    //Unlock appropriate mutex
    owner_ref->UnlockMutex(mutex_db_id);
}

//End of namespace macro
//ENGINE_NAMESPACE_END

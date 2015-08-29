//#define EUREKA_EXPORT
#include "rand_generators.h"
#include "eureka.h"
#include "conversion.h"
#include "threading.h"
#include "data_base.h"
#include "layersystem.h"

//Engine name space macro
//ENGINE_NAMESPACE

Layer::Layer(cstr file, Game* owner, size_t l_id)
{
    data_base lDOM(file);
    id = l_id;
    layer = new draw_base();
    layer->Load_Texture(file, owner->GetRenderer());
    loc.X = lDOM.GetIntFromData("x");
    loc.Y = lDOM.GetIntFromData("y");
    loc.Z = lDOM.GetIntFromData("z");
}

Layer::~Layer()
{
    if(layer)
        delete layer;
}

LayerSystem::LayerSystem(Game* owner)
{
    owner_ref = owner;
}

void LayerSystem::initLayerSys()
{
    mutex_layer_id = owner_ref->SpawnMutex();
}

LayerSystem::~LayerSystem()
{
    owner_ref->DeleteMutex(mutex_layer_id);
}

size_t LayerSystem::AddLayer(cstr file)
{
    size_t id = randUniform(Range(0, GetMaxValueSizeT()));
    //Lock mutex
    owner_ref->LockMutex(mutex_layer_id);
    //Let's check the id and make sure we have a unique id
    while(hasID(id))
    {
        id = randUniform(Range(0, GetMaxValueSizeT()));
    }
    //now we create the object
    layers.push_back(Layer(file, owner_ref, id));
    //Unlock mutex
    owner_ref->UnlockMutex(id);
    //Return id
    return id;
}

std::vector<size_t> LayerSystem::AddLayerSet(cstr file)
{
    std::vector<size_t> ids;
    data_base layerDOM(file);
    int layerCount = layerDOM.GetIntFromData("layer_count");
    //let's start creating the objects
    for(int i = 0; i < layerCount; i++)
    {
        ids.push_back(AddLayer(layerDOM.GetStrFromData(std::string("layer_") + intToStr(i) + "_file").c_str()));
    }
    //return the ids
    return ids;
}

void LayerSystem::DeleteLayer(size_t l_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_layer_id);
    for(std::list<Layer>::iterator itr = layers.begin(); itr != layers.end(); itr++)
    {
        if(itr->id == l_id)
        {
            layers.erase(itr);
            break;
        }
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_layer_id);
}

void LayerSystem::DeleteAllLayers()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_layer_id);
    layers.clear();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_layer_id);
}

Layer& LayerSystem::GetLayer(size_t l_id)
{
    std::list<Layer>::iterator itr;
    //Lock mutex
    owner_ref->LockMutex(mutex_layer_id);
    for(itr = layers.begin(); itr != layers.end(); itr++)
    {
        if(itr->id == l_id)
            break;
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_layer_id);
    return *itr;
}

size_t LayerSystem::GetLayerCount() const
{
    return layers.size();
}

void LayerSystem::DrawLayers()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_layer_id);
    for(std::list<Layer>::iterator itr = layers.begin(); itr != layers.end(); itr++)//Iterate through every layer
    {
        itr->layer->apply_surface(itr->loc.X, itr->loc.Y, owner_ref->GetRenderer());//Draw
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_layer_id);
}

bool LayerSystem::hasID(size_t l_id)
{
    for(std::list<Layer>::iterator itr = layers.begin(); itr != layers.end(); itr++)
    {
        if(itr->id == l_id)
            return true;
    }
    return false;
}

//End of namespace macro
//ENGINE_NAMESPACE_END

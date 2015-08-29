#ifndef LAYERSYSTEM_H_INCLUDED
#define LAYERSYSTEM_H_INCLUDED
#include "typedefs.h"
#include <iostream>
#include <vector>
#include <list>

//Engine name space macro
//ENGINE_NAMESPACE


class Game;
class draw_base;

class Layer
{
public:
    draw_base* layer;
    size_t id;
    math_point loc;

    Layer(cstr file, Game* owner, size_t l_id);
    ~Layer();
};

class LayerSystem
{
public:
    LayerSystem(Game* owner);
    ~LayerSystem();
    void initLayerSys();

    //Setters
    size_t AddLayer(cstr file);
    std::vector<size_t> AddLayerSet(cstr file);
    void DeleteLayer(size_t l_id);
    void DeleteAllLayers();

    //Getter
    Layer& GetLayer(size_t l_id);
    size_t GetLayerCount() const;

    //Housekeeping
    void DrawLayers();

private:
    std::list<Layer> layers;
    size_t mutex_layer_id;
    Game* owner_ref;

    bool hasID(size_t l_id);
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // LAYERSYSTEM_H_INCLUDED

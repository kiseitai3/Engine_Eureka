#ifndef LAYERSYSTEM_H_INCLUDED
#define LAYERSYSTEM_H_INCLUDED
#include "typedefs.h"
#include <iostream>
#include <vector>
#include <list>

class Game;
class draw_base;

struct Layer
{
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

    //Setters
    size_t AddLayer(cstr file);
    std::vector<size_t> AddLayerSet(cstr file);
    void DeleteLayer(size_t l_id);

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


#endif // LAYERSYSTEM_H_INCLUDED

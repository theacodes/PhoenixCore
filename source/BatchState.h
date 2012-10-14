#pragma once

#include "config.h"
#include "Texture.h"
#include "BatchGeometry.h"

namespace phoenix
{

class BatchState
{
public:
    BatchState()
        : is_dirty(false), texture(), texturing_enabled(false)
    {}

    ~BatchState(){}

    inline bool dirty(){
        return is_dirty;
    }

    inline void activate(){
        if(!is_dirty) return;

        if(texture){
            if(!texturing_enabled){
                glEnable(GL_TEXTURE_2D);
                texturing_enabled = true;
            }
            texture->bind();
        } else {
            glDisable(GL_TEXTURE_2D);
            texturing_enabled = false;
        }

        is_dirty = false;
    }

    inline void update(BatchGeometryPtr geom){
        if(geom->getTextureId()){
            if(geom->getTexture() != texture){
                is_dirty = true;
                texture = geom->getTexture();
            }
        } else{
            if(texture){
                is_dirty = true;
                texture = TexturePtr();
            }
        }
    }

private:
    bool is_dirty;
    TexturePtr texture;
    bool texturing_enabled;
    unsigned int primitive_type;
}; // Class BatchState

} // namespace phoenix

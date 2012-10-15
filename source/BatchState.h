#pragma once

#include <limits>
#include "config.h"
#include "Texture.h"
#include "GeometryState.h"
#include "BatchGeometry.h"
#include "BatchRenderer.h"

namespace phoenix
{

class BatchState
{
public:
    BatchState()
        : state(), last_state(), last_texture(0), last_group(std::numeric_limits<signed int>::min())
    {}

    ~BatchState(){}

    inline void activate(BatchRenderer& r){
        if(!state.isDirty()) return;

        if(state.getTexture()){
            if(!last_texture) glEnable(GL_TEXTURE_2D);
            if(last_texture != state.getTexture()->getTextureId()){
                last_texture = state.getTexture()->getTextureId();
                state.getTexture()->bind();
            }
        } else {
            glDisable(GL_TEXTURE_2D);
            last_texture = 0;
        }

        if(state.getGroupId() != last_group){
            // finalize the previous group.
            auto previous = r.getGroupState(last_group);
            if(previous) previous->end(r);

            // activate the current group.
            auto current = r.getGroupState(state.getGroupId());
            if(current) current->begin(r);

            last_group = state.getGroupId();
        }

        state.clean();
    }

    inline void deactivate(BatchRenderer& r){
        if(last_texture) glDisable(GL_TEXTURE_2D);

        // finalize the previous group.
        auto previous = r.getGroupState(last_group);
        if(previous) previous->end(r);
    }

    inline bool update(BatchGeometryPtr geom){
        last_state = state;
        state.update(geom->getState());
        return state.isDirty();
    }

    inline const GeometryState& last(){
        return last_state;
    }

private:
    GeometryState state;
    GeometryState last_state;
    unsigned int last_texture;
    signed int last_group;
}; // Class BatchState

} // namespace phoenix

#pragma once

#include <limits>
#include "config.h"
#include "Rectangle.h"
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
        : state(), last_state(), last_texture(0), last_group(std::numeric_limits<signed int>::min()), is_clipping(false), clip_rect(), last_clip_rect()
    {}

    ~BatchState(){}

    inline void activate(BatchRenderer& r){

        /* Handle texture state changes */
        if(state.isDirty()){

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

            /* Handle group state changes */
            if(state.getGroupId() != last_group){
                // finalize the previous group.
                auto previous = r.getGroupState(last_group);
                if(previous) previous->end(r);

                // activate the current group.
                auto current = r.getGroupState(state.getGroupId());
                if(current) current->begin(r);

                last_group = state.getGroupId();
            }

        }

        // excluded from isDirty because rect can change every time without the state being dirty */
        /* Handle clipping state changes */
        if(state.getClip()){
            if( !is_clipping ){
                glEnable( GL_SCISSOR_TEST );
                is_clipping = true;
            }

            // update scissor test if needed.
            if(clip_rect != last_clip_rect){
                // translate from top-left coords to bottom-left cords
                GLint view[4];
                glGetIntegerv( GL_VIEWPORT, &view[0] );
                GLuint r_y = view[3] - ((GLuint)clip_rect.getX() + (GLuint)clip_rect.getHeight());

                glScissor( (GLuint)clip_rect.getX() , r_y, (GLsizei)clip_rect.getWidth(), (GLsizei)clip_rect.getHeight() );
            }
        }
        else{
            if( is_clipping ){
                glDisable( GL_SCISSOR_TEST );
                is_clipping = false;
            }
        }

        // finally, mark the state as clean.
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

        if(state.getClip()){
            last_clip_rect = clip_rect;
            clip_rect = geom->getClippingRectangle();
        }

        return state.isDirty() || last_clip_rect != clip_rect;
    }

    inline const GeometryState& last(){
        return last_state;
    }

private:
    GeometryState state;
    GeometryState last_state;
    unsigned int last_texture;
    signed int last_group;
    bool is_clipping;
    Rectangle clip_rect;
    Rectangle last_clip_rect;
}; // Class BatchState

} // namespace phoenix

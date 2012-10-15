#pragma once
#include <boost/scoped_ptr.hpp>
#include <algorithm>
#include "Texture.h"
#include <iostream>

namespace phoenix{

class GeometryState {
public:
    GeometryState()
        : dirty(false), depth(0.0f), groupid(0), texture(), primitivetype(0),
        shadow_depth(0.0f), shadow_groupid(0), shadow_texture(), shadow_primitivetype(0)
    {}

    GeometryState(float _d, signed int _g, TexturePtr _t, unsigned int _p)
        : dirty(false), depth(_d), groupid(_g), texture(_t), primitivetype(_p),
        shadow_depth(_d), shadow_groupid(_g), shadow_texture(_t), shadow_primitivetype(_p)
    {}

    ~GeometryState(){
    }

    inline const float getDepth() const { return depth; }
    inline const signed int getGroupId() const { return groupid; }
    inline TexturePtr getTexture() const { return texture; }
    inline const unsigned int getPrimitiveType() const { return primitivetype; }

    inline bool isDirty(){
        return dirty;
    }

    inline void clean(){
        dirty = false;
    }

    inline void setDepth(const float _d){
        if(_d != depth){
            dirty = true;
            shadow_depth = depth;
            depth = _d;
        }
    }

    inline void setGroupId(const signed int _g){
        if(_g != groupid){
            dirty = true;
            shadow_groupid = groupid;
            groupid = _g;
        }
    }

    inline void setTexture(TexturePtr _t){
        if(_t != texture){
            dirty = true;
            shadow_texture = texture;
            texture = _t;
        }
    }

    inline void setPrimitiveType(const unsigned int _p){
        if(_p != primitivetype){
            dirty = true;
            shadow_primitivetype = primitivetype;
            primitivetype = _p;
        }
    }

    void swap(){
        std::swap(shadow_depth, depth);
        std::swap(shadow_groupid, groupid);
        std::swap(shadow_texture, texture);
        std::swap(shadow_primitivetype, primitivetype);
    }

    void update(const GeometryState& other){
        setDepth(other.depth);
        setGroupId(other.groupid);
        setTexture(other.texture);
        setPrimitiveType(other.primitivetype);
    }

    const bool operator< (const GeometryState& b) const{
        if( depth < b.depth ) return true;
        if( depth == b.depth && groupid < b.groupid ) return true;
        unsigned int textureid = texture ? texture->getTextureId() : 0;
        unsigned int other_textureid = b.texture ? b.texture->getTextureId() : 0;
        if( depth == b.depth && groupid == b.groupid && textureid < other_textureid ) return true;
        if( depth == b.depth && groupid == b.groupid && textureid == other_textureid && primitivetype < b.primitivetype) return true;
        return false;
    }

protected:
    bool dirty;

    float depth;
    signed int groupid;
    TexturePtr texture;
    unsigned int primitivetype;

    float shadow_depth;
    signed int shadow_groupid;
    TexturePtr shadow_texture;
    unsigned int shadow_primitivetype;
};

} //ns phoenix

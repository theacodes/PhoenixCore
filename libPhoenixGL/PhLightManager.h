#ifndef PHLIGHTMANAGER_H
#define PHLIGHTMANAGER_H

#include <vector>
#include "PhRenderTexture.h"
#include "PhSceneManager.h"

using namespace phoenix;
using namespace std;

namespace phoenix
{

    class PhLight;

    class PhLightManager
    {
    public:

        PhLightManager(PhSceneManager* s, PhVector2d ts = PhVector2d(256,256));
        virtual ~PhLightManager();

        void addLight(PhLight* l);
        void removeLight(PhLight* l);
        void clearLights();

        void generateBuffer();
        void renderBuffer();
        PhTexture* getBuffer();

        PhSceneManager* getSceneManager();

    protected:

        PhRenderTexture* rtexture;
        PhSceneManager* smgr;
        vector<PhLight*> lights;

    private:
    };

}

#include "PhLight.h"

#endif // PHLIGHTMANAGER_H

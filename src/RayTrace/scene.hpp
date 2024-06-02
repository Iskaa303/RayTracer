#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "Image.hpp"
#include "camera.hpp"
#include "./Primatives/objsphere.hpp"
#include "./Primatives/objplane.hpp"
#include "./Lights/pointlight.hpp"

namespace RT
{
    class Scene
    {
        public:
            // The defauls constructor
            Scene();

            // Function to perform 
            bool Render(Image &outputImage);
        
        // Private functions
        private:
            

        // Private members
        private:
            // The camera that we will use
            RT::Camera m_camera;

            // List of objects on the scene
            std::vector<std::shared_ptr<RT::ObjectBase>> m_objectList;

            // List of lights on the scene
            std::vector<std::shared_ptr<RT::LightBase>> m_lightList;
            
    };
}

#endif
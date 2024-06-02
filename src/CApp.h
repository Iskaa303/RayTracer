#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "./RayTrace/Image.hpp"
#include "./RayTrace/scene.hpp"
#include "./RayTrace/camera.hpp"

class CApp
{
    public:
        CApp();

        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event *event);
        void OnLoop();
        void OnRender();
        void OnExit();
    
    private:
        void PrintVector(const Vector<double> &inputVector);
    
    private:
        // An instance of the Image class to store the image
        Image m_image;

        // An instance of the scene class
        RT::Scene m_scene;

        // SDL2 Stuff
        bool isRunning;
        SDL_Window *pWindow;
        SDL_Renderer *pRenderer;
};

#endif
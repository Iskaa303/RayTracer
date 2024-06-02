#include "CApp.h"
#include "./LinAlg/Vector.h"

// The constructor (default)
CApp::CApp()
{
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    pWindow = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if (pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        // Initialize the Image instance
        m_image.Initialize(1280, 720, pRenderer);

        // Set the background color to white
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_RenderClear(pRenderer);

        // Render the scene
        m_scene.Render(m_image);

        // Display the image
        m_image.Display();

        // Show the result
        SDL_RenderPresent(pRenderer);
    }
    else
    {
        return false;
    }

    return true;
}

int CApp::OnExecute()
{
	SDL_Event event;
	
	if (OnInit() == false)
	{
		return -1;
	}
	
	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}
		
		OnLoop();
		OnRender();
	}
	
	OnExit();
	return 0;
}

void CApp::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void CApp::OnLoop()
{

}

void CApp::OnRender()
{
    // Set the background color to white
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    //SDL_RenderClear(pRenderer);

    // Render the scene
    //m_scene.Render(m_image);

    // Display the image
    //m_image.Display();

    // Show the result
    //SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
    // Tidy up SDL2 stuff
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}

// Private Functions
void CApp::PrintVector(const Vector<double> &inputVector)
{
    int nRows = inputVector.GetNumDims();
    for (int row = 0; row < nRows; ++row)
    {
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
    }
}
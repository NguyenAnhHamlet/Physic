#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window (you'd normally also create a renderer)
    SDL_Window* window = SDL_CreateWindow("Mouse Click Detection", 
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);
    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Main game loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) 
            {
                running = false;
            }
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN && 
                       event.button.button == SDL_BUTTON_LEFT) 
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                std::cout << "Left mouse click at (" << x << ", " << y << ")" << std::endl;
            }
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
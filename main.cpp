#include "vector.hpp"
#include "particle.hpp"
#include "particleDrag.hpp"
#include "particleForceRegister.hpp"
#include "particleRegister.hpp"
#include <list>
#include "pfgen.hpp"
#include "forceVisitor.hpp"
#include <ctime>
#include "ball.hpp"
#include <windows.h>
#include <SDL.h>

void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    for (int dy = 1; dy <= radius; ++dy) {
        for (int dx = 1; dx <= radius; ++dx) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
                SDL_RenderDrawPoint(renderer, cx - dx, cy + dy);
                SDL_RenderDrawPoint(renderer, cx + dx, cy - dy);
                SDL_RenderDrawPoint(renderer, cx - dx, cy - dy);
            }
        }
    }
}

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
    PARTICLE* particle = new PARTICLE();
    VECTOR vector(10000, 0, 0);

    particle->setVelocity(vector);
    PARTICLE_DRAG* dragForce = new PARTICLE_DRAG();
    dragForce->setDrag(0.1, 0.1);
    particle->setMass((float)10);

    particle->init();

    PARTICLE_FORCE_REGISTER* forceRegister = new PARTICLE_FORCE_REGISTER();

    std::list<PFGEN*> list{ static_cast<PFGEN*>(dragForce)};
    forceRegister->add(particle,list);

    particle->autoUpdatePos(forceRegister,(float) 0.00023);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Ball Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 2;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 3;
    }

    // Draw a ball (circle)
    int ballRadius = 10;

    while(1)
    {
    // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        int ballX = particle->getPos().x + 200;
        int ballY = particle->getPos().y + 200;
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        for (int i = 0; i < 360; ++i) {
            float angle = i * 3.14159265 / 180.0;
            int x = static_cast<int>(ballX + ballRadius * std::cos(angle));
            int y = static_cast<int>(ballY + ballRadius * std::sin(angle));
            drawFilledCircle(renderer, ballX, ballY, ballRadius, 255, 0, 0, 255);
        }
        // Update the screen
        SDL_RenderPresent(renderer);

        // Wait for a while
        SDL_Delay(16);

    }


    // Quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



#include "base/Vector3D.hpp"
#include "base/particle.hpp"
#include "force/particleDrag.hpp"
#include "force/particleForceRegister.hpp"
#include <list>
#include "force/pfgen.hpp"
#include <ctime>
#include <SDL.h>
#include "render/shape.hpp"
#include "render/renderer.hpp"
#include "common/common.hpp"

int
SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    // CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


int
SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    // CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int main()
{
    RENDERER* render = RENDERER::getInstance();
    SDL_SetRenderDrawColor(render->getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(render->getRenderer());

    // Set the color for the filled circle (e.g., red)
    SDL_SetRenderDrawColor(render->getRenderer(), 255, 0, 0, 255);

    // Define the center and radius of the filled circle
    int centerX = 400;  // Adjust these coordinates based on your window size
    int centerY = 300;
    int radius = 50;

    // Render the filled circle
    SDL_RenderFillCircle(render->getRenderer(), centerX, centerY, radius);

    // Present the renderer to display the rendered content
    SDL_RenderPresent(render->getRenderer());

    // Delay for a short period (you might want to handle events during the delay)
    TIMER::static_delay(1000000, clock());

    return 0;
}


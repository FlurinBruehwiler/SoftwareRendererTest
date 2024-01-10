#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "renderer.h"
#include "structs.h"

int main(int argc, char **argv) {
    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL Example",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH,
                              HEIGHT,
                              0);

    if (window == NULL) {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH,
                                             HEIGHT);
    if (texture == NULL) {
        fprintf(stderr, "Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    void *voidPixels;
    int pitch;
    SDL_LockTexture(texture, NULL, &voidPixels, &pitch);

    pixels = (unsigned int *) voidPixels;
    render();

    SDL_UnlockTexture(texture);

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);

    bool exit = false;
    SDL_Event eventData;
    while (!exit) {
        while (SDL_PollEvent(&eventData)) {
            switch (eventData.type) {
                case SDL_QUIT:
                    exit = true;
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

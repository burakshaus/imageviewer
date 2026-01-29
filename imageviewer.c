#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // FIX: %S -> %s
        printf("SDL Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // FIX: Added 'int' declaration
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        // FIX: %S -> %s
        printf("SDL_image Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // FIX: SDL_WINDIWPOS -> SDL_WINDOWPOS
    SDL_Window* window = SDL_CreateWindow("C Image Viewer", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
        // FIX: %S -> %s
        printf("Window Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer) {
        // FIX: %S -> %s
        printf("Renderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, argv[1]);
    if (!texture) {
        // FIX: prinf -> printf
        printf("Texture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int quit = 0;
    SDL_Event e;
    
    SDL_RenderClear(renderer);
    // FIX: SDL_Render_Copy -> SDL_RenderCopy
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    while (!quit) {
        if (SDL_WaitEvent(&e)) {
            // FIX: SDL_Quit (function) -> SDL_QUIT (constant)
            if (e.type == SDL_QUIT) {
                quit = 1;
            // FIX: SDL_WINDIWEVENT -> SDL_WINDOWEVENT
            } else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

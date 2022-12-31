#include "graphics.h"
#include "zone.h"
#include "player.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char* args[]) {
    srand(time(NULL));

    render_context_init();

    Zone zone = zone_create(100, 100);
    Player player = player_create();

    uint64_t last_tick_time = SDL_GetTicks64();
    SDL_Event e;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    bool quit = false;
    while (!quit) {
        // delta_time
        uint64_t tick_time = SDL_GetTicks64();
        float delta_time = (float)(tick_time - last_tick_time) / 1000;
        last_tick_time = tick_time;

        // events (should be in update fn?) -> probably put in own module at some point
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        break;
                    
                    case SDLK_DOWN:
                        break;
                    
                    case SDLK_LEFT:
                        break;
                    
                    case SDLK_RIGHT:
                        break;
                    
                    default:
                        break;
                }
            }
        }

        player_update(&player, delta_time, keys);

        // drawing
        SDL_RenderClear(render_context->renderer);
        zone_draw(zone);
        player_draw(&player);
        SDL_RenderPresent(render_context->renderer);
    }

    render_context_destroy(render_context);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
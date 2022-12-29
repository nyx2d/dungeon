#include "graphics.h"
#include "zone.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char* args[]) {
	srand(time(NULL));

	Zone zone = zone_create(100, 100);

	RenderContext context = render_context_create();
	uint64_t last_tick_time = SDL_GetTicks64();
	SDL_Event e;

	// load assets, game data, etc
	render_context_load(&context);
	
	bool quit = false;
	while (!quit) {
		// delta_time
		uint64_t tick_time = SDL_GetTicks64();
		float delta_time = (float)(tick_time - last_tick_time) / 1000;
		last_tick_time = tick_time;

		// events (should be in update fn?)
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		// drawing
		SDL_RenderClear(context.renderer);
		zone_draw(zone, context);
		SDL_RenderPresent(context.renderer);
	}

	render_context_destroy(context);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

extern const int MAX_TILE_ID;

typedef struct Camera {
    float x, y;
} Camera;

Camera camera_create();
void camera_update(Camera camera, float delta_time);

typedef struct RenderContext {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *tileset;
    int tileset_width, tileset_height;

    Camera camera;
} RenderContext;

RenderContext render_context_create();
void render_context_load(RenderContext *context);
void render_context_destroy(RenderContext context);

void render_context_draw_tile(RenderContext context, int tile_id, int map_x, int map_y);

#endif
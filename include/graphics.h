#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

extern const int MAX_TILE_ID;

typedef struct Camera {
    float x, y;
} Camera;

typedef struct RenderContext {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *tileset;
    int tileset_width, tileset_height;
} RenderContext;

extern RenderContext *render_context;
extern Camera camera;

void camera_update(Camera camera, float delta_time);
void camera_center(Camera *camera, int tile_x, int tile_y);

void render_context_init(); // populates global render context variable
void render_context_destroy(RenderContext *context);

// graphics functions assume global *render_context is initialized
void graphics_draw_tile(int tile_id, int map_x, int map_y);
void grpahics_draw_tile_floating(int tile_id, float map_x, float map_y);

void graphics_center_camera(int map_x, int map_y);
void graphics_center_camera_floating(float map_x, float map_y);

#endif
#include "graphics.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const SDL_WindowFlags WINDOW_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
const int TILE_SIZE = 12; // w, h in pixels (tiles assumed square)
const char TILESET_PATH[] = "assets/tileset.png";
const int TILESET_ZOOM = 5;

const int MAX_TILE_ID = 599;

Camera camera_create() {
    Camera c = {.x = 200, .y = 200};
    return c;
}

RenderContext render_context_create() {
    RenderContext c = {};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! %s\n", SDL_GetError());
        exit(-1);
    }

    c.window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAGS);
    if (c.window == NULL) {
		printf("Window could not be created! %s\n", SDL_GetError());
        exit(-1);
    }

    c.renderer = SDL_CreateRenderer(c.window, -1, SDL_RENDERER_ACCELERATED);
    if (c.renderer == NULL) {
        printf("Renderer could not be created! %s\n", SDL_GetError());
        exit(-1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(-1);
    } 

    c.camera = camera_create();

    return c;
}

void render_context_load(RenderContext *context) {
    context->tileset = IMG_LoadTexture(context->renderer, TILESET_PATH);
    if (context->tileset == NULL) {
        printf("Tileset could not be loaded! %s\n", IMG_GetError());
        exit(-1);
    }

    if (SDL_QueryTexture(context->tileset, NULL, NULL, &context->tileset_width, &context->tileset_height) < 0) {
        printf("Tileset texture could not be queried! %s\n", IMG_GetError());
        exit(-1);
    }
}

void render_context_destroy(RenderContext context) {
    SDL_DestroyTexture(context.tileset);
    SDL_DestroyRenderer(context.renderer);
    SDL_DestroyWindow(context.window);
}

void render_context_draw_tile(RenderContext context, int tile_id, int map_x, int map_y) {
    int x = map_x * TILE_SIZE * TILESET_ZOOM - context.camera.x;
    int y = map_y * TILE_SIZE * TILESET_ZOOM - context.camera.y;

    int tileset_x = (tile_id * TILE_SIZE) % context.tileset_width;
    int tileset_y = ((tile_id * TILE_SIZE) / context.tileset_width) * TILE_SIZE;

    SDL_Rect tileset_quad = {.x = tileset_x, .y = tileset_y, .w = TILE_SIZE, .h = TILE_SIZE};
    SDL_Rect render_quad = {.x = x, .y = y, .w = TILE_SIZE * TILESET_ZOOM, .h = TILE_SIZE * TILESET_ZOOM};

    SDL_RenderCopy(context.renderer, context.tileset, &tileset_quad, &render_quad);
}
#include "graphics.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const SDL_WindowFlags WINDOW_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
const int TILE_SIZE = 12; // w, h in pixels (tiles assumed square)
const char TILESET_PATH[] = "assets/tileset.png";
const int TILESET_ZOOM = 2;

const int MAX_TILE_ID = 599;

RenderContext *render_context; // global render context, accessed around game
Camera camera = {.x = 0, .y = 0}; // global camera, accessed around game

void render_context_init() {
    render_context = malloc(sizeof *render_context);

    // setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! %s\n", SDL_GetError());
        exit(-1);
    }

    render_context->window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAGS);
    if (render_context->window == NULL) {
        printf("Window could not be created! %s\n", SDL_GetError());
        exit(-1);
    }

    render_context->renderer = SDL_CreateRenderer(render_context->window, -1, SDL_RENDERER_ACCELERATED);
    if (render_context->renderer == NULL) {
        printf("Renderer could not be created! %s\n", SDL_GetError());
        exit(-1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(-1);
    } 

    // load tileset
    render_context->tileset = IMG_LoadTexture(render_context->renderer, TILESET_PATH);
    if (render_context->tileset == NULL) {
        printf("Tileset could not be loaded! %s\n", IMG_GetError());
        exit(-1);
    }

    if (SDL_QueryTexture(render_context->tileset, NULL, NULL, &render_context->tileset_width, &render_context->tileset_height) < 0) {
        printf("Tileset texture could not be queried! %s\n", IMG_GetError());
        exit(-1);
    }
}

void render_context_destroy(RenderContext *context) {
    SDL_DestroyTexture(context->tileset);
    SDL_DestroyRenderer(context->renderer);
    SDL_DestroyWindow(context->window);
    free(context);
}

void graphics_draw_tile(int tile_id, int map_x, int map_y) {
    int x = map_x * TILE_SIZE * TILESET_ZOOM - camera.x;
    int y = map_y * TILE_SIZE * TILESET_ZOOM - camera.y;

    int tileset_x = (tile_id * TILE_SIZE) % render_context->tileset_width;
    int tileset_y = ((tile_id * TILE_SIZE) / render_context->tileset_width) * TILE_SIZE;

    SDL_Rect tileset_quad = {.x = tileset_x, .y = tileset_y, .w = TILE_SIZE, .h = TILE_SIZE};
    SDL_Rect render_quad = {.x = x, .y = y, .w = TILE_SIZE * TILESET_ZOOM, .h = TILE_SIZE * TILESET_ZOOM};

    SDL_RenderCopy(render_context->renderer, render_context->tileset, &tileset_quad, &render_quad);
}

void graphics_center_camera(int map_x, int map_y) {
    int w, h;
    SDL_GetRendererOutputSize(render_context->renderer, &w, &h);
    
    camera.x = map_x * TILE_SIZE * TILESET_ZOOM - (w / 2);
    camera.y = map_y * TILE_SIZE * TILESET_ZOOM - (h / 2); 
}
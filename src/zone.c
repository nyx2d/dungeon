#include "zone.h"
#include "graphics.h"
#include <stdlib.h>

const int GRASS_TILES[] = {291, 292, 294, 79, 252, 253};

Zone zone_create(int width, int height) {
    Zone z = {.width = width, .height = height};
    z.tiles = malloc(sizeof *z.tiles * width * height);
    
    // randomly fill it in
    for (int i = 0; i < width * height; i++) {
        z.tiles[i] = GRASS_TILES[rand() % (sizeof GRASS_TILES / sizeof *GRASS_TILES)]; // grass
    }

    return z;
}

void zone_draw(Zone zone) {
    for (int x = 0; x < zone.width; x++) {
        for (int y = 0; y < zone.height; y++) {
            int tile_id = zone_get_tile_id_at(zone, x, y);
            graphics_draw_tile(tile_id, x, y);
        }
    }
}

int zone_get_tile_id_at(Zone zone, int x, int y) {
    return zone.tiles[(y * zone.width) + x]; // TODO: bounds checking?
}

void zone_destroy(Zone zone) {
    free(zone.tiles);
}
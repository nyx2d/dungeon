#ifndef ZONE_H
#define ZONE_H

#include "graphics.h"

typedef struct Zone {
    int width, height;
    int *tiles;
} Zone;

Zone zone_create(int width, int height);
void zone_draw(Zone zone, RenderContext context);
int zone_get_tile_id_at(Zone zone, int x, int y);
void zone_destroy(Zone zone);

#endif
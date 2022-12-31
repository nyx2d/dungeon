#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include <SDL.h>

typedef struct Player {
    float x, y; // in tile coords
} Player;

Player player_create();
void player_update(Player *player, float delta_time, Uint8 *keys);
void player_draw(Player *player);

#endif
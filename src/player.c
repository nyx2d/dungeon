#include "player.h"
#include "graphics.h"
#include <SDL.h>

const float PLAYER_SPEED = 5; // in tiles per second
const int PLAYER_TILE_ID = 21;

Player player_create() {
    Player p = {.x = 0, .y = 0};
    return p;
}

void player_update(Player *player, float delta_time, Uint8 *keys) {
    if (keys[SDL_SCANCODE_RIGHT]) {
        player->x += PLAYER_SPEED * delta_time;
    } else if (keys[SDL_SCANCODE_LEFT]) {
        player->x -= PLAYER_SPEED * delta_time;
    }

    if (keys[SDL_SCANCODE_UP]) {
        player->y -= PLAYER_SPEED * delta_time;
    } else if (keys[SDL_SCANCODE_DOWN]) {
        player->y += PLAYER_SPEED * delta_time;
    }

    // center camera on player
    graphics_center_camera((int) player->x, (int) player->y);
}

void player_draw(Player *player) {
    int tile_x = (int)player->x;
    int tile_y = (int)player->y;
    graphics_draw_tile(PLAYER_TILE_ID, tile_x, tile_y);
}
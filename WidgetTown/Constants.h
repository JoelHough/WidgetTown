#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace {
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;

    const int TILE_WIDTH = 32;
    const int TILE_HEIGHT = 32;

    const int LAYER_COUNT = 4;
    const int CHARACTER_LAYER = 2;
    const int ITEM_LAYER = 2;

    const int CHARACTER_SHEET_ANIMS = 4;
    const int CHARACTER_SHEET_FRAMES = 3;
    const int CHARACTER_SHEET_WALK_UP_ANIM = 0;
    const int CHARACTER_SHEET_WALK_RIGHT_ANIM = 1;
    const int CHARACTER_SHEET_WALK_DOWN_ANIM = 2;
    const int CHARACTER_SHEET_WALK_LEFT_ANIM = 3;
    const int CHARACTER_SHEET_WALK_FRAMES[] = {1, 0, 1, 2};
    const int CHARACTER_SHEET_WALK_FRAME_COUNT = 4;
    const double CHARACTER_FRAME_TIME = 0.25;

    const double CHARACTER_SPEED = 78.0;
}
#endif // CONSTANTS_H

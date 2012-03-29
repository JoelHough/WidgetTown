#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace {
  // Map size, in tiles
  const int MAP_WIDTH = 100;
  const int MAP_HEIGHT = 100;

  // Tile size, in pixels
  const int TILE_WIDTH = 32;
  const int TILE_HEIGHT = 32;

  // Layer values
  const int LAYER_COUNT = 4;
  const int CHARACTER_LAYER = 2;
  const int ITEM_LAYER = 2;

  // Everything you ever wanted to know about character animation
  const int CHARACTER_SHEET_ANIMS = 4; // Number of animations in the sheet
  const int CHARACTER_SHEET_FRAMES = 3; // Number of frames in each animation
  const int CHARACTER_SHEET_DEFAULT_ANIM = -1; // Tells the object "Don't care, pick one."

  // Anim aliases.  These equal the row on the charsheet the animation is on.
  const int CHARACTER_SHEET_WALK_UP_ANIM = 0;
  const int CHARACTER_SHEET_WALK_RIGHT_ANIM = 1;
  const int CHARACTER_SHEET_WALK_DOWN_ANIM = 2;
  const int CHARACTER_SHEET_WALK_LEFT_ANIM = 3;
  
const int CHARACTER_SHEET_DEFAULT_FRAME = -1; // Tells the object "Don't care, pick one."
  
  // Frames correspond to the column on the charsheet.
  const int CHARACTER_SHEET_WALK_FRAMES[] = {1, 0, 1, 2}; // The walking cycle
  const int CHARACTER_SHEET_WALK_FRAME_COUNT = 4; //Number of walking frames

  const double CHARACTER_FRAME_TIME = 0.25; // How long each frame takes, in seconds.

  const double CHARACTER_SPEED = 78.0; // Character speed, in pixels/second
}
#endif // CONSTANTS_H

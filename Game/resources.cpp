
#include "resources.h"

std::vector<ALLEGRO_BITMAP*> GameResources::BackgroundTiles;


void GameResources::DrawTank(int Colour, int X, int Y, Angle Rotation)
{
  ALLEGRO_BITMAP* t;

  switch( Colour )
  {
    case 0:
      t = BitmapCache::LoadBitmap("resources/tankRed.png");
      break;
    case 1:
      t = BitmapCache::LoadBitmap("resources/tankGreen.png");
      break;
    case 2:
      t = BitmapCache::LoadBitmap("resources/tankBlue.png");
      break;
  }
  if( Rotation.ToDegrees() == 0 )
  {
    al_draw_bitmap( t, X - (al_get_bitmap_width( t ) / 2), Y - (al_get_bitmap_height( t ) / 2), 0 );
  } else {
    al_draw_rotated_bitmap( t, (al_get_bitmap_width( t ) / 2), (al_get_bitmap_height( t ) / 2), X, Y, Rotation.ToRadians(), 0 );
  }

  BitmapCache::UnloadBitmap( t );

  switch( Colour )
  {
    case 2:
      t = BitmapCache::LoadBitmap("resources/barrelRed.png");
      break;
    case 0:
      t = BitmapCache::LoadBitmap("resources/barrelGreen.png");
      break;
    case 1:
      t = BitmapCache::LoadBitmap("resources/barrelBlue.png");
      break;
  }
  if( Rotation.ToDegrees() == 0 )
  {
    al_draw_bitmap( t, X - (al_get_bitmap_width( t ) / 2), Y - al_get_bitmap_height( t ) + 10, 0 );
  } else {
    al_draw_rotated_bitmap( t, (al_get_bitmap_width( t ) / 2), al_get_bitmap_height( t ) - 10, X, Y, Rotation.ToRadians(), 0 );
  }
  BitmapCache::UnloadBitmap( t );

}

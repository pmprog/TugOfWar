
#include "resources.h"

std::vector<ALLEGRO_BITMAP*> GameResources::BackgroundTiles;
SpriteSheet* GameResources::BluePanel;
SpriteSheet* GameResources::RedPanel;
SpriteSheet* GameResources::CombinedButtons;

void GameResources::InitResources()
{
	BluePanel = new SpriteSheet( "resources/metalPanel_blueCorner.png", 30, 30 );
	RedPanel = new SpriteSheet( "resources/metalPanel_redCorner.png", 30, 30 );

	CombinedButtons = new SpriteSheet( "resources/buttonsCombined.png", 16, 16 );
}

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
		default:
			return;
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


void GameResources::DrawPanel(SpriteSheet* Graphics, int X, int Y, int TilesWide, int TilesHigh, int HeaderTilesWide)
{
	al_hold_bitmap_drawing( true );
	for( int y = 0; y < TilesHigh; y++ )
	{
		for( int x = 0; x < TilesWide; x++ )
		{
			if( y <= 1 )
			{
				if( x == 0 )
				{
					Graphics->DrawSprite( y * 5, X + (x *30), Y + (y * 30) );
				} else if( x == TilesWide - 1) {
					Graphics->DrawSprite( (y * 5) + 4, X + (x * 30), Y + (y * 30) );
				} else if( x < HeaderTilesWide ) {
					Graphics->DrawSprite( (y * 5) + 1, X + (x * 30), Y + (y * 30) );
				} else if( x == HeaderTilesWide ) {
					Graphics->DrawSprite( (y * 5) + 2, X + (x * 30), Y + (y * 30) );
				} else {
					Graphics->DrawSprite( (y * 5) + 3, X + (x * 30), Y + (y * 30) );
				}
			} else if( y == TilesHigh - 1 ) {
				if( x == 0 )
				{
					Graphics->DrawSprite( 20, X + (x * 30), Y + (y * 30) );
				} else if( x == TilesWide - 1) {
					Graphics->DrawSprite( 24, X + (x * 30), Y + (y * 30) );
				} else {
					Graphics->DrawSprite( 21, X + (x * 30), Y + (y * 30) );
				}
			} else {
				if( x == 0 )
				{
					Graphics->DrawSprite( 10, X + (x * 30), Y + (y * 30) );
				} else if( x == TilesWide - 1) {
					Graphics->DrawSprite( 9, X + (x * 30), Y + (y * 30) );
				} else {
					Graphics->DrawSprite( 8, X + (x * 30), Y + (y * 30) );
				}
			}
		}
	}
	al_hold_bitmap_drawing( false );
}

void GameResources::DrawButton(ButtonColours::Colours Colour, bool IsRaised, int X, int Y, int TilesWide, int TilesHigh)
{
	al_hold_bitmap_drawing( true );
	for( int y = 0; y < TilesHigh; y++ )
	{
		for( int x = 0; x < TilesWide; x++ )
		{
			if( y == 0 )
			{
				if( x == 0 )
				{
					CombinedButtons->DrawSprite( 0 + (3 * Colour) + (!IsRaised ? 36 : 0), X + (x *16), Y + (y * 16) );
				} else if( x == TilesWide - 1) {
					CombinedButtons->DrawSprite( 2 + (3 * Colour) + (!IsRaised ? 36 : 0), X + (x * 16), Y + (y * 16) );
				} else {
					CombinedButtons->DrawSprite( 1 + (3 * Colour) + (!IsRaised ? 36 : 0), X + (x * 16), Y + (y * 16) );
				}
			} else if( y == TilesHigh - 1 ) {
				if( x == 0 )
				{
					CombinedButtons->DrawSprite( 24 + (3 * Colour) + (!IsRaised ? 24 : 0), X + (x * 16), Y + (y * 16) );
				} else if( x == TilesWide - 1) {
					CombinedButtons->DrawSprite( 26 + (3 * Colour) + (!IsRaised ? 24 : 0), X + (x * 16), Y + (y * 16) );
				} else {
					CombinedButtons->DrawSprite( 25 + (3 * Colour) + (!IsRaised ? 24 : 0), X + (x * 16), Y + (y * 16) );
				}
			} else {
				if( x == 0 )
				{
					CombinedButtons->DrawSprite( 12 + (3 * Colour), X + (x * 16), Y + (y * 16) );
				} else if( x == TilesWide - 1) {
					CombinedButtons->DrawSprite( 14 + (3 * Colour), X + (x * 16), Y + (y * 16) );
				} else {
					CombinedButtons->DrawSprite( 13 + (3 * Colour), X + (x * 16), Y + (y * 16) );
				}
			}
		}
	}
	al_hold_bitmap_drawing( false );
}

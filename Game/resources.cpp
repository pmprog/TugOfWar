
#include "resources.h"

std::vector<ALLEGRO_BITMAP*> GameResources::BackgroundTiles;
SpriteSheet* GameResources::BluePanel;
SpriteSheet* GameResources::RedPanel;
SpriteSheet* GameResources::WhiteButtonUp;
SpriteSheet* GameResources::WhiteButtonDown;
SpriteSheet* GameResources::BlueButtonUp;
SpriteSheet* GameResources::BlueButtonDown;
SpriteSheet* GameResources::RedButtonUp;
SpriteSheet* GameResources::RedButtonDown;

void GameResources::InitResources()
{
	BluePanel = new SpriteSheet( "resources/metalPanel_blueCorner.png", 30, 30 );
	RedPanel = new SpriteSheet( "resources/metalPanel_redCorner.png", 30, 30 );
	
	WhiteButtonUp = new SpriteSheet( "resources/buttonGrey01.png" );
	WhiteButtonUp->AddSprite( 0, 0, 16, 16 );
	WhiteButtonUp->AddSprite( 16, 0, 16, 16 );
	WhiteButtonUp->AddSprite( al_get_bitmap_width( WhiteButtonUp->GetSheet() ) - 16, 0, 16, 16 );
	WhiteButtonUp->AddSprite( 0, 16, 16, 16 );
	WhiteButtonUp->AddSprite( 16, 16, 16, 16 );
	WhiteButtonUp->AddSprite( al_get_bitmap_width( WhiteButtonUp->GetSheet() ) - 16, 16, 16, 16 );
	WhiteButtonUp->AddSprite( 0, al_get_bitmap_height( WhiteButtonUp->GetSheet() ) - 16, 16, 16 );
	WhiteButtonUp->AddSprite( 16, al_get_bitmap_height( WhiteButtonUp->GetSheet() ) - 16, 16, 16 );
	WhiteButtonUp->AddSprite( al_get_bitmap_width( WhiteButtonUp->GetSheet() ) - 16, al_get_bitmap_height( WhiteButtonUp->GetSheet() ) - 16, 16, 16 );
	WhiteButtonDown = WhiteButtonUp->CloneTo( "resources/buttonGrey02.png" );
	BlueButtonUp = WhiteButtonUp->CloneTo( "resources/buttonBlue01.png" );
	BlueButtonDown = WhiteButtonUp->CloneTo( "resources/buttonBlue02.png" );
	RedButtonUp = WhiteButtonUp->CloneTo( "resources/buttonRed01.png" );
	RedButtonDown = WhiteButtonUp->CloneTo( "resources/buttonRed02.png" );
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

void GameResources::DrawButton(SpriteSheet* Graphics, int X, int Y, int TilesWide, int TilesHigh)
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
					Graphics->DrawSprite( 0, X + (x *16), Y + (y * 16) );
				} else if( x == TilesWide - 1) {
					Graphics->DrawSprite( 2, X + (x * 16), Y + (y * 16) );
				} else {
					Graphics->DrawSprite( 1, X + (x * 16), Y + (y * 16) );
				}
			} else if( y == TilesHigh - 1 ) {
				if( x == 0 )
				{
					Graphics->DrawSprite( 6, X + (x * 16), Y + (y * 16) );
				} else if( x == TilesWide - 1) {
					Graphics->DrawSprite( 8, X + (x * 16), Y + (y * 16) );
				} else {
					Graphics->DrawSprite( 7, X + (x * 16), Y + (y * 16) );
				}
			} else {
				if( x == 0 )
				{
					Graphics->DrawSprite( 3, X + (x * 16), Y + (y * 16) );
				} else if( x == TilesWide - 1) {
					Graphics->DrawSprite( 5, X + (x * 16), Y + (y * 16) );
				} else {
					Graphics->DrawSprite( 4, X + (x * 16), Y + (y * 16) );
				}
			}
		}
	}
	al_hold_bitmap_drawing( false );
}
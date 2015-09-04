
#include "boot.h"
#include "resources.h"
#include "menu.h"
#include "../Framework/Primitives/easing.h"

bool BootUp::loadingComplete = false;

void BootUp::Begin()
{
	srand( al_get_time() );
	DISPLAY->SetTitle("Tug Of War");
	bootBarSize = 0;
	bootBarAdjust = (DISPLAY->GetWidth() / (FRAMEWORK->GetFramesPerSecond() * 1.75f));

  logoFadeOut = false;
	logoSprite = BitmapCache::LoadBitmap("resources/polymath.png");
	logoFadeIn = 0;

	BitmapCache::SetLoadMode( true );
#ifndef NOTHREADLOAD
	loadingthread = al_create_thread( ThreadedLoad, nullptr );
	al_start_thread( loadingthread );
#endif
}

void BootUp::Pause()
{
}

void BootUp::Resume()
{
}

void BootUp::Finish()
{
}

void BootUp::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
		} else if( loadingComplete ) {
			// StartGame();
			logoFadeOut = true;
		}
	}
}

void BootUp::Update()
{
  if( logoFadeOut )
  {
    logoFadeIn--;
  } else {
		if( logoFadeIn < 50 )
		{
			logoFadeIn++;
		}
  }

	if( bootBarSize < DISPLAY->GetWidth() )
	{
		bootBarSize += bootBarAdjust;
	}

#ifdef NOTHREADLOAD
	// Don't thread loading in Pandora
	if( !loadingComplete )
	{
		ThreadedLoad( nullptr, nullptr );
	}
#endif

	// Only allow completion when all resources are loaded
	if( loadingComplete && bootBarSize >= DISPLAY->GetWidth() && !logoFadeOut )
	{
		// StartGame();
		logoFadeOut = true;
		logoFadeIn = 50;
	}

	if( logoFadeOut && logoFadeIn <= 0 )
  {
    StartGame();
  }
}

void BootUp::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	int logoh = al_get_bitmap_height(logoSprite);
	int logox = (DISPLAY->GetWidth() - al_get_bitmap_width(logoSprite)) / 2;
	int logoy = (DISPLAY->GetHeight() - logoh) / 2;

	al_draw_bitmap( logoSprite, logox, Easing::EaseOutBounce( logoFadeIn, -logoh, logoy + logoh, 50 ), 0 ); // logoy, 0 );

	int xPos = (DISPLAY->GetWidth() / 2) - (bootBarSize / 2);
	int yPos = DISPLAY->GetHeight() - 24;
	al_draw_filled_rectangle( xPos, yPos, xPos + bootBarSize, yPos + 12, al_map_rgb( 255, 144, 64 ) );
}

void BootUp::StartGame()
{
#ifndef NOTHREADLOAD
	BitmapCache::SetLoadMode( false );
	BitmapCache::UploadToVideo();
#endif
	delete Framework::System->ProgramStages->Pop();
	Framework::System->ProgramStages->Push( new Menu() );
}

bool BootUp::IsTransition()
{
	return false;
}

void* BootUp::ThreadedLoad( ALLEGRO_THREAD*, void* )
{
	// Load all resources for caching

	BitmapCache::LoadBitmap("resources/pcBlack.png");
	BitmapCache::LoadBitmap("resources/pcWhite.png");
	BitmapCache::LoadBitmap("resources/helpBlack.png");
	BitmapCache::LoadBitmap("resources/helpWhite.png");
	BitmapCache::LoadBitmap("resources/settingsBlack.png");
	BitmapCache::LoadBitmap("resources/settingsWhite.png");
	BitmapCache::LoadBitmap("resources/exitBlack.png");
	BitmapCache::LoadBitmap("resources/exitWhite.png");

	BitmapCache::LoadBitmap("resources/metalPanel_blueCorner.png");
	BitmapCache::LoadBitmap("resources/metalPanel_redCorner.png");


	GameResources::BackgroundTiles.push_back( BitmapCache::LoadBitmap("resources/grass.png") );
	GameResources::BackgroundTiles.push_back( BitmapCache::LoadBitmap("resources/sand.png") );
	GameResources::BackgroundTiles.push_back( BitmapCache::LoadBitmap("resources/dirt.png") );

	BitmapCache::LoadBitmap("resources/tankBlue.png");
	BitmapCache::LoadBitmap("resources/tankGreen.png");
	BitmapCache::LoadBitmap("resources/tankRed.png");
	BitmapCache::LoadBitmap("resources/barrelBlue.png");
	BitmapCache::LoadBitmap("resources/barrelGreen.png");
	BitmapCache::LoadBitmap("resources/barrelRed.png");
	BitmapCache::LoadBitmap("resources/bulletYellowSilver.png");

	BitmapCache::LoadBitmap("resources/smokeGrey0.png");
	BitmapCache::LoadBitmap("resources/smokeGrey4.png");
	BitmapCache::LoadBitmap("resources/smokeGrey5.png");

	BitmapCache::LoadBitmap("resources/singleplayer.png");
	BitmapCache::LoadBitmap("resources/multiplayer.png");
	BitmapCache::LoadBitmap("resources/massiveMultiplayer.png");

	BitmapCache::LoadBitmap("resources/gamepad1.png");
	BitmapCache::LoadBitmap("resources/gamepad2.png");
	BitmapCache::LoadBitmap("resources/gamepad3.png");
	BitmapCache::LoadBitmap("resources/gamepad4.png");


	loadingComplete = true;
	return nullptr;
}

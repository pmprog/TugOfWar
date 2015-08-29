
#include "boot.h"
#include "resources.h"
#include "menu.h"

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

	loadingthread = al_create_thread( ThreadedLoad, nullptr );
	al_start_thread( loadingthread );
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
    logoFadeIn++;
  }

	if( logoFadeIn > 40 )
  {
  } else if( logoFadeIn > 37 ) {
  } else if( logoFadeIn > 34 ) {
  } else if( logoFadeIn > 31 ) {
  } else if( logoFadeIn > 28 ) {
  } else if( logoFadeIn > 25 ) {
  } else {
  }

	if( bootBarSize < DISPLAY->GetWidth() )
	{
		bootBarSize += bootBarAdjust;
	}

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

	int logox = (DISPLAY->GetWidth() - al_get_bitmap_width(logoSprite)) / 2;
	int logoy = (DISPLAY->GetHeight() - al_get_bitmap_height(logoSprite)) / 2;

	al_draw_bitmap( logoSprite, logox, logoy, 0 );

	int xPos = (DISPLAY->GetWidth() / 2) - (bootBarSize / 2);
	int yPos = DISPLAY->GetHeight() - 24;
	al_draw_filled_rectangle( xPos, yPos, xPos + bootBarSize, yPos + 12, al_map_rgb( 255, 144, 64 ) );
}

void BootUp::StartGame()
{
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
	// ALLEGRO_BITMAP* bkg = BitmapCache::LoadBitmap("resources/ui_background.png");
	GameResources::BackgroundTiles.push_back( BitmapCache::LoadBitmap("resources/grass.png") );
	GameResources::BackgroundTiles.push_back( BitmapCache::LoadBitmap("resources/sand.png") );
	GameResources::BackgroundTiles.push_back( BitmapCache::LoadBitmap("resources/dirt.png") );

	loadingComplete = true;
	return nullptr;
}

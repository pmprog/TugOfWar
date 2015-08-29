
#include "menu.h"
#include "debugstage.h"
#include "gamestage.h"

void Menu::Begin()
{
	backgroundindex = rand() % 3;
	menutime = 0;

	titlefont = FontCache::LoadFont( "resources/armalite.ttf", 80 );
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );

	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_intro [1].ogg", true );
}

void Menu::Pause()
{
  AUDIO->StopMusic();
}

void Menu::Resume()
{
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_intro [1].ogg", true );
}

void Menu::Finish()
{
	AUDIO->StopMusic();
}

void Menu::EventOccurred(Event *e)
{
	bool activateoption = false;

	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			FRAMEWORK->ShutdownFramework();
			return;
		}

		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_SPACE )
    {
      // FRAMEWORK->ProgramStages->Push( new GameStage() );
      return;
    }
	}

}

void Menu::Update()
{
	menutime++;
}

void Menu::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0 ,0 ) );

	
	int bx = 0;
	int by = 0;
	int iw = al_get_bitmap_width( GameResources::BackgroundTiles.at(backgroundindex) );
	int ih = al_get_bitmap_height( GameResources::BackgroundTiles.at(backgroundindex) );
	while( by < DISPLAY->GetHeight() )
	{
		while( bx < DISPLAY->GetWidth() )
		{
			al_draw_bitmap( GameResources::BackgroundTiles.at(backgroundindex), bx, by, 0 );
			bx += iw;
		}
		by += ih;
		bx = 0;
	}

	titlefont->DrawString( (DISPLAY->GetWidth() / 2) + 4, 24, "Tug Of War!", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	titlefont->DrawString( DISPLAY->GetWidth() / 2, 20, "Tug Of War!", FontHAlign::CENTRE, al_map_rgb( 255, 255, 0 ) );

	optionfont->DrawString( DISPLAY->GetWidth() / 2, 420, "Local Game", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
	//optionfont->DrawString( DISPLAY->GetWidth() / 2, 260, "Network Game", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
	//optionfont->DrawString( DISPLAY->GetWidth() / 2, 280, "Help", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
	//optionfont->DrawString( DISPLAY->GetWidth() / 2, 300, "Quit", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );

}

bool Menu::IsTransition()
{
	return false;
}

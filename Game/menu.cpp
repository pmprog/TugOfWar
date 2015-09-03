
#include "menu.h"
#include "localsetupstage.h"
#include "helpstage.h"
#include "../Framework/Primitives/easing.h"

void Menu::Begin()
{
	menutime = 0;
	sliderindex = 0;
	slidertarget = 0;
	rendertime = 0;

	titlefont = FontCache::LoadFont( "resources/armalite.ttf", 80 );
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );

    background = nullptr;
    GenerateBackground();

	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_intro [1].ogg", true );
}

void Menu::Pause()
{
  AUDIO->StopMusic();
}

void Menu::Resume()
{
    // GenerateBackground();
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_intro [1].ogg", true );
}

void Menu::Finish()
{
	al_destroy_bitmap( background );
	AUDIO->StopMusic();
}

void Menu::EventOccurred(Event *e)
{
	bool activateoption = false;

	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			// FRAMEWORK->ShutdownFramework();
			FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::SPIRAL_INWARDS, 6, 6 ) );
			return;
		}

		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_LEFT )
    {
			sliderstart = menutime;
			sliderprevious = sliderindex;
      // FRAMEWORK->ProgramStages->Push( new GameStage() );
			slidertarget = slidertarget - 400;
      return;
    }
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_RIGHT )
    {
			sliderstart = menutime;
			sliderprevious = sliderindex;
      // FRAMEWORK->ProgramStages->Push( new GameStage() );
			slidertarget = slidertarget + 400;
      return;
    }

		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_SPACE || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ENTER || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_PGDN || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_PGUP || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_HOME || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_END || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_LCTRL || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ALT )
    {
			switch( slidertarget )
			{
				case 0:
					// Local
					FRAMEWORK->ProgramStages->Push( new TransitionTiled( new LocalSetupStage(), TiledTransitions::NORTHWEST_TO_SOUTHEAST, 12, 12 ) );
					break;
				case 400:
					// Network
					break;
				case 800:
					// Help
					FRAMEWORK->ProgramStages->Push( new TransitionStrips( new HelpStage(), FRAMEWORK->GetFramesPerSecond() / 2, 6 )  );
					break;
				case 1200:
					// Quit
					// FRAMEWORK->ShutdownFramework();
					FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::SPIRAL_INWARDS, 6, 6 ) );
					break;
			}
      return;
    }
	}

}

void Menu::Update()
{
	menutime++;

	int sliderdiff = 0;
	if( sliderindex != slidertarget )
	{
		sliderindex = Easing::EaseOutBack( menutime - sliderstart, sliderprevious, slidertarget - sliderprevious, FRAMEWORK->GetFramesPerSecond(), 0 );
	}
	if( sliderindex > 1200 && slidertarget == 1600 )
	{
		sliderprevious -= 1600;
		sliderindex -= 1600;
		slidertarget = 0;
	} else if( sliderindex < 0 && slidertarget == -400 ) {
		sliderprevious += 1600;
		sliderindex += 1600;
		slidertarget = 1200;
	}

}

void Menu::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0 ,0 ) );

	int iw = al_get_bitmap_width( GameResources::BackgroundTiles.at(backgroundindex) );

	al_draw_bitmap( background, -(menutime % iw), 0, 0 );

	titlefont->DrawString( (DISPLAY->GetWidth() / 2) + 4, 24, "Tug Of War!", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	titlefont->DrawString( DISPLAY->GetWidth() / 2, 20, "Tug Of War!", FontHAlign::CENTRE, al_map_rgb( 255, 255, 0 ) );

	optionfont->DrawString( (DISPLAY->GetWidth() / 2) - sliderindex, 420, "Local Game", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 400 - sliderindex, 420, "Network", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 800 - sliderindex, 420, "Help", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 1200 - sliderindex, 420, "Quit", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 1600 - sliderindex, 420, "Local Game", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2) - 400 - sliderindex, 420, "Quit", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );

}

bool Menu::IsTransition()
{
	return false;
}

void Menu::GenerateBackground()
{
	backgroundindex = rand() % 3;

	if( background == nullptr )
    {
        background = al_create_bitmap( 1024, 512 );
    }
	DISPLAY->SetTarget( background );

	int iw = al_get_bitmap_width( GameResources::BackgroundTiles.at(backgroundindex) );
	int ih = al_get_bitmap_height( GameResources::BackgroundTiles.at(backgroundindex) );
	int bx = 0;
	int by = 0;

	al_hold_bitmap_drawing( true );
	while( by < 512 )
	{
		while( bx < 1024 )
		{
			al_draw_bitmap( GameResources::BackgroundTiles.at(backgroundindex), bx, by, 0 );
			bx += iw;
		}
		by += ih;
		bx = 0;
	}
	al_hold_bitmap_drawing( false );

	DISPLAY->ClearTarget();
}

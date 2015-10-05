
#include "menu_net.h"
#include "gamelobbystage.h"
#include "helpstage.h"
#include "../Framework/Primitives/easing.h"
#include "input.h"

void NetworkMenu::Begin()
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

void NetworkMenu::Pause()
{
  AUDIO->StopMusic();
}

void NetworkMenu::Resume()
{
    // GenerateBackground();
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_intro [1].ogg", true );
}

void NetworkMenu::Finish()
{
	al_destroy_bitmap( background );
	AUDIO->StopMusic();
}

void NetworkMenu::EventOccurred(Event *e)
{
	bool activateoption = false;

	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::SPIRAL_INWARDS, 7, 7 ) );
			return;
		}

		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_LEFT )
    {
			sliderstart = menutime;
			sliderprevious = sliderindex;
			slidertarget = slidertarget - MENU_SPACING;
      return;
    }
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_RIGHT )
    {
			sliderstart = menutime;
			sliderprevious = sliderindex;
			slidertarget = slidertarget + MENU_SPACING;
      return;
    }

		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_SPACE || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ENTER || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_PGDN || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_PGUP || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_HOME || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_END || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_LCTRL || e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ALT )
    {
			switch( slidertarget / MENU_SPACING )
			{
				case 0:
					// Local
					FRAMEWORK->ProgramStages->Push( new TransitionTiled( new GameLobbyStage(), TiledTransitions::NORTHWEST_TO_SOUTHEAST, 12, 12 ) );
					break;
				case 1:
					// Network
					break;
				case 2:
					// Help
					FRAMEWORK->ProgramStages->Push( new TransitionStrips( new HelpStage(), FRAMEWORK->GetFramesPerSecond() / 2, 12 )  );
					break;
				case 3:
					// Settings
					break;
				case 4:
					// Quit
					FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::SPIRAL_INWARDS, 7, 7 ) );
					break;
			}
      return;
    }
	}

}

void NetworkMenu::Update()
{
	menutime++;

	int sliderdiff = 0;
	if( sliderindex != slidertarget )
	{
		sliderindex = Easing::EaseOutBack( menutime - sliderstart, sliderprevious, slidertarget - sliderprevious, FRAMEWORK->GetFramesPerSecond(), 0 );
	}
	if( sliderindex > (MENU_SPACING * 4) && slidertarget == (MENU_SPACING * 5) )
	{
		sliderprevious -= (MENU_SPACING * 5);
		sliderindex -= (MENU_SPACING * 5);
		slidertarget = 0;
	} else if( sliderindex < 0 && slidertarget == -MENU_SPACING ) {
		sliderprevious += (MENU_SPACING * 5);
		sliderindex += (MENU_SPACING * 5);
		slidertarget = (MENU_SPACING * 4);
	}

}

void NetworkMenu::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0 ,0 ) );

	int iw = al_get_bitmap_width( GameResources::BackgroundTiles.at(backgroundindex) );

	al_draw_bitmap( background, -(menutime % iw), 0, 0 );

	titlefont->DrawString( (DISPLAY->GetWidth() / 2) + 4, 24, "Tug Of War!", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	titlefont->DrawString( DISPLAY->GetWidth() / 2, 20, "Tug Of War!", FontHAlign::CENTRE, al_map_rgb( 255, 255, 0 ) );

	int centrepos = (DISPLAY->GetWidth() / 2) - sliderindex;
	RenderQuit( centrepos - (MENU_SPACING) );
	RenderLocal( centrepos );
	RenderNetwork( centrepos + (MENU_SPACING) );
	RenderHelp( centrepos + (MENU_SPACING * 2) );
	RenderSettings( centrepos + (MENU_SPACING * 3) );
	RenderQuit( centrepos + (MENU_SPACING * 4) );
	RenderLocal( centrepos + (MENU_SPACING * 5) );

	if( menutime % FRAMEWORK->GetFramesPerSecond() < (FRAMEWORK->GetFramesPerSecond() / 2) )
	{
		al_draw_bitmap( Input::GetIcon( InputItems::LEFT ), 10, 420, 0 );
		al_draw_bitmap( Input::GetIcon( InputItems::RIGHT ), 740, 420, 0 );
	}

}

void NetworkMenu::RenderLocal(int X)
{
	if( X - (MENU_SPACING / 2) >= DISPLAY->GetWidth() || X + (MENU_SPACING / 2) <= 0 )
	{
		return;
	}
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/pcBlack.png" ), X + 4 - 110, 124, 0 );
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/pcWhite.png" ), X - 110, 120, 0 );

	optionfont->DrawString( X + 4, 424, "Local Game", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( X, 420, "Local Game", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
}

void NetworkMenu::RenderNetwork(int X)
{
	if( X - (MENU_SPACING / 2) >= DISPLAY->GetWidth() || X + (MENU_SPACING / 2) <= 0 )
	{
		return;
	}
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/pcBlack.png" ), X - 220, 124, 0 );
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/pcWhite.png" ), X - 224, 120, 0 );
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/pcBlack.png" ), X + 8, 124, 0 );
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/pcWhite.png" ), X + 4, 120, 0 );
	optionfont->DrawString( X + 4, 424, "Network", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( X, 420, "Network", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );

}

void NetworkMenu::RenderHelp(int X)
{
	if( X - (MENU_SPACING / 2) >= DISPLAY->GetWidth() || X + (MENU_SPACING / 2) <= 0 )
	{
		return;
	}
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/helpBlack.png" ), X + 4 - 85, 124, 0 );
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/helpWhite.png" ), X - 85, 120, 0 );

	optionfont->DrawString( X + 4, 424, "Help", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( X, 420, "Help", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
}

void NetworkMenu::RenderSettings(int X)
{
	if( X - (MENU_SPACING / 2) >= DISPLAY->GetWidth() || X + (MENU_SPACING / 2) <= 0 )
	{
		return;
	}
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/settingsBlack.png" ), X + 4 - 141, 124, 0 );
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/settingsWhite.png" ), X - 141, 120, 0 );

	optionfont->DrawString( X + 4, 424, "Settings", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( X, 420, "Settings", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
}

void NetworkMenu::RenderQuit(int X)
{
	if( X - (MENU_SPACING / 2) >= DISPLAY->GetWidth() || X + (MENU_SPACING / 2) <= 0 )
	{
		return;
	}
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/exitBlack.png" ), X + 4 - 106, 124, 0 );
	al_draw_bitmap( BitmapCache::LoadBitmap( "resources/exitWhite.png" ), X - 106, 120, 0 );
	optionfont->DrawString( X + 4, 424, "Quit", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( X, 420, "Quit", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
}

bool NetworkMenu::IsTransition()
{
	return false;
}

void NetworkMenu::GenerateBackground()
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

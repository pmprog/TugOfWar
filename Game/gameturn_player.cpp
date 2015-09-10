
#include "gameturn_player.h"

GameTurnPlayerStage::GameTurnPlayerStage( GameStage* Owner, PlayerInfo* Player )
{
	currentgame = Owner;
	currentplayer = Player;
	GenerateBackground();
}

void GameTurnPlayerStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	playeracknowledgedturn = false;
}

void GameTurnPlayerStage::Pause()
{
}

void GameTurnPlayerStage::Resume()
{
}

void GameTurnPlayerStage::Finish()
{
}

void GameTurnPlayerStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
			return;
		}

		if( !playeracknowledgedturn )
		{
			playeracknowledgedturn = true;
		} else {

			// TODO: Handle keys

		}
	}
}

void GameTurnPlayerStage::Update()
{
}

void GameTurnPlayerStage::Render()
{
	if( playeracknowledgedturn )
	{
		currentgame->Render();
		al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );

		al_draw_filled_rectangle( 0, 150, DISPLAY->GetWidth(), 330, ( currentplayer->BlueTeam ? al_map_rgb( 30, 167, 225 ) : al_map_rgb( 232, 106, 23 ) ) );
		optionfont->DrawString( 404, 279 - optionfont->GetFontHeight(), currentplayer->Name, FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
		optionfont->DrawString( 400, 275 - optionfont->GetFontHeight(), currentplayer->Name, FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
		optionfont->DrawString( 404, 289, "Press any key", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
		optionfont->DrawString( 400, 285, "Press any key", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );

	} else {

		al_draw_bitmap( background, 0, 0, 0 );

		for( int y = 0; y < 6; y++ )
		{
			al_draw_line( 15, 15 + (y * 90), 465, 15 + (y * 90), al_map_rgb( 255, 255, 255 ), 3 );
			al_draw_line( 15 + (y * 90), 15, 15 + (y * 90), 465, al_map_rgb( 255, 255, 255 ), 3 );
		}

		GameResources::DrawPanel( (currentplayer->BlueTeam ? GameResources::BluePanel : GameResources::RedPanel ), 480, 10, 10, 5, 6 );

	}
}

bool GameTurnPlayerStage::IsTransition()
{
	return false;
}

void GameTurnPlayerStage::GenerateBackground()
{
	int backgroundindex = rand() % 3;

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

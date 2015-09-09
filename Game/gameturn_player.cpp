
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
	}
}

void GameTurnPlayerStage::Update()
{
}

void GameTurnPlayerStage::Render()
{
	al_draw_bitmap( background, 0, 0, 0 );
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

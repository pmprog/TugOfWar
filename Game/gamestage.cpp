
#include "gamestage.h"

GameStage::GameStage(GameInfo* Game)
{
	currentgame = Game;
	background = nullptr;
	GenerateBackground();
	// Set to first players
	currentgame->NextTurn();
}

void GameStage::Begin()
{
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );
}

void GameStage::Pause()
{
}

void GameStage::Resume()
{
}

void GameStage::Finish()
{
	AUDIO->StopMusic();
	al_destroy_bitmap( background );
}

void GameStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
			return;
		}
	}

	if( e->Type == EVENT_NETWORK_PACKET_RECEIVED )
	{
		if( currentgame->AmHost )
		{
			// Process and distribute
		} else {
			// Drive from here
		}
	}
}

void GameStage::Update()
{

	if( currentgame->AmHost )
	{
		// Drive from here

		if( currentgame->BlueTeam[currentgame->BlueCurrent]->TurnData.size()  )

	} else {
		// Check last packet, if not heard anything for a while, ping and check
	}
}

void GameStage::Render()
{
	al_draw_bitmap( background, 0, 0, 0 );

	// Draw Blue Team's Health
	al_draw_filled_rectangle( 0, 450, 400, 480, al_map_rgb( 30, 167, 225 ) );
	// Draw Red Team's Health
	al_draw_filled_rectangle( 400, 450, 800, 480, al_map_rgb( 232, 106, 23 ) );

}

bool GameStage::IsTransition()
{
	return false;
}

void GameStage::GenerateBackground()
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

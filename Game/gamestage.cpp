
#include "gamestage.h"
#include "gameturn_player.h"
#include "gameturn_ai.h"

GameStage::GameStage(GameInfo* Game)
{
	currentgame = Game;
	background = nullptr;
	performbattle = false;
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

	if( performbattle )
	{

		if( battlecountdown > 0 )
		{
			battlecountdown--;
		} else {
			performbattle = false;
			currentgame->NextTurn();
		}

	} else if( currentgame->AmHost ) {
		// Drive from here
		PlayerInfo* blue = currentgame->BlueTeam[currentgame->BlueCurrent];
		PlayerInfo* red = currentgame->RedTeam[currentgame->RedCurrent];

		if( blue->Local && blue->TurnData.back()->TurnData.size() == 0 )
		{
			if( !blue->AI )
			{
				FRAMEWORK->ProgramStages->Push( new GameTurnPlayerStage( this, blue ) );
			} else {
				FRAMEWORK->ProgramStages->Push( new GameTurnAIStage( this, blue ) );
			}
			return;
		}

		if( red->Local && red->TurnData.back()->TurnData.size() == 0 )
		{
			if( !red->AI )
			{
				FRAMEWORK->ProgramStages->Push( new GameTurnPlayerStage( this, red ) );
			} else {
				FRAMEWORK->ProgramStages->Push( new GameTurnAIStage( this, red ) );
			}
			return;
		}

		if( blue->TurnData.back()->TurnData.size() == 0 )
		{
			// TODO: Push Network Wait
		}

		if( red->TurnData.back()->TurnData.size() == 0 )
		{
			// TODO: Push Network Wait
		}

		performbattle = true;
		battlecountdown = 300;

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

  background = al_create_bitmap( 1024, 512 );
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

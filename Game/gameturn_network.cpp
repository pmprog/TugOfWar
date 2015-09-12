
#include "gameturn_network.h"

GameTurnNetworkStage::GameTurnNetworkStage( GameStage* Owner, PlayerInfo* Player )
{
	currentgame = Owner;
	currentplayer = Player;
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
}

void GameTurnNetworkStage::Begin()
{
}

void GameTurnNetworkStage::Pause()
{
}

void GameTurnNetworkStage::Resume()
{
}

void GameTurnNetworkStage::Finish()
{
}

void GameTurnNetworkStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
			return;
		}
	}

	// Let the game handle inputs
	if( e->Type == EVENT_NETWORK_PACKET_RECEIVED )
  {
    FRAMEWORK->ProgramStages->Previous()->EventOccurred( e );
  }
}

void GameTurnNetworkStage::Update()
{
}

void GameTurnNetworkStage::Render()
{
	currentgame->Render();
	al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );

	al_draw_filled_rectangle( 0, 150, DISPLAY->GetWidth(), 330, ( currentplayer->BlueTeam ? al_map_rgb( 30, 167, 225 ) : al_map_rgb( 232, 106, 23 ) ) );
	optionfont->DrawString( 404, 284 - (optionfont->GetFontHeight() / 2), "Waiting for " + currentplayer->Name + "...", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( 400, 280 - (optionfont->GetFontHeight() / 2), "Waiting for " + currentplayer->Name + "...", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
}

bool GameTurnNetworkStage::IsTransition()
{
	return false;
}

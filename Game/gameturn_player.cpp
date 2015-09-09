
#include "gamelobby_kick.h"

GameLobbyKickStage::GameLobbyKickStage( GameLobbyStage* Owner )
{
	lobby = Owner;
}

void GameLobbyKickStage::Begin()
{
}

void GameLobbyKickStage::Pause()
{
}

void GameLobbyKickStage::Resume()
{
}

void GameLobbyKickStage::Finish()
{
}

void GameLobbyKickStage::EventOccurred(Event *e)
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

void GameLobbyKickStage::Update()
{
}

void GameLobbyKickStage::Render()
{
	lobby->Render();
	al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );
}

bool GameLobbyKickStage::IsTransition()
{
	return false;
}

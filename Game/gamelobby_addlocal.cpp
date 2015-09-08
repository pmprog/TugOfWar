
#include "gamelobby_addlocal.h"

GameLobbyAddLocalStage::GameLobbyAddLocalStage( GameLobbyStage* Owner )
{
	lobby = Owner;
}

void GameLobbyAddLocalStage::Begin()
{
}

void GameLobbyAddLocalStage::Pause()
{
}

void GameLobbyAddLocalStage::Resume()
{
}

void GameLobbyAddLocalStage::Finish()
{
}

void GameLobbyAddLocalStage::EventOccurred(Event *e)
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

void GameLobbyAddLocalStage::Update()
{
}

void GameLobbyAddLocalStage::Render()
{
	lobby->Render();
	al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );
}

bool GameLobbyAddLocalStage::IsTransition()
{
	return false;
}

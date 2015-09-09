
#include "gamelobby_addai.h"

GameLobbyAddAIStage::GameLobbyAddAIStage( GameLobbyStage* Owner )
{
	lobby = Owner;
}

void GameLobbyAddAIStage::Begin()
{
}

void GameLobbyAddAIStage::Pause()
{
}

void GameLobbyAddAIStage::Resume()
{
}

void GameLobbyAddAIStage::Finish()
{
}

void GameLobbyAddAIStage::EventOccurred(Event *e)
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

void GameLobbyAddAIStage::Update()
{
}

void GameLobbyAddAIStage::Render()
{
	lobby->Render();
	al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );
}

bool GameLobbyAddAIStage::IsTransition()
{
	return false;
}

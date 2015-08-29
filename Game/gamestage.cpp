
#include "gamestage.h"

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
}

void GameStage::Update()
{
}

void GameStage::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
}

bool GameStage::IsTransition()
{
	return false;
}

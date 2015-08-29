
#include "localsetupstage.h"
#include "menu.h"

void LocalSetupStage::Begin()
{
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );
}

void LocalSetupStage::Pause()
{
}

void LocalSetupStage::Resume()
{
}

void LocalSetupStage::Finish()
{
	AUDIO->StopMusic();
}

void LocalSetupStage::EventOccurred(Event *e)
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

void LocalSetupStage::Update()
{
}

void LocalSetupStage::Render()
{
	al_clear_to_color( al_map_rgb( 192, 180, 144 ) );
}

bool LocalSetupStage::IsTransition()
{
	return false;
}


#include "debugstage.h"

void DebugStage::Begin()
{
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );
}

void DebugStage::Pause()
{
}

void DebugStage::Resume()
{
}

void DebugStage::Finish()
{
	AUDIO->StopMusic();
}

void DebugStage::EventOccurred(Event *e)
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

void DebugStage::Update()
{
}

void DebugStage::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
}

bool DebugStage::IsTransition()
{
	return false;
}

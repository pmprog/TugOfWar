
#include "localsetupstage.h"
#include "menu.h"

void LocalSetupStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
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
	al_clear_to_color( al_map_rgb( 128, 96, 48 ) );

	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 2, 12, "Lobby", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2), 10, "Lobby", FontHAlign::CENTRE, al_map_rgb( 255, 255, 0 ) );

	al_draw_filled_rectangle( 10, 80, 390, 350, al_map_rgb( 0, 0, 64 ) );
	al_draw_filled_rectangle( 10, 80, 390, 80 + optionfont->GetFontHeight() + 2, al_map_rgb( 64, 64, 192 ) );

	al_draw_filled_rectangle( 410, 80, 790, 350, al_map_rgb( 64, 0, 0 ) );
	al_draw_filled_rectangle( 410, 80, 790, 80 + optionfont->GetFontHeight() + 2, al_map_rgb( 192, 64, 64 ) );

}

bool LocalSetupStage::IsTransition()
{
	return false;
}

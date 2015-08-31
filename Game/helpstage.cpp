
#include "helpstage.h"

void HelpStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );
}

void HelpStage::Pause()
{
}

void HelpStage::Resume()
{
}

void HelpStage::Finish()
{
	AUDIO->StopMusic();
}

void HelpStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			// delete FRAMEWORK->ProgramStages->Pop();
			FRAMEWORK->ProgramStages->Push( new TransitionStrips( FRAMEWORK->GetFramesPerSecond() / 2, 6 )  );
			return;
		}
	}
}

void HelpStage::Update()
{
}

void HelpStage::Render()
{
	al_clear_to_color( al_map_rgb( 192, 180, 144 ) );

	// Page 0
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 2, 12, "Battle Matrix", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2), 10, "Battle Matrix", FontHAlign::CENTRE, al_map_rgb( 255, 255, 0 ) );
	GameResources::DrawTank( 0, 290, 100, Angle(0) );
	GameResources::DrawTank( 0, 150, 210, Angle(90) );
	GameResources::DrawTank( 1, 440, 100, Angle(0) );
	GameResources::DrawTank( 1, 150, 310, Angle(90) );
	GameResources::DrawTank( 2, 590, 100, Angle(0) );
	GameResources::DrawTank( 2, 150, 410, Angle(90) );
	/*
	ALLEGRO_BITMAP* t = BitmapCache::LoadBitmap("resources/tankBlue.png");
	al_draw_bitmap( t, 250, 80, 0 );
	al_draw_bitmap( t, 100, 200, 0 );
	BitmapCache::UnloadBitmap("resources/tankBlue.png");
	t = BitmapCache::LoadBitmap("resources/tankGreen.png");
	al_draw_bitmap( t, 400, 80, 0 );
	al_draw_bitmap( t, 100, 300, 0 );
	BitmapCache::UnloadBitmap("resources/tankGreen.png");
	t = BitmapCache::LoadBitmap("resources/tankRed.png");
	al_draw_bitmap( t, 550, 80, 0 );
	al_draw_bitmap( t, 100, 400, 0 );
	BitmapCache::UnloadBitmap("resources/tankRed.png");
	*/

	al_draw_line( 100, 160, 650, 160, al_map_rgb( 255, 255, 255 ), 4 );
	al_draw_line( 240, 60, 240, 460, al_map_rgb( 255, 255, 255 ), 4 );

}

bool HelpStage::IsTransition()
{
	return false;
}

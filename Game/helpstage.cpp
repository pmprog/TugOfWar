
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


	GameResources::DrawTank( 0, 440, 210, Angle(0) );
	GameResources::DrawTank( 2, 590, 210, Angle(0) );
	GameResources::DrawTank( 0, 290, 310, Angle(0) );
	GameResources::DrawTank( 1, 590, 310, Angle(0) );
	GameResources::DrawTank( 2, 290, 410, Angle(0) );
	GameResources::DrawTank( 1, 440, 410, Angle(0) );

	ALLEGRO_BITMAP* t = BitmapCache::LoadBitmap( "resources/smokeGrey4.png" );
	al_draw_bitmap( t, 290 - (al_get_bitmap_width( t ) / 2), 210 - (al_get_bitmap_height( t ) / 2), 0 );
	al_draw_bitmap( t, 440 - (al_get_bitmap_width( t ) / 2), 310 - (al_get_bitmap_height( t ) / 2), 0 );
	al_draw_bitmap( t, 590 - (al_get_bitmap_width( t ) / 2), 410 - (al_get_bitmap_height( t ) / 2), 0 );

	al_draw_line( 100, 160, 650, 160, al_map_rgb( 255, 255, 255 ), 4 );
	al_draw_line( 240, 60, 240, 460, al_map_rgb( 255, 255, 255 ), 4 );

}

bool HelpStage::IsTransition()
{
	return false;
}


#include "localsetupstage.h"
#include "menu.h"

void LocalSetupStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );

	bluepanel = new SpriteSheet( "resources/metalPanel_blueCorner.png", 30, 30 );
	redpanel = new SpriteSheet( "resources/metalPanel_redCorner.png", 30, 30 );

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

	DrawPanel( bluepanel, 5, 80, 13, 9, 8 );
	optionfont->DrawString( 15, 85, "Blue Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

	DrawPanel( redpanel, 405, 80, 13, 9, 8 );
	optionfont->DrawString( 415, 85, "Red Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

}

bool LocalSetupStage::IsTransition()
{
	return false;
}

void LocalSetupStage::DrawPanel(SpriteSheet* PanelGraphics, int X, int Y, int TilesWide, int TilesHigh, int HeaderTilesWide)
{
	al_hold_bitmap_drawing( true );
	for( int y = 0; y < TilesHigh; y++ )
	{
		for( int x = 0; x < TilesWide; x++ )
		{
			if( y <= 1 )
			{

				if( x == 0 )
				{
					PanelGraphics->DrawSprite( y * 5, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else if( x == TilesWide - 1) {
					PanelGraphics->DrawSprite( (y * 5) + 4, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else if( x < HeaderTilesWide ) {
					PanelGraphics->DrawSprite( (y * 5) + 1, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else if( x == HeaderTilesWide ) {
					PanelGraphics->DrawSprite( (y * 5) + 2, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else {
					PanelGraphics->DrawSprite( (y * 5) + 3, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				}


			} else if( y == TilesHigh - 1 ) {
				if( x == 0 )
				{
					PanelGraphics->DrawSprite( 20, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else if( x == TilesWide - 1) {
					PanelGraphics->DrawSprite( 24, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else {
					PanelGraphics->DrawSprite( 21, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				}
			} else {
				if( x == 0 )
				{
					PanelGraphics->DrawSprite( 10, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else if( x == TilesWide - 1) {
					PanelGraphics->DrawSprite( 9, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				} else {
					PanelGraphics->DrawSprite( 8, X + (x * PanelGraphics->GetFrame(0)->Width), Y + (y * PanelGraphics->GetFrame(0)->Height) );
				}
			}
		}
	}
	al_hold_bitmap_drawing( false );
}

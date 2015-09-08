
#include "gamelobbystage.h"
#include "menu.h"

void GameLobbyStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );

}

void GameLobbyStage::Pause()
{
}

void GameLobbyStage::Resume()
{
}

void GameLobbyStage::Finish()
{
	AUDIO->StopMusic();
}

void GameLobbyStage::EventOccurred(Event *e)
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

void GameLobbyStage::Update()
{
}

void GameLobbyStage::Render()
{
	al_clear_to_color( al_map_rgb( 128, 96, 48 ) );

	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 2, 12, "Lobby", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2), 10, "Lobby", FontHAlign::CENTRE, al_map_rgb( 255, 255, 0 ) );

	GameResources::DrawPanel( GameResources::BluePanel, 5, 80, 13, 8, 8 );
	optionfont->DrawString( 15, 85, "Blue Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

	GameResources::DrawButton( GameResources::WhiteButtonUp, 15, 140, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 15, 192, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 15, 244, 23, 3 );

	GameResources::DrawPanel( GameResources::RedPanel, 405, 80, 13, 8, 8 );
	optionfont->DrawString( 415, 85, "Red Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

	GameResources::DrawButton( GameResources::WhiteButtonUp, 415, 140, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 415, 192, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 415, 244, 23, 3 );


}

bool GameLobbyStage::IsTransition()
{
	return false;
}

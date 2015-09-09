
#include "gamelobby_addlocal.h"

GameLobbyAddLocalStage::GameLobbyAddLocalStage( PlayerInfo* ConfigurePlayer )
{
	player = ConfigurePlayer;
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );

	editform = new Form();
	editform->Size.X = DISPLAY->GetWidth();
	editform->Size.Y = (optionfont->GetFontHeight() + 8) * 2;
	editform->Location.X = 0;
	editform->Location.Y = 240 - (editform->Size.Y / 2);
	editform->BackgroundColour = al_map_rgb( 64, 64, 64 );
	Label* l = new Label( editform, "Enter Player's Name", optionfont );
	l->Size.X = editform->Size.X;
	l->Size.Y = optionfont->GetFontHeight() + 2;
	l->Location.X = 0;
	l->Location.Y = (editform->Size.Y / 2) - l->Size.Y - 2;
	l->TextHAlign = HorizontalAlignment::Centre;
	l->TextVAlign = VerticalAlignment::Centre;
	l->ForegroundColour = al_map_rgb( 255, 255, 255 );
	l->BackgroundColour.a = 0;

	editname = new TextEdit( editform, player->Name, optionfont );
	editname->Size.X = editform->Size.X - 8;
	editname->Size.Y = optionfont->GetFontHeight() + 2;
	editname->Location.X = 4;
	editname->Location.Y = (editform->Size.Y / 2) + 2;
	editname->TextHAlign = HorizontalAlignment::Centre;
	editname->TextVAlign = VerticalAlignment::Centre;
	editname->BackgroundColour = al_map_rgb( 255, 255, 255 );
	editname->ForegroundColour = al_map_rgb( 0, 0, 0 );
}

void GameLobbyAddLocalStage::Begin()
{
	FRAMEWORK->ProcessEvents();
	editname->Focus();
	editname->BeginEdit();
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
	editform->EventOccured( e );
	if( e->Handled )
	{
		return;
	}

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
	editform->Update();
	if( !editname->IsEditing() )
	{
		player->Name = editname->GetText();
		delete FRAMEWORK->ProgramStages->Pop();
	}
}

void GameLobbyAddLocalStage::Render()
{
	FRAMEWORK->ProgramStages->Previous()->Render();
	al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );
	editform->Render();
	// al_draw_filled_rectangle( 0, 240 - optionfont->GetFontHeight() - 4, DISPLAY->GetWidth(), 240 + optionfont->GetFontHeight() + 4, al_map_rgb( 192, 192, 192 ) );
	// optionfont->DrawString( 400, 240 - optionfont->GetFontHeight() - 4, "Enter Player's Name", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	// optionfont->DrawString( 400, 240 - optionfont->GetFontHeight() - 4, player->Name, FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
}

bool GameLobbyAddLocalStage::IsTransition()
{
	return false;
}

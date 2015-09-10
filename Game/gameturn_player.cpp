
#include "gameturn_player.h"
#include "input.h"

GameTurnPlayerStage::GameTurnPlayerStage( GameStage* Owner, PlayerInfo* Player )
{
	currentgame = Owner;
	currentplayer = Player;
	GenerateBackground();
}

void GameTurnPlayerStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	playeracknowledgedturn = false;
	selectinggrid = false;
	gridx = 0;
	gridy = 0;
	selectionmenu = 0;
}

void GameTurnPlayerStage::Pause()
{
}

void GameTurnPlayerStage::Resume()
{
}

void GameTurnPlayerStage::Finish()
{
}

void GameTurnPlayerStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			currentplayer->TurnData.back()->TurnData.push_back( new TurnInfo( TurnInfo::Actions::NONE ) );
			delete FRAMEWORK->ProgramStages->Pop();
			return;
		}
	}

	InputItems::ItemSet inputkey = Input::GetItemFromEvent( e );
	if( !playeracknowledgedturn )
	{
		playeracknowledgedturn = ( inputkey == InputItems::START );
	} else {
		switch( inputkey )
		{
			case InputItems::START:
				currentplayer->TurnData.back()->TurnData.push_back( new TurnInfo( TurnInfo::Actions::NONE ) );
				delete FRAMEWORK->ProgramStages->Pop();
				break;

			case InputItems::SELECT:
				if( selectinggrid )
				{
					selectinggrid = false;
				}
				break;

			case InputItems::UP:
				if( selectinggrid )
				{
				} else {
					selectionmenu = ( selectionmenu > 0 ? selectionmenu - 1 : 0 );
				}
				break;
			case InputItems::DOWN:
				if( selectinggrid )
				{
				} else {
					selectionmenu = ( selectionmenu < 5 ? selectionmenu + 1 : 5 );
				}
				break;
			case InputItems::LEFT:
				if( selectinggrid )
				{
				}
				break;
			case InputItems::RIGHT:
				if( selectinggrid )
				{
				}
				break;
			case InputItems::X:
			case InputItems::Y:
			case InputItems::A:
			case InputItems::B:
				if( selectinggrid )
				{
					// Perform action
					selectinggrid = false;
				} else {
					// Handle menu
				}
				break;

		}
	}

}

void GameTurnPlayerStage::Update()
{
}

void GameTurnPlayerStage::Render()
{
	if( !playeracknowledgedturn )
	{
		currentgame->Render();
		al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );

		al_draw_filled_rectangle( 0, 150, DISPLAY->GetWidth(), 330, ( currentplayer->BlueTeam ? al_map_rgb( 30, 167, 225 ) : al_map_rgb( 232, 106, 23 ) ) );
		optionfont->DrawString( 404, 279 - optionfont->GetFontHeight(), currentplayer->Name, FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
		optionfont->DrawString( 400, 275 - optionfont->GetFontHeight(), currentplayer->Name, FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
		optionfont->DrawString( 404, 289, "Press any key", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
		optionfont->DrawString( 400, 285, "Press any key", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );

	} else {

		al_draw_bitmap( background, 0, 0, 0 );

		int drawx = ( currentplayer->BlueTeam ? 15 : 90 );
		for( int x = 0; x < 5; x++ )
		{
			al_draw_line( drawx + (x * 90), 15, drawx + (x * 90), 465, al_map_rgb( 255, 255, 255 ), 3 );
		}

		for( int y = 0; y < 6; y++ )
		{
			al_draw_line( drawx, 15 + (y * 90), drawx + 360, 15 + (y * 90), al_map_rgb( 255, 255, 255 ), 3 );
			if( currentplayer->BlueTeam )
			{
				al_draw_bitmap( BitmapCache::LoadBitmap( "resources/arrowRight.png" ), 390, 35 + (y * 90), 0 );
			} else {
				al_draw_bitmap( BitmapCache::LoadBitmap( "resources/arrowLeft.png" ), 15, 35 + (y * 90), 0 );
			}
		}

		GameResources::DrawPanel( (currentplayer->BlueTeam ? GameResources::BluePanel : GameResources::RedPanel ), 480, 10, 10, 5, 6 );

		int btny = 180;
		RenderMenuButton( 0, btny, "Buy Red Tank (Defeats Green)" ); btny += 49;
		RenderMenuButton( 1, btny, "Buy Green Tank (Defeats Blue)" ); btny += 49;
		RenderMenuButton( 2, btny, "Buy Blue Tank (Defeats Red)" ); btny += 49;
		RenderMenuButton( 3, btny, "Buy Intrest (+5%)" ); btny += 49;
		RenderMenuButton( 4, btny, "Sell Tank" ); btny += 49;
		RenderMenuButton( 5, btny, "Finish" ); btny += 49;

	}
}

bool GameTurnPlayerStage::IsTransition()
{
	return false;
}

void GameTurnPlayerStage::GenerateBackground()
{
	int backgroundindex = rand() % 3;

  background = al_create_bitmap( 1024, 512 );
	DISPLAY->SetTarget( background );

	int iw = al_get_bitmap_width( GameResources::BackgroundTiles.at(backgroundindex) );
	int ih = al_get_bitmap_height( GameResources::BackgroundTiles.at(backgroundindex) );
	int bx = 0;
	int by = 0;

	al_hold_bitmap_drawing( true );
	while( by < 512 )
	{
		while( bx < 1024 )
		{
			al_draw_bitmap( GameResources::BackgroundTiles.at(backgroundindex), bx, by, 0 );
			bx += iw;
		}
		by += ih;
		bx = 0;
	}
	al_hold_bitmap_drawing( false );

	DISPLAY->ClearTarget();
}

void GameTurnPlayerStage::RenderMenuButton( int Index, int Y, std::string Label )
{
	ButtonColours::Colours btnc = (currentplayer->BlueTeam ? ButtonColours::BLUE : ButtonColours::RED );
	btnc = ( selectionmenu == Index ? ButtonColours::YELLOW : btnc );

	GameResources::DrawButton( btnc, (selectionmenu == Index), 483, Y, 18, 3 );
	optionfont->DrawString( 629, Y + 10 - (selectionmenu == Index ? 4 : 0 ), Label, FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( 627, Y + 8 - (selectionmenu == Index ? 4 : 0 ), Label, FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
}

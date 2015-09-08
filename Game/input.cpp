
#include "input.h"

ALLEGRO_BITMAP* Input::GetIcon( InputItems::ItemSet Input )
{
	if( FRAMEWORK->HasController() )
	{
		switch( Input )
		{
			case InputItems::UP:
				return BitmapCache::LoadBitmap( "resources/arrowUp.png" );
				break;
			case InputItems::DOWN:
				return BitmapCache::LoadBitmap( "resources/arrowDown.png" );
				break;
			case InputItems::LEFT:
				return BitmapCache::LoadBitmap( "resources/arrowLeft.png" );
				break;
			case InputItems::RIGHT:
				return BitmapCache::LoadBitmap( "resources/arrowRight.png" );
				break;
			case InputItems::START:
				return BitmapCache::LoadBitmap( "resources/buttonStart.png" );
				break;
			case InputItems::SELECT:
				return BitmapCache::LoadBitmap( "resources/buttonSelect.png" );
				break;
			case InputItems::A:
				return BitmapCache::LoadBitmap( "resources/buttonA.png" );
				break;
			case InputItems::B:
				return BitmapCache::LoadBitmap( "resources/buttonB.png" );
				break;
			case InputItems::X:
				return BitmapCache::LoadBitmap( "resources/buttonX.png" );
				break;
			case InputItems::Y:
				return BitmapCache::LoadBitmap( "resources/buttonY.png" );
				break;
			case InputItems::L:
				return BitmapCache::LoadBitmap( "resources/buttonL.png" );
				break;
			case InputItems::R:
				return BitmapCache::LoadBitmap( "resources/buttonR.png" );
				break;
		}

	} else {

		// TODO: Fix up to show keyboard related keys
		switch( Input )
		{
			case InputItems::UP:
				return BitmapCache::LoadBitmap( "resources/arrowUp.png" );
				break;
			case InputItems::DOWN:
				return BitmapCache::LoadBitmap( "resources/arrowDown.png" );
				break;
			case InputItems::LEFT:
				return BitmapCache::LoadBitmap( "resources/arrowLeft.png" );
				break;
			case InputItems::RIGHT:
				return BitmapCache::LoadBitmap( "resources/arrowRight.png" );
				break;
			case InputItems::START:
				return BitmapCache::LoadBitmap( "resources/buttonStart.png" );
				break;
			case InputItems::SELECT:
				return BitmapCache::LoadBitmap( "resources/buttonSelect.png" );
				break;
			case InputItems::A:
				return BitmapCache::LoadBitmap( "resources/buttonA.png" );
				break;
			case InputItems::B:
				return BitmapCache::LoadBitmap( "resources/buttonB.png" );
				break;
			case InputItems::X:
				return BitmapCache::LoadBitmap( "resources/buttonX.png" );
				break;
			case InputItems::Y:
				return BitmapCache::LoadBitmap( "resources/buttonY.png" );
				break;
			case InputItems::L:
				return BitmapCache::LoadBitmap( "resources/buttonL.png" );
				break;
			case InputItems::R:
				return BitmapCache::LoadBitmap( "resources/buttonR.png" );
				break;
		}
	}

	// Placeholder
	return BitmapCache::LoadBitmap( "resources/question.png" );
}

InputItems::ItemSet Input::GetItemFromEvent( Event* e )
{
	InputItems::ItemSet result = InputItems::NONE;
#ifdef PANDORA
	if( e->Type == EVENT_KEY_DOWN )
	{
		switch( e->Data.Keyboard.KeyCode )
		{
			case ALLEGRO_KEY_UP:
				result = InputItems::UP;
				break;
			case ALLEGRO_KEY_DOWN:
				result = InputItems::DOWN;
				break;
			case ALLEGRO_KEY_LEFT:
				result = InputItems::LEFT;
				break;
			case ALLEGRO_KEY_RIGHT:
				result = InputItems::RIGHT;
				break;
			case ALLEGRO_KEY_ALT:
				result = InputItems::START;
				break;
			case ALLEGRO_KEY_LCTRL:
				result = InputItems::SELECT;
				break;
			case ALLEGRO_KEY_HOME:
				result = InputItems::A;
				break;
			case ALLEGRO_KEY_PGUP:
				result = InputItems::Y;
				break;
			case ALLEGRO_KEY_PGDN:
				result = InputItems::X;
				break;
			case ALLEGRO_KEY_END:
				result = InputItems::B;
				break;
			case ALLEGRO_KEY_RSHIFT:
				result = InputItems::L;
				break;
			case ALLEGRO_KEY_RCTRL:
				result = InputItems::R;
				break;
		}
	}
#else

	if( e->Type == EVENT_KEY_DOWN )
	{
		switch( e->Data.Keyboard.KeyCode )
		{
			case ALLEGRO_KEY_UP:
				result = InputItems::UP;
				break;
			case ALLEGRO_KEY_DOWN:
				result = InputItems::DOWN;
				break;
			case ALLEGRO_KEY_LEFT:
				result = InputItems::LEFT;
				break;
			case ALLEGRO_KEY_RIGHT:
				result = InputItems::RIGHT;
				break;
			case ALLEGRO_KEY_ENTER:
				result = InputItems::START;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				result = InputItems::SELECT;
				break;
			case ALLEGRO_KEY_A:
				result = InputItems::A;
				break;
			case ALLEGRO_KEY_S:
				result = InputItems::Y;
				break;
			case ALLEGRO_KEY_Z:
				result = InputItems::X;
				break;
			case ALLEGRO_KEY_X:
				result = InputItems::B;
				break;
			case ALLEGRO_KEY_D:
				result = InputItems::L;
				break;
			case ALLEGRO_KEY_C:
				result = InputItems::R;
				break;
		}
	}
#endif
	return result;
}

void Input::MapEventToInput( InputItems::ItemSet Input, Event* e )
{
}


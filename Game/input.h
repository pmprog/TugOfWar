
#pragma once

#include "includes.h"

class InputItems
{
	public:
		enum ItemSet
		{
			NONE,
			UP,
			DOWN,
			LEFT,
			RIGHT,
			A,
			B,
			X,
			Y,
			START,
			SELECT,
			L,
			R
		};
};

class Input
{

	public:
		static ALLEGRO_BITMAP* GetIcon( InputItems::ItemSet Input );
		static InputItems::ItemSet GetItemFromEvent( Event* e );
		static void MapEventToInput( InputItems::ItemSet Input, Event* e );

};
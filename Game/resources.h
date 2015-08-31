
#pragma once

#include "includes.h"

class GameResources
{

  public:
		static std::vector<ALLEGRO_BITMAP*> BackgroundTiles;

		static void DrawTank(int Colour, int X, int Y, Angle Rotation);
};

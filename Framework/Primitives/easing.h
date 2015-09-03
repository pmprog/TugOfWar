
#pragma once

#include "../maths.h"

class Easing
{

	public:
		static float EaseOutBack( float Time, float Begin, float Change, float Duration, float Swing );
		static float EaseOutBounce( float Time, float Begin, float Change, float Duration );
		static float EaseOutElastic( float Time, float Begin, float Change, float Duration );

};
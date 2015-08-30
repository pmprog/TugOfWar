
#pragma once

#include "includes.h"
#include "resources.h"


class Menu : public Stage
{
	private:
		int backgroundindex;
		int menutime;
		int rendertime;
		TTFFont* titlefont;
		TTFFont* optionfont;
		int sliderindex;
		int slidertarget;

		void GenerateBackground();

  public:
		ALLEGRO_BITMAP* background;

    // Stage control
    virtual void Begin();
    virtual void Pause();
    virtual void Resume();
    virtual void Finish();
    virtual void EventOccurred(Event *e);
    virtual void Update();
    virtual void Render();
		virtual bool IsTransition();
};

#pragma once

#include <Diablo_Const4D.h>
#include <Diablo_Serial_4DLib.h>

namespace smm {
    class DiabloGraph {
    public:
	DiabloGraph(Stream *serial,
		    int resetPin,
		    unsigned int width=800,
		    unsigned int height=480)
	    : mDisplay(serial), mResetPin(resetPin),
	      mWidth(width), mHeight(height), mPosition(0),
	      mPrevious(-1)
	{}

	void setup()
	{
	    pinMode(mResetPin, OUTPUT);
	    digitalWrite(mResetPin, 0);
	    delay(100);
	    digitalWrite(mResetPin, 1);
	    delay(5000);

	    mDisplay.gfx_ScreenMode(LANDSCAPE);
	    mDisplay.gfx_Cls();

	    mDisplay.putstr("Hello, world!");
	}

	void push(double v)
	{
	    int value = (int) (v * mHeight);

	    if (mPrevious < 0)
		mPrevious = value;
	    else {
		mDisplay.gfx_Line(mPosition, mPrevious,
				  ++mPosition, value,
				  GREEN);
		mPrevious = value;
		if (mPosition >= mWidth) {
		    mPosition = 0;
		    mDisplay.gfx_Cls();
		}
	    }
	}

    private:
	Diablo_Serial_4DLib mDisplay;
	int mResetPin;
	unsigned int mWidth, mHeight, mPosition;
	int mPrevious;
    };
}

/*
	Author: bitluni 2019
	License: 
	Creative Commons Attribution ShareAlike 4.0
	https://creativecommons.org/licenses/by-sa/4.0/
	
	For further details check out: 
		https://youtube.com/bitlunislab
		https://github.com/bitluni
		http://bitluni.net
*/
#pragma once

#include "../I2S/I2S.h"
#include "Mode.h"
#include "PinConfig.h"

class VGA : public I2S
{
  public:
	VGA(const int i2sIndex = 0);
	void setLineBufferCount(int lineBufferCount);
	bool init(const Mode &mode, const int *pinMap, const int bitCount, const int clockPin = -1);
	virtual bool init(const Mode &mode, const PinConfig &pinConfig) = 0;

	static const Mode MODE720x400;
	static const Mode MODE640x480;
	static const Mode MODE640x400;


	Mode mode;

	virtual int bytesPerSample() const = 0;

  protected:
	
	virtual void initSyncBits() = 0;
	virtual long syncBits(bool h, bool v) = 0;
 
	int lineBufferCount;
	int vsyncPin;
	int hsyncPin;
	int currentLine;
	long vsyncBit;
	long hsyncBit;
	long vsyncBitI;
	long hsyncBitI;

	int totalLines;
	volatile bool vSyncPassed;

	void *vSyncInactiveBuffer;
	void *vSyncActiveBuffer;
	void *inactiveBuffer;
	void *blankActiveBuffer;

	void allocateLineBuffers(const int lines);
	virtual void allocateLineBuffers();
	virtual void allocateLineBuffers(void **frameBuffer);
	virtual void propagateResolution(const int xres, const int yres) = 0;

  protected:
	virtual void interrupt();
	virtual void vSync();
	virtual void interruptPixelLine(int y, unsigned long *pixels, unsigned long syncBits);
};

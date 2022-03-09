#ifndef __BATHYLIB_H_
#define __BATHYLIB_H_

#include "IBathyLib.h"
#include <string>

class BathyLib : public IBathyLib
{
public:
	void jsonInit(const char* jsonContent) override;

	double nextWaveHeight() override;

	double nextDepth() override;

	double nextLat() override;

	double nextLon() override;

private:
	void replaceHomeVar(std::string& s)
	{
		std::string homeVar("$ENV{HOME}");
		std::string homeValue(getenv("HOME"));
		size_t index = s.find(homeVar, 0);
		if (index != std::string::npos)
			s = s.replace(index, homeVar.size(), homeValue);
	}

	float* dataWave = NULL;
	unsigned int countWave = 0;
	unsigned int countWaveMax = 1;
	float waveHeight = 0;
	std::string waveFilename = "";
	std::string waveVarName = "";

	float* dataBottom = NULL;
	unsigned int countBottom = 0;
	unsigned int countBottomMax = 1;
	float bottom = 0;
	std::string bottomMotionFilename = "";
	std::string bottomVarName = "";

	float* dataDepth = NULL;
	unsigned int countDepth = 0;
	unsigned int countDepthMax = 1;
	float depth = 0;
	std::string depthFilename = "";
	std::string depthVarName = "";

	float* dataLon = NULL;
	unsigned int countLon = 0;
	unsigned int countLonMax = 1;
	float lon = 0;
	std::string lonFilename = "";
	std::string lonVarName = "";

	float* dataLat = NULL;
	unsigned int countLat = 0;
	unsigned int countLatMax = 1;
	float lat = 0;
	std::string latFilename = "";
	std::string latVarName = "";
};

#endif

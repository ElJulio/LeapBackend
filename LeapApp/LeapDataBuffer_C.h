#include <vector>
#include <LeapC.h>
#include <mutex>
#include <thread>
#pragma once
class LeapDataBuffer_C
{
public:

	struct Position
	{
		float x;
		float y;
		float z;
	};

	struct FingerTip
	{
		Position pos;
	};

	struct Palm
	{
		Position pos;
	};

	struct HandData
	{
		FingerTip thumb;
		FingerTip index;
		FingerTip middle;
		FingerTip ring;
		FingerTip pinky;
		Palm	  palm;
		uint32_t  id;
	};

	struct LeapData
	{
		std::vector<HandData> handDataCollection;
		uint8_t				  nHands;
		int64_t				  frameID;
	};

	typedef std::vector<LeapData> LeapDataBuffer;

	LeapDataBuffer_C();
	~LeapDataBuffer_C();


	std::vector<LeapData> PollLeapData();

	void SaveData(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID);

private:

	LeapDataBuffer mLeapDataBuffer;
	std::mutex     mMutex;

};


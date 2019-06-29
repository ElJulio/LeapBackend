#pragma once
#include <LeapC.h>
#include <json.hpp>
#include <ctime>
#include <mutex>

class JsonCreator_C
{
public:
	JsonCreator_C();
	~JsonCreator_C();

	/**
	*@brief: Writes the hands struct to a json file
	*/
	void WriteJson(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID);

	/**
	*@brief: Set NextStep sets a time stamp in the next processed Leap frame
	*/
	void SetNextStep(std::time_t timeStamp);

	/**
	*@brief: Set NextStep sets a time stamp in the next processed Leap frame
	*/
	void IsLastFrame();

	bool GetIsLastFrame();

private:

	std::time_t GetNextStep();

	/*Member vars*/
	std::mutex   mMutex;
	bool	     mNextStep = false;
	std::time_t  mNextStepTime;
	bool		 mIsLastFrame = false;
	std::string  mFileName;
};


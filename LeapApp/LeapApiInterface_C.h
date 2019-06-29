#include <vector>
#include "LeapController_C.h"
#include "LeapDataBuffer_C.h"

#pragma once
class LeapApiInterface_C
{
public:
	LeapApiInterface_C();
	~LeapApiInterface_C();

	/**
	*@brief Start data collection thread
	*
	*
	*/
	bool StartDataCollectionThread();

	/**
	*@brief Start data collection thread
	*
	*
	*/
	bool StopDataCollectionThread();

	/**
	*@brief Poll data
	*
	*
	*/
	std::vector<LeapDataBuffer_C::LeapData> PollLeapData();

	/**
	*@brief Poll Error State
	*
	*
	*/
	std::vector<int> PollErrorState();

private:

	LeapDataBuffer_C* mLeapDataBuffer;
	LeapController_C* mLeapController;


};


#pragma once
#include "DataProcessor_C.h"

class LeapApiWrapper_C
{
public:
	LeapApiWrapper_C(DataProcessor_C* dataProcessor);
	~LeapApiWrapper_C();

	/**
	*@brief: Starting the main loop to poll the data from the LeapMotion 
	*/
	void StartMainLoop();

	/**
	*@brief: Stopping the main loop
	*/
	void StopMainLoop();
private:

	/**
	*@brief: The loop that polls the data from the LeapMotion 
	*/
	void MainLoop();

	/*Member vars*/
	DataProcessor_C* mDataProcessor;
	bool			 mStopMainLoop;
	bool			 mThreadFinished = false;


};


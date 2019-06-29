#pragma once

#include "Configurator_C.h"
#include "JsonCreator_C.h"
#include "DataProcessor_C.h"
#include "KeyRecognition_C.h"
#include "LeapApiWrapper_C.h"

class LeapController_C
{
public:
	LeapController_C();
	LeapController_C(LeapDataBuffer_C* leapDatabuffer);
	~LeapController_C();

	bool StartDataCollectionThread();

	bool StopDataCollectionThread();

	/**
	*@brief Init the Leap Controller and starting all the threads
	*/
	void Init();

private:

	/**
	*@brief Reading the config file
	*/
	Configurator_C::LeapConf_ST ReadConf();


	/*Member vars*/
	Configurator_C::LeapConf_ST mLeapConf;

	LeapApiWrapper_C* mLeapApiWrapper;
	LeapDataBuffer_C* mLeapDataBuffer;

};


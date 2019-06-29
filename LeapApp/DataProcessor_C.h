#pragma once

#include "JsonCreator_C.h"
#include "LeapDataBuffer_C.h"
#include "Configurator_C.h"
#include <LeapC.h>

class DataProcessor_C
{
public:
	/**
	*@brief Constructor for stand alone mode
	*
	*/
	DataProcessor_C(JsonCreator_C* jsonCreator, Configurator_C::LeapConf_ST* leapConf);

	/**
	*@brief Constructor for stand api mode
	*
	*/
	DataProcessor_C(LeapDataBuffer_C* leapDataBuffer, Configurator_C::LeapConf_ST* leapConf);


	~DataProcessor_C();

	void DataInput(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID);

	void IsLastFrame();

private:

	void DataOutput(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID);

	/*Meber variables*/
	JsonCreator_C*				 mJsonCreator;
	LeapDataBuffer_C*			 mLeapDataBuffer;
	Configurator_C::LeapConf_ST* mLeapConf;
	int64_t						 mLastFrameID;

};


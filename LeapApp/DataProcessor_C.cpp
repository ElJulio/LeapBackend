#include "DataProcessor_C.h"

DataProcessor_C::DataProcessor_C(JsonCreator_C* jsonCreator, Configurator_C::LeapConf_ST *leapConf) :
	mJsonCreator(jsonCreator),
	mLeapConf(leapConf)
{
}

DataProcessor_C::DataProcessor_C(LeapDataBuffer_C* leapDataBuffer, Configurator_C::LeapConf_ST* leapConf) :
	mLeapDataBuffer(leapDataBuffer),
	mLeapConf(leapConf)
{
}

DataProcessor_C::~DataProcessor_C()
{
}

void DataProcessor_C::DataInput(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID)
{
	
	if (mLeapConf->compressionActive)
	{
		//Drop frames with the same id
		if (mLastFrameID == frameID) {
			return;
		}
	}
	mLastFrameID = frameID;
	DataOutput(hands, nHands, frameID);
}

void DataProcessor_C::IsLastFrame()
{
	if(!mLeapConf->apiMode)
		mJsonCreator->IsLastFrame();
}

void DataProcessor_C::DataOutput(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID)
{
	if (mLeapConf->apiMode)
		mLeapDataBuffer->SaveData(hands, nHands, frameID);
	else
		mJsonCreator->WriteJson(hands, nHands, frameID);
}



#include "LeapApiInterface_C.h"



LeapApiInterface_C::LeapApiInterface_C()
{
	mLeapDataBuffer = new LeapDataBuffer_C();
	mLeapController = new LeapController_C(mLeapDataBuffer);
}


LeapApiInterface_C::~LeapApiInterface_C()
{
}

bool LeapApiInterface_C::StartDataCollectionThread()
{
	return mLeapController->StartDataCollectionThread();
}


bool LeapApiInterface_C::StopDataCollectionThread()
{
	return mLeapController->StopDataCollectionThread();
}

std::vector<LeapDataBuffer_C::LeapData> LeapApiInterface_C::PollLeapData()
{
	return mLeapDataBuffer->PollLeapData();
}

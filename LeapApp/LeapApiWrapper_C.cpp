#include "LeapApiWrapper_C.h"

#include <iostream>
#include <thread>
#include <chrono>

extern "C"{
#include "LeapApi.h"
}


LeapApiWrapper_C::LeapApiWrapper_C(DataProcessor_C* dataProcessor):
	mDataProcessor(dataProcessor),
	mStopMainLoop(false),
	mThreadFinished(false)
{

}

LeapApiWrapper_C::~LeapApiWrapper_C()
{
}

void LeapApiWrapper_C::StartMainLoop()
{
	std::thread t(&LeapApiWrapper_C::MainLoop, this);
	t.join();
}

void LeapApiWrapper_C::StopMainLoop()
{
	mStopMainLoop = true;
	//wait for the thread to end
	while (!mThreadFinished)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void LeapApiWrapper_C::MainLoop()
{
	for (;;)
	{
		const uint8_t buffsize = 100;
		LEAP_HAND* hands[buffsize];
		int64_t frameID;
		uint8_t nHands;
		int res = GetLeapData(hands, buffsize, &frameID, &nHands);
		//now write the data to the data Processor
		if (res == 0) 
		{
			if (mStopMainLoop) 
			{
				mDataProcessor->IsLastFrame();
				mDataProcessor->DataInput(hands, nHands, frameID);
				break;
			}
			else
			{
				mDataProcessor->DataInput(hands, nHands, frameID);
			}
		}
		else if (res == 1)
		{
			std::cerr << "To Many Hands that frame will be dropped" << std::endl;
			if (mStopMainLoop)
			{
				break;
			}
		}
		else if (res == 2)
		{
			break; // No LeapMotion detected
		}
	}
	mThreadFinished = true;
}

#include "LeapController_C.h"
#include <stdexcept>
#include <thread>
#include <iostream>


LeapController_C::LeapController_C(): 
	mLeapConf(Configurator_C::LeapConf_ST())
{
	Init();
}

LeapController_C::LeapController_C(LeapDataBuffer_C* leapDatabuffer) :
	mLeapConf(Configurator_C::LeapConf_ST()),
	mLeapDataBuffer(leapDatabuffer)
{
}


LeapController_C::~LeapController_C()
{
}

void LeapController_C::Init()
{
	mLeapConf = ReadConf();
	if (&mLeapConf == nullptr) {
		throw std::runtime_error("Configuration could not be applied!");
	}

	if (!mLeapConf.apiMode)
	{
		//Init Json Creator
		JsonCreator_C* jsonCreator = new JsonCreator_C();

		//Init Data Processor
		DataProcessor_C* dataProcessor = new DataProcessor_C(jsonCreator, &mLeapConf);

		//Start LeapApi Thread
		LeapApiWrapper_C* leapApiWrapper = new LeapApiWrapper_C(dataProcessor);
		std::thread leapApiThread(&LeapApiWrapper_C::StartMainLoop, leapApiWrapper);

		//Start Keyboad Recognizer
		KeyRecognition_C* keyRecognition = new KeyRecognition_C(jsonCreator);
		std::thread keyRecThread(&KeyRecognition_C::StartMainLoop, keyRecognition);

		keyRecThread.join();
		std::cout << "Quitting LeapApiThread" << std::endl;
		leapApiWrapper->StopMainLoop();
		std::cout << "Exited LeapApiThread" << std::endl;

		leapApiThread.join();
		std::cout << "Good Bye" << std::endl;

		delete jsonCreator;
		delete dataProcessor;
		delete leapApiWrapper;
		delete keyRecognition;
	}
	else 
	{
		
		//Init Data Processor
		DataProcessor_C* dataProcessor = new DataProcessor_C(mLeapDataBuffer, &mLeapConf);

		LeapApiWrapper_C* mLeapApiWrapper = new LeapApiWrapper_C(dataProcessor);

		std::thread leapApiThread(&LeapApiWrapper_C::StartMainLoop, mLeapApiWrapper);
		leapApiThread.join();
		
	}
	
}

bool LeapController_C::StartDataCollectionThread()
{
	Init();
	return true;
}

bool LeapController_C::StopDataCollectionThread()
{
	mLeapApiWrapper->StopMainLoop();
	return true;
}


Configurator_C::LeapConf_ST LeapController_C::ReadConf()
{
	Configurator_C configurator;
	Configurator_C::LeapConf_ST leapConf = configurator.GetConf();
	return leapConf;
}


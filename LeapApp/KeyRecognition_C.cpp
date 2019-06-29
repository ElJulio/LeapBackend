#include "KeyRecognition_C.h"
#include <iostream>
#include <thread>
#include <Windows.h>

KeyRecognition_C::KeyRecognition_C(JsonCreator_C* jsonCreator):
	mJsonCreator(jsonCreator)
{
}

KeyRecognition_C::~KeyRecognition_C()
{
}

void KeyRecognition_C::StartMainLoop()
{
	std::thread t(&KeyRecognition_C::MainLoop, this);
	t.join();
}

void KeyRecognition_C::MainLoop() {
	std::cout << "KeyRecognition_C started" << std::endl;
	bool aIsDown = false;
	bool qIsDown = false;
	for (;;)
	{
		if (GetKeyState('A') & 0x8000)
		{
			aIsDown = true;
		}
		else if (aIsDown)
		{
			aIsDown = false;
			std::cout << "a released" << std::endl;
			auto stamp = std::chrono::system_clock::now();
			std::time_t stampTime = std::chrono::system_clock::to_time_t(stamp);
			mJsonCreator->SetNextStep(stampTime);
		}
		if (GetKeyState('Q') & 0x8000)
		{
			qIsDown = true;
		}
		else if (qIsDown)    
		{
			qIsDown = false;
			break;
		}
	}
}

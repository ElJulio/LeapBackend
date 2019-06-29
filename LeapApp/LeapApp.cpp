// LeapApp.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//


#define STANDALONE
#undef APIMODE

#include <iostream>
#include <thread>
#include <chrono>
#ifdef STANDALONE
#include "LeapController_C.h"
#endif // STANDALONE
#ifdef APIMODE
#include "LeapApiInterface_C.h"
#endif // APIMODE


int main()
{
	
#ifdef APIMODE
	LeapApiInterface_C li; //Cerate an Instance of the Interface
	std::thread lt(&LeapApiInterface_C::StartDataCollectionThread, li); //Start the Data collection in an background thread
	for (;;)
	{
		std::vector < LeapDataBuffer_C::LeapData > ld = li.PollLeapData(); //Polling the Data
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	lt.join();
#endif // APIMODE

#ifdef STANDALONE
	LeapController_C lc;

#endif // STANDALONE

	
		
}

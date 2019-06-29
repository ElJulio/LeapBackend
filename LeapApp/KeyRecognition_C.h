#pragma once

#include "JsonCreator_C.h"

class KeyRecognition_C
{
public:
	KeyRecognition_C(JsonCreator_C* jsonCreator);
	~KeyRecognition_C();

	/**
	*@brief Starting the main loop to capture key strokes
	*/
	void StartMainLoop();

	void MainLoop();


private:

	/*Member Variables*/
	JsonCreator_C* mJsonCreator;
};


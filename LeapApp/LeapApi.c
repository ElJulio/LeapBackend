

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "LeapApi.h"
#include "BaseUtils_C.h"

int lastFrameID = 0; //The last frame received


int GetLeapData(LEAP_HAND* leapHand[], const uint8_t bufzize, int64_t* frameID, uint8_t* nHands) {
	if (!IsConnected)
	{
		OpenConnection();
		while (!IsConnected)
			millisleep(100); //wait a bit to let the connection complete
		printf("Try to connected... \n");
		LEAP_DEVICE_INFO* deviceProps = GetDeviceProperties();
		if (deviceProps)
			printf("Using device %s.\n", deviceProps->serial);
		else 
		{
			printf("No LeapMotion found!\n");
			printf("Press: Q to end\n");
			return 2;
		}
	}
	

	LEAP_TRACKING_EVENT* frame = GetFrame();
	if (frame && (frame->tracking_frame_id > lastFrameID)) {
		lastFrameID = frame->tracking_frame_id;
		if (bufzize < frame->nHands)
			return 1;
		for (uint32_t h = 0; h < frame->nHands; h++) {
			leapHand[h] = &frame->pHands[h];
			*frameID = lastFrameID;
		}
		*nHands = frame->nHands;
	}
	return 0;
}
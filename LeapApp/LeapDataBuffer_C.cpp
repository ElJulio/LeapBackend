#include "LeapDataBuffer_C.h"
#include <iostream>



LeapDataBuffer_C::LeapDataBuffer_C()
{
}


LeapDataBuffer_C::~LeapDataBuffer_C()
{
}

std::vector<LeapDataBuffer_C::LeapData> LeapDataBuffer_C::PollLeapData()
{
	std::lock_guard<std::mutex> lock(mMutex);
	
	LeapDataBuffer tmpbuf = mLeapDataBuffer;
	mLeapDataBuffer = LeapDataBuffer();
	return tmpbuf;
	
}

void LeapDataBuffer_C::SaveData(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID)
{
	
	if (this != NULL)
	{
		std::lock_guard<std::mutex> lock(mMutex);
	}
	else {
		std::cout << "You might have configured apimode but using it as standalone! \nBreak here!" << std::endl;
		return;
	}

	LeapData leapData;
	leapData.frameID = frameID;
	leapData.nHands = nHands;
	for (uint8_t handCount = 0; handCount < nHands; handCount ++)
	{
		HandData handData;

		handData.id = hands[handCount]->id;

		handData.thumb.pos.x = hands[handCount]->thumb.bones->next_joint.x;
		handData.thumb.pos.y = hands[handCount]->thumb.bones->next_joint.y;
		handData.thumb.pos.z = hands[handCount]->thumb.bones->next_joint.z;

		handData.index.pos.x = hands[handCount]->index.bones->next_joint.x;
		handData.index.pos.y = hands[handCount]->index.bones->next_joint.y;
		handData.index.pos.z = hands[handCount]->index.bones->next_joint.z;

		handData.middle.pos.x = hands[handCount]->middle.bones->next_joint.x;
		handData.middle.pos.y = hands[handCount]->middle.bones->next_joint.y;
		handData.middle.pos.z = hands[handCount]->middle.bones->next_joint.z;

		handData.ring.pos.x = hands[handCount]->ring.bones->next_joint.x;
		handData.ring.pos.y = hands[handCount]->ring.bones->next_joint.y;
		handData.ring.pos.z = hands[handCount]->ring.bones->next_joint.z;

		handData.pinky.pos.x = hands[handCount]->pinky.bones->next_joint.x;
		handData.pinky.pos.y = hands[handCount]->pinky.bones->next_joint.y;
		handData.pinky.pos.z = hands[handCount]->pinky.bones->next_joint.z;

		handData.palm.pos.x = hands[handCount]->palm.position.x;
		handData.palm.pos.y = hands[handCount]->palm.position.y;
		handData.palm.pos.z = hands[handCount]->palm.position.z;

		leapData.handDataCollection.push_back(handData);
	}
	mLeapDataBuffer.push_back(leapData);
}
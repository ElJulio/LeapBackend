#include "JsonCreator_C.h"
#include <fstream>
#include <iostream>

JsonCreator_C::JsonCreator_C()
{
	auto stamp = std::chrono::system_clock::now();
	std::time_t stampTime = std::chrono::system_clock::to_time_t(stamp);
	mFileName = std::to_string(stampTime) + "_leap.json";
	std::ofstream outfile;
	outfile.open(mFileName, std::ios::out);
	outfile << "[" << std::endl;
	outfile.close();
}


JsonCreator_C::~JsonCreator_C()
{
	std::ofstream outfile;
	outfile.open(mFileName, std::ios_base::app);
	outfile << "]" << std::endl;
	outfile.close();
}

void JsonCreator_C::WriteJson(LEAP_HAND* hands[], uint8_t nHands, int64_t frameID)
{	

	nlohmann::json leapJson;
	std::ofstream outfile;

	std::vector<nlohmann::json> handsJson;
	outfile.open(mFileName, std::ios_base::app);
	for (int handCount = 0; handCount < nHands; handCount++) {
		
		nlohmann::json handJson = {
			{"id", hands[handCount]->id},
			{"palm",{
				{"position",{
						{"x", hands[handCount]->palm.position.x},
						{"y", hands[handCount]->palm.position.y},
						{"z", hands[handCount]->palm.position.z}
					}
				}
			}
			},
			{"index",{
				{"position",
					{
						{"x", hands[handCount]->index.bones->next_joint.x},
						{"y", hands[handCount]->index.bones->next_joint.y},
						{"z", hands[handCount]->index.bones->next_joint.z}
					}
				}
			}
			},
			{"middle",{
				{"position",
					{
						{"x", hands[handCount]->middle.bones->next_joint.x},
						{"y", hands[handCount]->middle.bones->next_joint.y},
						{"z", hands[handCount]->middle.bones->next_joint.z}
					}
				}
			}
			},
			{"ring",{
				{"position",
					{
						{"x", hands[handCount]->ring.bones->next_joint.x},
						{"y", hands[handCount]->ring.bones->next_joint.y},
						{"z", hands[handCount]->ring.bones->next_joint.z}
					}
				}
			}
			},
			{"pinky",{
				{"position",
					{
						{"x", hands[handCount]->pinky.bones->next_joint.x},
						{"y", hands[handCount]->pinky.bones->next_joint.y},
						{"z", hands[handCount]->pinky.bones->next_joint.z}
					}
				}
			}
			},
			{"thumb",{
				{"position",
					{
						{"x", hands[handCount]->thumb.bones->next_joint.x},
						{"y", hands[handCount]->thumb.bones->next_joint.y},
						{"z", hands[handCount]->thumb.bones->next_joint.z}
					}
				}
			}
			}
		};
		
		handsJson.push_back(handJson);
	}

	auto stamp = std::chrono::system_clock::now();     
	std::time_t stampTime = std::chrono::system_clock::to_time_t(stamp);

	leapJson["timeStamp"] = stampTime;
	leapJson["frameID"] = frameID;
	leapJson["nHands"] = nHands;
	leapJson["hands"] = handsJson;
	if (mNextStep)
	{
		leapJson["nextStep"] = GetNextStep();
	}
	else
	{
		leapJson["nextStep"] = -1;
	}

	if (!GetIsLastFrame())
	{
		outfile << leapJson << "," << std::endl;
	}
	else
	{
		outfile << leapJson << std::endl;
		std::cout << "last frame" << std::endl;
	}

	std::cout << stampTime << std::endl;
	outfile.close();
}

void JsonCreator_C::SetNextStep(std::time_t timeStamp)
{
	std::lock_guard<std::mutex> guard(mMutex);
	mNextStepTime = timeStamp;
	mNextStep = true;
}

void JsonCreator_C::IsLastFrame()
{
	std::lock_guard<std::mutex> guard(mMutex);
	mIsLastFrame = true;
}

bool JsonCreator_C::GetIsLastFrame()
{
	std::lock_guard<std::mutex> guard(mMutex);
	return mIsLastFrame;
}

std::time_t JsonCreator_C::GetNextStep()
{
	std::lock_guard<std::mutex> guard(mMutex);
	mNextStep = false;
	return mNextStepTime;
}

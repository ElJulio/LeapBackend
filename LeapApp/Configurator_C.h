#pragma once
class Configurator_C
{
public:

	struct LeapConf_ST
	{
		bool compressionActive; // do only save canging values
		float threshHold;	    // set the value when a change is recognized
		bool smoothingActive;	// active for smoothing the curve
		int somothingBuffer;	// value that defines how many frames should be used for median calc
		bool apiMode;			// If in API mode no JSON is created but the data can be polled over the LeapApiInterface
	};

	Configurator_C();
	~Configurator_C();

	/*
	*@brief GetConf() returns the config values
	*@return LeapConf_ST
	*/
	Configurator_C::LeapConf_ST GetConf();

	
};

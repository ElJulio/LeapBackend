#include "Configurator_C.h"
#include "../../LibConfig/libconfig.h++"
#include <iostream>
#include <iomanip>

using namespace std;

Configurator_C::Configurator_C()
{
		
}

Configurator_C::~Configurator_C()
{
}

Configurator_C::LeapConf_ST Configurator_C::GetConf()
{
	std::cout << "Start configuration" << std::endl;
	libconfig::Config cfg;
	LeapConf_ST leapConf;

	try
	{
		cfg.readFile("LeapApp.cfg");
	}
	catch (const libconfig::FileIOException & fioex)
	{
		std::cerr << "I/O error while reading file." << std::endl;
	}
	catch (const libconfig::ParseException & pex)
	{
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
			<< " - " << pex.getError() << std::endl;
	}
	

	// Get the values
	try
	{
		leapConf.compressionActive = cfg.lookup("compressionActive");
		leapConf.threshHold = cfg.lookup("threshHold");
		leapConf.smoothingActive = cfg.lookup("smoothingActive");
		leapConf.somothingBuffer = cfg.lookup("somothingBuffer");
		leapConf.apiMode = cfg.lookup("apiMode");
	}
	catch (exception)
	{
		cerr << "Wrong config vlues detected" << endl;
		return LeapConf_ST();
	}
	std::cout << "Successfully read cfg" << std::endl;
	return leapConf;
}

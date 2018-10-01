#ifndef GENERICDEVICE_HPP
#define GENERICDEVICE_HPP

#include "m2kglobal.hpp"
#include <string>
#include <iio.h>
#include "analogin.hpp"


namespace libm2k {
namespace devices {
class LIBM2K_API GenericDevice {
	static std::vector<AnalogIn*> s_instancesAnalogIn;
public:
	GenericDevice(std::string uri, struct iio_context*, std::string name);
	~GenericDevice();
	AnalogIn* analogInOpen();
	void analogInClose(AnalogIn*);
	AnalogIn* getAnalogInInstance(std::string);
	void blinkLed();
	static GenericDevice* getDevice(std::string uri);
private:
	std::string m_uri;
	iio_context* m_ctx;
};
}
}

#endif // GENERICDEVICE_HPP
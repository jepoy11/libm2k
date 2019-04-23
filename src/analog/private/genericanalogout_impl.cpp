/*
 * Copyright 2018 Analog Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file LICENSE.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "../../utils/private/device_impl.cpp"
#include <libm2k/analog/genericanalogout.hpp>
#include <libm2k/m2kexceptions.hpp>
#include <libm2k/utils/utils.hpp>
#include <iostream>

using namespace std;
using namespace libm2k::analog;
using namespace libm2k::utils;

class GenericAnalogOut::GenericAnalogOutImpl : public DeviceImpl {
public:

	GenericAnalogOutImpl(iio_context *ctx, std::string dac_dev):
		DeviceImpl(ctx, dac_dev)
	{
	}

	~GenericAnalogOutImpl()
	{

	}

	double getSamplerate()
	{
		return getDoubleValue("sampling_frequency");
	}

	double getSamplerate(unsigned int chn_idx)
	{
		return getDoubleValue(chn_idx, "sampling_frequency", true);
	}

	double setSamplerate(double sampleRate)
	{
		return setDoubleValue(sampleRate, "sampling_frequency");
	}

	double setSamplerate(unsigned int chn_idx, double sampleRate)
	{
		return setDoubleValue(chn_idx, sampleRate,
				      "sampling_frequency", true);
	}

	std::vector<double> getAvailableSamplerates()
	{
		return DeviceImpl::getAvailableSamplerates();
	}

	void setCyclic(bool en)
	{
		for (unsigned int i = 0; i < getNbChannels(); i++) {
			m_cyclic.at(i) = en;
		}
	}

	void setCyclic(bool en, unsigned int chn)
	{
		if (chn >= getNbChannels()) {
			throw_exception(EXC_INVALID_PARAMETER, "Generic Analog Out: No such channel");
		}
		m_cyclic.at(chn) = en;
	}

	bool getCyclic(unsigned int chn)
	{
		if (chn >= getNbChannels()) {
			throw_exception(EXC_INVALID_PARAMETER, "Generic Analog Out: No such channel");
		}
		return m_cyclic.at(chn);
	}

	void push(std::vector<short> const &data, unsigned int chn_idx)
	{
		DeviceImpl::push(data, chn_idx, getCyclic(chn_idx));
	}

	void push(std::vector<double> const &data, unsigned int chn_idx)
	{
		DeviceImpl::push(data, chn_idx, getCyclic(chn_idx));
	}

	void openAnalogOut()
	{

	}

	void closeAnalogOut()
	{

	}

	void stop()
	{
		DeviceImpl::stop();
	}

private:
	std::vector<bool> m_cyclic;
};
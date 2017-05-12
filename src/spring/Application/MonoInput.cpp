#include "spring/Application/MonoInput.h"
#include <qendian.h>
#include <iostream>

MonoInput::MonoInput(double timeSlice, unsigned sampleRate)
	:dataLength(timeSlice * sampleRate),
	channelBytes(2)
{
	audioFormat.setSampleRate(sampleRate);
	audioFormat.setChannelCount(1);
	audioFormat.setSampleSize(16);
	audioFormat.setCodec("audio/pcm");
	audioFormat.setByteOrder(QAudioFormat::LittleEndian);
	audioFormat.setSampleType(QAudioFormat::SignedInt);

	maxAmplitude = 32767;
}


MonoInput::~MonoInput()
{
}

qint64 MonoInput::writeData(const char *data, qint64 len)
{
	//const auto *ptr = reinterpret_cast<const unsigned char *>(data);
	const auto *ptr = data;

	for (auto i = 0; i < len / channelBytes; ++i) {

		qint32 value = 0;

		value = qFromLittleEndian<qint16>(ptr);
		
		auto level = float(value) * (5./ maxAmplitude);
		timeData.push_back(level);
		ptr += channelBytes;
	}

	if (timeData.size() > dataLength)
		timeData.remove(0, timeData.size() - dataLength);

	std::cout << "data received " << len << std::endl;

	return len;
}


QAudioFormat MonoInput::getAudioFormat()
{
	return audioFormat;
}

QVector<double> MonoInput::vecGetData() const
{
	return timeData;
}
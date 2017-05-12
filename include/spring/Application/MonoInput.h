#pragma once
#include <QVector>
#include <qaudioformat.h>
#include <qiodevice.h>

class MonoInput: public QIODevice
{
public:
	MonoInput(double timeSlice, unsigned sampleRate);
	virtual ~MonoInput();

	qint64 readData(char *data, qint64 maxlen) override
	{
		Q_UNUSED(data);
		Q_UNUSED(maxlen);
		return -1;
	}

	qint64 writeData(const char *data, qint64 len) override;

	virtual QAudioFormat getAudioFormat();
	virtual QVector<double> vecGetData() const;

private:
	QAudioFormat audioFormat;
	QVector<double> timeData;
	const unsigned dataLength;
	const unsigned channelBytes;
	qint32 maxAmplitude;
};


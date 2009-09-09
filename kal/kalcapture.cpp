#include "kalcapture.h"
#include <KDebug>
#include <QTime>
#include <QFile>
KALCapture::KALCapture(QString deviceName, QObject *parent)
        : QObject(parent)
{
    if (isAvailable()) {
        captureDevice = alcCaptureOpenDevice(deviceName.toUtf8(), 44100, AL_FORMAT_MONO16, 44100);
    } else {
        kError() << "No capture device available";
        return;
    }

    if (!captureDevice) {
        kError() << "Could not set the capture device";
        return;
    }
}

KALCapture::~KALCapture()
{
    alcCaptureCloseDevice(captureDevice);
}

bool KALCapture::isAvailable()
{
    return alcIsExtensionPresent(device, "ALC_EXT_CAPTURE");
}

// TODO: This is mostly copy-pasted from KALEngine::deviceList(), find a way to avoid code duplication
QStringList KALCapture::deviceList()
{
    const ALCchar* devices = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);

    // alcGetString returns a list of devices separated by a null char (the list itself ends with a double null char)
    // So we can't pass it directly to QStringList
    QStringList list;
    if (devices) {
        while (strlen(devices) > 0) {
            list.append(devices);
            devices += strlen(devices) + 1;
        }
    }
    return list;
}

//FIXME: Why is there code duplication here?
void KALCapture::record(int duration)
{
    QTime recordTime;
    recordTime.start();

    while (recordTime.elapsed() < duration) {
        ALCint samplesAvailable;
        alcGetIntegerv(captureDevice, ALC_CAPTURE_SAMPLES, 1, &samplesAvailable);
        if (samplesAvailable > 0) {
            samples.append(samplesAvailable);
            alcCaptureSamples(captureDevice, &samples.last(), samplesAvailable);
        }
    }

    alcCaptureStop(captureDevice);

    ALCint samplesAvailable;
    alcGetIntegerv(captureDevice, ALC_CAPTURE_SAMPLES, 1, &samplesAvailable);
    if (samplesAvailable > 0) {
        samples.append(samplesAvailable);
        alcCaptureSamples(captureDevice, &samples.last(), samplesAvailable);
    }

}


void KALCapture::save(const QString& fileName)
{
    SF_INFO fileInfo;
    fileInfo.channels = 1;
    fileInfo.samplerate = 44100;
    fileInfo.format = SF_FORMAT_PCM_16 | SF_FORMAT_WAV;

    SNDFILE *file = sf_open(fileName.toUtf8(), SFM_WRITE, &fileInfo);

    if (!file)
        return;

    sf_write_short(file, &samples[0], samples.size());

    sf_close(file);
}
qpulsedevicelistfetcher
=======================

This repository contains `QPulseDeviceListFetcher`, a class that allows Qt
to get PulseAudio's input and output device lists. This repository builds a demo
application that displays the fields that the fetcher provides.

The repository example is built using Qt 5 and builds with CMake.

### Usage

Add `QPulseDeviceListFetcher.{cpp,h}` to your project, as well as the CMake
rules to search for PulseAudio. The fetcher does **not** spawn a thread, and
**will** block.

### Interface

```
class QPulseDeviceEntry : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int index READ index);
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(QString desc READ desc);

public:
    QPulseDeviceEntry(const char *n, const char *d, int i)
    {
        m_name = n;
        m_desc = d;
        m_index = i;
    }

    int index(void) const { return m_index; }
    QString desc(void) const { return m_desc; }
    QString name(void) const { return m_name; }

private:
    int m_index;
    QString m_desc;
    QString m_name;
};

class QPulseDeviceListFetcher
{
public:
    static QList<QPulseDeviceEntry *> readSinkOutputs(void);
    static QList<QPulseDeviceEntry *> readSourceInputs(void);
};
```

### Credit

This is an adaptation of the following:

https://www.freedesktop.org/wiki/Software/PulseAudio/Documentation/Developer/Clients/Samples/AsyncDeviceList/

#ifndef QPULSEDEVICELISTFETCHER_H
# define QPULSEDEVICELISTFETCHER_H
# include <QObject>

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

#endif

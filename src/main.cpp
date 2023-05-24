#include <QApplication>
#include <QDebug>

#include "qpulsedevicelistfetcher.h"

#define SHOW_RESULTS(func, entry_kind) \
{ \
    auto srcs = QPulseDeviceListFetcher::func(); \
 \
    for (int i = 0;i < srcs.size();i++) { \
        QPulseDeviceEntry *e = srcs[i]; \
 \
        qDebug() << "=====[ " entry_kind " Entry #" << i << "]====="; \
 \
        qDebug() << "Name: " << e->name(); \
        qDebug() << "Desc: " << e->desc(); \
        qDebug() << "Index: " << e->index(); \
    } \
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    SHOW_RESULTS(readSourceInputs, "Input")
    qDebug() << "";
    SHOW_RESULTS(readSinkOutputs, "Output")
    return app.exec();
}

#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include "sfdownloadpreparer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    SFDownloadPreparer preparer;
    preparer.download("DJWY");
    return a.exec();
}

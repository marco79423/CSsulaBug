#include <QtGui/QApplication>
#include <QTextCodec>
#include "lister.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    Lister w;
    w.show();
    
    return a.exec();
}

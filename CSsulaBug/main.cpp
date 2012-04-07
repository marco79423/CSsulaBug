#include <QApplication>
#include <QTextCodec>
#include <QTextBrowser>

#include "networkaccessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    
    NetworkAccessor accessor;

    QTextBrowser browser;
    QObject::connect(&accessor, SIGNAL(oneReply(QString)),
                     &browser, SLOT(append(QString)));
    browser.show();
    accessor.get(QList<QString>()<<"http://csbala.nba.nctu.edu.tw"
                 <<"http://csbala.nba.nctu.edu.tw"
                 <<"http://csbala.nba.nctu.edu.tw"
                 );


    return a.exec();
}

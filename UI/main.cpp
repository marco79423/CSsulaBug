#include <QApplication>
#include <QDeclarativeView>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDeclarativeView view;

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    view.setSource(QUrl("qrc:/main.qml"));
    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view.show();
    return app.exec();
}

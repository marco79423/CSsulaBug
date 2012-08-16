#include <QtGui>
#include <QtDeclarative>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList list;
    list << "Item1" << "Item2" << "Item3";
    QDeclarativeView view;
    view.rootContext()->setContextProperty("comicModel", QVariant::fromValue(list));
    view.setSource(QUrl("test.qml"));
    view.show();
    return a.exec();
}

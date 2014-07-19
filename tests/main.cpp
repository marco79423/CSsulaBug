#include <QString>
#include <QDebug>

#include <convertz.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(src_resource);

    ConvertZ convertz;
    QString tpattern = convertz.convertToTraditional("今天天气不错");
    qDebug() << tpattern;
}

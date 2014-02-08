#include <QtCore>
#include <QtGui>

QString convertToTraditional(const QString &content)
{
    QFile file("convertz.dat");
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Form::can't open convertz";
    }

    QHash<QChar, QChar> table;
    QDataStream in(&file);
    in >> table;
    qDebug() << "size" <<table.size();

    QString word = "用";
    qDebug() << table[word[0]];
    QString traditional;
    /*foreach(QChar word, content)
    {
        qDebug() << word << table.value(word, QChar());
        traditional += table.value(word, word);
    }*/

    return traditional;
}

int main(int argc, char *argv[])
{
    QFile content("../../../convertz.res");
    content.open(QIODevice::ReadOnly);
    QTextStream in(&content);
    QString sim = in.readLine();
    qDebug() << "get sim";
    QString tra = in.readLine();
    qDebug() << "get tra";

    QHash<QChar, QChar> table;
    for(int i=0; i < sim.size(); i++)
    {
        qDebug() << sim[i] << tra[i];
        table[sim[i]] = tra[i]; 
    }
    QFile output("../../../convertz.dat");
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QDataStream out(&output);
    out << table;
    qDebug() << "done";
    output.close();
    /*
    QString string = "使用繁体字";
    //QString string2 = convertToTraditional(string);

    QFileInfo info("../../../convertz.dat");
    qDebug() << info.absoluteFilePath();
    QFile file("../../../convertz.dat");
    if(!file.open(QIODevice::ReadOnly))
        qCritical() << "無法開啟 convertz.dat";

    QHash<QChar, QChar> table;
    QDataStream in(&file);
    in >> table;
    file.close();

    foreach(QChar word, table.keys())
        qDebug() << word << table[word];*/
}

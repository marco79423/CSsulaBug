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
    QApplication app(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    QFile content("convertz.res");
    content.open(QIODevice::ReadOnly);
    QTextStream in(&content);
    QString sim = in.readLine();
    qDebug() << "get sim";
    QString tra = in.readLine();
    qDebug() << "get tra";

    QHash<QChar, QChar> table;
    for(int i=0; i < sim.size(); i++)
    {
        table[sim[i]] = tra[i]; 
    }
    qDebug() << table.size();
    QFile output("convertz.dat");
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QDataStream out(&output);
    out << table;
    qDebug() << "done";
    output.close();

    QString word = "用";
    qDebug() << table[word[0]];

    QString string = "使用繁体字";
    QString string2 = convertToTraditional(string);

    QTextBrowser browser;
    browser.append(string);
    browser.append(string2);
    browser.append(QString(sim[75]));
    browser.append(QString(tra[75]));

    browser.show();
    return app.exec();
}

#ifndef MOCKFILESAVER_H
#define MOCKFILESAVER_H

#include <afilesaver.h>

class MockFileSaver: public AFileSaver
{
public:

    MOCK_METHOD2(saveFile, SaverStatus(const QByteArray& data, const QString& filePath));
};


#endif // MOCKFILESAVER_H


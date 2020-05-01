#ifndef CTABLESAVER_H
#define CTABLESAVER_H

#include <QObject>
#include <QFile>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
#include <QByteArray>
#include <QTableWidget>
#include <QTextStream>
#include "xbifile.h"
#include "cchain.h"

class CXBISaver
{
public:
    CXBISaver();
    void SaveFile3(XBIfile * file, QString filePath);
    void LoadFile3(XBIfile* loadedFile,QString filePath);
    void CreateNewFile(QString filePath,QString fileName);
private:
    QStringList columnNameList;
};

#endif // CTABLESAVER_H

#ifndef CFILESYSTEM_H
#define CFILESYSTEM_H

#include <QObject>
#include <QFile>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
#include <QByteArray>

class CFileSystemm {
public:
    CFileSystemm();
    ~CFileSystemm() { this->Close(); }
    void Open( string path );
    void Open( QString path ) { this->Open(path.toStdString()); }
    void Close();
    void Write( string text );
    QByteArray Read(  );
    bool is_open() { return file.isOpen(); }
private:
    QFile file;
    QString path;

};

#endif // CFILESYSTEM_H

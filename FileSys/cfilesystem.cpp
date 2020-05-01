#include "cfilesystem.h"
#include <QTextStream>

CFileSystemm::CFileSystemm( )
{

}

void CFileSystemm::Open(string path)
{
    this->path = path.c_str();

    file.setFileName(path.c_str());
    file.open(QIODevice::Append | QIODevice::ReadWrite | QIODevice::Text);
    if(!file.isOpen()) {
        cout << "ERROR: file isnt open" << endl;
    }
}

void CFileSystemm::Close()
{
   file.close();
}

void CFileSystemm::Write(string text)
{
    file.setFileName( path );
    file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
    if(!file.isOpen()) {
        cout << "ERROR: file isnt open" << endl;
    }
    QTextStream ss(&file);
    ss << text.c_str();
    this->Close();
}

QByteArray CFileSystemm::Read()
{
    file.setFileName( path );
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen()) {
        cout << "ERROR: file isnt open" << endl;
    }
    QByteArray res = file.read(file.size());
    this->Close();
    return res;
}

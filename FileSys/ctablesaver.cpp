#include "ctablesaver.h"
#include <QByteArray>
#include <QDebug>
#include <QTextCodec>
#include <QFileDialog>
#include "FileSys/cfilesystem.h"

CXBISaver::CXBISaver()
{
    columnNameList.push_back(QString("Имя"));
    columnNameList.push_back(QString("Родитель"));
    columnNameList.push_back(QString("Размер Поля"));
    columnNameList.push_back(QString("Описание"));
}

void CXBISaver::SaveFile3(XBIfile *file, QString filePath)
{
    QFile tfile;
    tfile.setFileName(filePath);
    tfile.open(QIODevice::WriteOnly | QIODevice::Text);
    tfile.resize(0);
    QTextStream ss(&tfile);
    ss << "\\f" << file->GetName().c_str(); // установка имени файла
    for(int chainid=0;chainid<file->GetChainSize();chainid++)
    {
        ss << "\\c" << file->GetChain(chainid)->GetName().c_str(); // установка имени узла
        for(int rowid=0;rowid<file->GetChain(chainid)->RowSize();rowid++)
        {
            for(int columnid=0;columnid<4;columnid++)
            {
                //todo: сделать запись так чтобы блять был один ебучий паттерн у булевой хуеты, либо t/f либо сука 1/0 а то не к хую не к жопе
                ss << "\\d" << file->GetChain(chainid)->GetItem(rowid,columnid).c_str();
            }
        }
    }
    ss << "\n";
}

void CXBISaver::LoadFile3(XBIfile * loadedFile,QString filePath)
{
    int chainCounter = -1, columnCounter = 0, rowCounter = 0;
    loadedFile->SetPath(filePath.toStdString());
    QFile tfile;
    tfile.setFileName(filePath);
    tfile.open(QIODevice::ReadWrite | QIODevice::Text);

    QByteArray arr = tfile.readAll();
    int arrid = 0; bool done = false;
    while(!done)
    {
        QString fileName,chainName,columnName,cellData;
        if(arr[arrid] == '\\') {
            arrid++;
            switch (arr[arrid]) {
            case 'f': // filename
                fileName.clear();
                arrid++;
                while(arr[arrid] != '\\') {
                    fileName += arr[arrid];
                    arrid++;
                }
                loadedFile->SetName(fileName.toStdString());
                qDebug() << fileName << endl;
            break;
            case 'c': // chainname
                chainName.clear();
                arrid++;
                while(arr[arrid] != '\\') {
                    chainName += arr[arrid];
                    arrid++;
                }
                chainCounter++;
                loadedFile->GetNewChain(chainName.toStdString());
                loadedFile->GetChain(chainCounter)->AddField(SField());
                rowCounter = 0;
                columnCounter = 0;
                qDebug() << chainName << endl;
            break;
            case 'd': // celldata
                cellData.clear();
                arrid++;
                while(arr[arrid] != '\\') {
                    if(arr[arrid] == '\n' || arrid > arr.size()) { break;
                    } else {
                        cellData += arr[arrid];
                        arrid++;
                        //qDebug() << arr[arrid] << endl;
                    }
                }
                loadedFile->GetChain(chainCounter)->SetItem(cellData,rowCounter,columnCounter);
                columnCounter++;
                if(columnCounter > 3 && arr[arrid] != '\n') {
                    qDebug() << "new row" << endl;
                    columnCounter = 0;
                    rowCounter++;
                    loadedFile->GetChain(chainCounter)->AddField(SField());

                }
                qDebug() << cellData << endl;
            break;
            }
        } else {
            arrid++;
        }
        if(arrid >= arr.size() || arr[arrid] == '\n') done = true;
        qDebug() << arrid << "|"<< arr.size() << endl;
    }
    qDebug() << "file is loaded" << endl;
}

void CXBISaver::CreateNewFile(QString filePath,QString fileName)
{
    QFile tfile;
    tfile.setFileName(filePath);
    tfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream ss(&tfile);
    ss << "\\f" << fileName /*<< "\\cbch\\d0\\d0\\d0\\d0"*/ << endl; // установка имени файла
}

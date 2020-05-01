#ifndef CMODEL_H
#define CMODEL_H

#include <QStringList>
#include <QString>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
#include <QTableWidget>

#include "cpsqldatabase.h"
#include "xbifile.h"
#include "FileSys/cfilesystem.h"


class CModel {
public:
    CModel();
    void Init();

    void NewFile(string path,string name);
    void NewFile(QString path,QString name) { this->NewFile(path.toStdString(),name.toStdString()); }
    void OpenFile(QString path);
    void AddNewChainToFile(string filePath,string chainName);
    void AddNewChainToFile(QString filePath,QString chainName) { this->AddNewChainToFile(filePath.toStdString(),chainName.toStdString()); }

    void FillTableWidget(QTableWidget * table,QString chainName);
    void FillTableWidget(QTableWidget * table,QString filePath,QString chainName);
    void FillChainFromDb(CChain * chain);

    void DeleteFile(int id);

    XBIfile* GetFile(int id);
    int FileAmmount() { return xbiFileList.size(); }

    void LoadWorkbanchDirectoryPath(QString path) { workbanchDirectoryName = path; }
    void LoadFileNames(QStringList fileNames);
    void LoadConnectionTool(CPSQLDatabase * connTool) { connectionTool = connTool; }


    void LoadExistingFile(string filePath);
    void LoadExistingFile(QString filePath) { this->LoadExistingFile(filePath.toStdString()); }


    void ConsoleShowFileNames();

    QString GetWorkbanchDirectoryPath() { return workbanchDirectoryName; }
    QStringList GetFileNames() { return fileNames; }
    QStringList GetChainNames(QString filePath);
    CPSQLDatabase* GetConnectionTool() { return connectionTool; }

    void SaveAllFiles();
    void DropAllTables();
private:
    vector<XBIfile> xbiFileList;
    QString workbanchDirectoryName;
    QStringList fileNames;
    CPSQLDatabase * connectionTool;
};

#endif // CMODEL_H

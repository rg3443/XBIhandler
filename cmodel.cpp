#include "cmodel.h"
#include <QTableWidgetItem>
#include <QTextCodec>
#include "FileSys/ctablesaver.h"
#include <QDebug>

CModel::CModel()
{

}

void CModel::NewFile(string path,string name)
{
    XBIfile newFile; newFile.Init(name,path);
    xbiFileList.push_back(newFile);
}

void CModel::OpenFile(QString path)
{
    CXBISaver loader;
    cout << path.toStdString() << endl;
    xbiFileList.push_back(XBIfile());
    loader.LoadFile3(&xbiFileList[xbiFileList.size()-1], path);
    xbiFileList[xbiFileList.size()-1]._ConsoleShow();
    for(int chainid=0;chainid<xbiFileList[xbiFileList.size()-1].GetChainSize();chainid++) {
        CChain* chain = xbiFileList[xbiFileList.size()-1].GetChain(chainid);
        string chainName = chain->GetName();
        string command = "create table "+chainName+"(Имя text,Родитель boolean, Размер_поля integer, Описание text);";
        connectionTool->ExecCommand(command);
        if(chain->RowSize() != 0) {
            for(int rowid=0;rowid>chain->RowSize();rowid++)
            {
                string insertCommand = "insert into " + chainName + " values("
                        +"'"+chain->GetItem(rowid,0)+"',"
                        +chain->GetItem(rowid,1)+","
                        +chain->GetItem(rowid,2)+","
                        +"'"+chain->GetItem(rowid,3)+"');";
                connectionTool->ExecCommand(insertCommand);

            }
        }
    }
    qDebug() << "file opened" << endl;
}

void CModel::AddNewChainToFile(string filePath,string chainName)
{
    bool done = false;
    for(int i=0;i<xbiFileList.size();i++) {
        if(xbiFileList[i].GetPath() == filePath && !done) {
            xbiFileList[i].AddChain(chainName);
            QFile tfile;
            tfile.setFileName(QString(filePath.c_str()));
            tfile.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
            tfile.resize(tfile.size()-1); // delete last '\n' symbol
            QTextStream ss(&tfile);
            ss << "\\c" << chainName.c_str() << "\\d0\\d0\\d0\\d0" << endl;
            done = true;
        }
    }
}

void CModel::FillTableWidget(QTableWidget *table, QString chainName)
{
    connectionTool->SelectFromTable(chainName.toStdString());
    for(int x=0;x<connectionTool->GetColumnsAmmount();x++) {
        table->insertRow(x);
        for(int y=0;y<connectionTool->GetRowAmmount();y++) {
            QString item(connectionTool->GetData(y,x).c_str());
            table->setItem(x,y,new QTableWidgetItem(item));
        }
        QStringList columnNames;
        columnNames.push_back(QString("Имя"));
        columnNames.push_back(QString("Родитель"));
        columnNames.push_back(QString("Размер Поля"));
        columnNames.push_back(QString("Описание"));
        table->setHorizontalHeaderLabels(columnNames);
    }
    table->resizeColumnsToContents();
}

void CModel::FillChainFromDb(CChain *chain)
{
    connectionTool->SelectFromTable(chain->GetName());
    chain->Clear();
    for(int y=0;y<connectionTool->GetRowAmmount();y++) {
        chain->AddField(SField(connectionTool->GetData(0,y).c_str(),
                               connectionTool->GetData(1,y).c_str(),
                               connectionTool->GetData(2,y).c_str(),
                               connectionTool->GetData(3,y).c_str()));
    }
}


void CModel::FillTableWidget(QTableWidget *table,QString filePath, QString chainName)
{
    int fileId,chainId;
    for(int fid=0;fid<xbiFileList.size();fid++) {
        if(xbiFileList[fid].GetPath() == filePath.toStdString()) {
            fileId = fid;
            for(int cid=0;cid<xbiFileList[fileId].GetChainSize();cid++) {
                if(xbiFileList[fileId].GetChain(cid)->GetName() == chainName.toStdString()) {
                    chainId = cid;
                }
            }
        }
    }
    CChain* openedChain = xbiFileList[fileId].GetChain(chainId);
    for(int y=0;y<openedChain->RowSize();y++) {
        table->insertRow(y);
        //cout << connectionTool->GetRowAmmount() << endl;
        for(int x=0;x<openedChain->ColumnSize();x++) {
            QString item(openedChain->GetItem(y,x).c_str());
            table->setItem(y,x,new QTableWidgetItem(item));
        }
        QStringList columnNames;
        columnNames.push_back(QString("Имя"));
        columnNames.push_back(QString("Родитель"));
        columnNames.push_back(QString("Размер Поля"));
        columnNames.push_back(QString("Описание"));
        table->setHorizontalHeaderLabels(columnNames);
    }
    table->resizeColumnsToContents();
}

void CModel::DeleteFile(int id)
{
    xbiFileList.erase( xbiFileList.begin()+id );
}

XBIfile* CModel::GetFile(int id)
{
    return &xbiFileList[id];
}

void CModel::LoadFileNames(QStringList fileNames)
{
    this->fileNames = fileNames;
    for(int i=0;i<fileNames.end()-fileNames.begin();i++)
    {
        XBIfile file; file.Init("this function do not working",fileNames[i].toStdString());
        xbiFileList.push_back( file );
    }
    this->ConsoleShowFileNames();
    for(int i=0; i<fileNames.size();i++)
    {
        cout << i <<  "---------------" << endl;
        cout << xbiFileList[i].GetPath() << endl;
        for(int chainID=0;chainID<xbiFileList[i].GetChainSize();chainID++) {
            cout << xbiFileList[i].GetChain(chainID)->GetField(0)->name << endl;
        }
    }
}

void CModel::ConsoleShowFileNames()
{
    for(int i=0;i<fileNames.end()-fileNames.begin();i++)
    {
        cout << fileNames[i].toStdString() << endl;
    }
}

QStringList CModel::GetChainNames(QString filePath)
{
    QStringList list;
    for(int fileID=0;fileID<xbiFileList.size();fileID++) {
        qDebug() << filePath << "|" << xbiFileList[fileID].GetPath().c_str() << endl;
        if(xbiFileList[fileID].GetPath().c_str() == filePath)
        {
            for(int chainid=0;chainid<xbiFileList[fileID].GetChainSize();chainid++) {
                QString suka = xbiFileList[fileID].GetChain(chainid)->GetName().c_str();
                list.push_back(suka);
            }
        }
    }
    return list;
}

void CModel::SaveAllFiles()
{
    CXBISaver saver;
    for(int i=0;i<xbiFileList.size();i++) {
        saver.SaveFile3(&xbiFileList[i],workbanchDirectoryName);
    }
}

void CModel::DropAllTables()
{
    for(int fid=0;fid<xbiFileList.size();fid++) {
        for(int chainid=0;chainid<xbiFileList[fid].GetChainSize();chainid++) {
            CChain * chain = xbiFileList[fid].GetChain(chainid);
            this->FillChainFromDb(chain);
        }
        CXBISaver saver;
        xbiFileList[fid]._ConsoleShow();
        saver.SaveFile3(&xbiFileList[fid],xbiFileList[fid].GetPath().c_str());
    }
    for(int fid=0;fid<xbiFileList.size();fid++) {
        for(int cid=0;cid<xbiFileList[fid].GetChainSize();cid++) {
            string dropCommand = "drop table "
                    +xbiFileList[fid].GetChain(cid)->GetName()+";";
            connectionTool->ExecCommand(dropCommand);
        }
    }
}

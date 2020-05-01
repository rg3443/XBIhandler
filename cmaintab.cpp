#include "cmaintab.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStringList>
#include "ui_mainwindow.h"
#include "cpsqldatabase.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <fstream>
#include "FileSys/cfilesystem.h"
#include <QSqlQuery>
#include "FileSys/ctablesaver.h"
#include <QDebug>


CMainTab::CMainTab(CModel* model, QWidget *parent) : QWidget(parent)
{

    this->model = model;
    slayout = new QGridLayout(this);
    QPushButton * directoryChooseB = new QPushButton("выбор директории",this);
    QPushButton * newFileB = new QPushButton("новый файл",this);
    QPushButton * openFileB = new QPushButton("открыть файл",this);
    QPushButton * openChainB = new QPushButton("открыть узел",this);
    QPushButton * chooseFilesB = new QPushButton("выбор файлов",this);
    QPushButton * saveChainTable = new QPushButton("сохранить изменения",this);
    QPushButton * deleteRow = new QPushButton("удалить строку",this);

    QPushButton * newRow = new QPushButton("новый обьект",this);
    QPushButton * newChainB = new QPushButton("создать узел",this);

    QPushButton * quitProg = new QPushButton("окончание работы",this);


    newFileName = new QLineEdit(this);
    newChainName = new QLineEdit(this);


    toDeleteRowId = new QSpinBox(this);


    fileList = new QComboBox(this);
    chainList = new QComboBox(this);


    tableView[0] = new QTableWidget(this);
    tableView[0]->setColumnCount(4);
    tableView[0]->setShowGrid(true);
    tableView[0]->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList columnNames;
    columnNames.push_back(QString("Имя"));
    columnNames.push_back(QString("Родитель"));
    columnNames.push_back(QString("Размер Поля"));
    columnNames.push_back(QString("Описание"));
    tableView[0]->setHorizontalHeaderLabels(columnNames);


    connect(directoryChooseB,SIGNAL(released()),this,SLOT(OpenDirectory()));
    connect(newFileB,SIGNAL(released()),this,SLOT(NewFile()));
    connect(openFileB,SIGNAL(released()),this,SLOT(OpenFile()));
    connect(openChainB,SIGNAL(released()),this,SLOT(OpenChain()));
    connect(chooseFilesB,SIGNAL(released()),this,SLOT(OpenFiles()));
    connect(newRow,SIGNAL(released()),this,SLOT(AddObjectInToChain()));
    connect(newChainB,SIGNAL(released()),this,SLOT(AddChain()));
    connect(saveChainTable,SIGNAL(released()),this,SLOT(SaveChainTable()));
    connect(deleteRow,SIGNAL(released()),this,SLOT(DeleteRowInCurrentChain()));
    connect(quitProg,SIGNAL(released()),this,SLOT(QuitProg()));


    slayout->addWidget(newRow,0,0); slayout->addWidget(directoryChooseB,0,1); slayout->addWidget(chooseFilesB,0,2);
    slayout->addWidget(tableView[0],1,0); slayout->addWidget(saveChainTable,1,1); slayout->addWidget(deleteRow,1,2); slayout->addWidget(toDeleteRowId,1,3);
    slayout->addWidget(newFileName,2,0); slayout->addWidget(newFileB,2,1); slayout->addWidget(fileList,2,2); slayout->addWidget(openFileB,2,3);
    slayout->addWidget(newChainName,3,0); slayout->addWidget(newChainB,3,1); slayout->addWidget(chainList,3,2); slayout->addWidget(openChainB,3,3);
    slayout->addWidget(quitProg,4,0);

    setLayout(slayout);
}

void CMainTab::OpenDirectory()
{
    model->LoadWorkbanchDirectoryPath(QFileDialog::getExistingDirectory(0,"Выберите директорию",""));
}

void CMainTab::OpenFiles()
{
    model->LoadFileNames(QFileDialog::getOpenFileNames(0,"Выберите файлы","","*.xbi"));
    QStringList fileNames = model->GetFileNames();
    for(int i=0;i<fileNames.size();i++) {
        fileList->addItem(fileNames[i]);
    }
}

void CMainTab::NewFile()
{
    QString filePath = model->GetWorkbanchDirectoryPath() + "/" + newFileName->text() + ".xbi";
        model->NewFile(filePath.toStdString(),newFileName->text().toStdString());
        CXBISaver saver; saver.CreateNewFile(filePath,newFileName->text());
        newFileName->clear();
}

void CMainTab::OpenFile()
{
    QString filePath = fileList->currentText();
    model->OpenFile(filePath);
    QStringList chainNames = model->GetChainNames(filePath);
    qDebug() << chainNames.size() << endl;
    chainList->clear();
    if(chainNames.size() != 0)
    for (int i=0;i<chainNames.size();i++) {
        chainList->addItem(chainNames[i]);
    }
}

void CMainTab::SaveChainTable()// SAVE ALL XBI FILE
{
    CPSQLDatabase * connTool = model->GetConnectionTool();
    connTool->EditTable(tableView[0],chainList->currentText());
    //model->GetFile(fileList->currentIndex())->GetChain(chainList->currentIndex())->LoadTable(tableView[0]);
    //CXBISaver saver; saver.SaveFile3(model->GetFile(fileList->currentIndex()),model->GetFile(fileList->currentIndex())->GetPath().c_str());
    //CTabff
}


void CMainTab::OpenChain()
{
    tableView[0]->clear();
    QStringList columnNames;
    columnNames.push_back(QString("Имя"));
    columnNames.push_back(QString("Родитель"));
    columnNames.push_back(QString("Размер Поля"));
    columnNames.push_back(QString("Описание"));
    tableView[0]->setHorizontalHeaderLabels(columnNames);

    QVariant chainName = chainList->currentText();
    model->FillTableWidget(tableView[0],fileList->currentText(), chainName.toString());
}

void CMainTab::AddChain()
{
    model->AddNewChainToFile(fileList->currentText(),newChainName->text());
    newChainName->clear();
}

void CMainTab::AddObjectInToChain()
{
    tableView[0]->insertRow(tableView[0]->rowCount());
}

void CMainTab::DeleteFile()
{

}

void CMainTab::DeleteRowInCurrentChain()
{
    tableView[0]->removeRow(toDeleteRowId->value()+1);
}

void CMainTab::QuitProg()
{
    model->DropAllTables();
}

#include "cview.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStringList>
#include "ui_mainwindow.h"
#include <QTabWidget>
CView::CView(CModel * model, QWidget *parent) : QWidget(parent)
{
    QTabWidget * tbw = new QTabWidget(this);

    dbWindow = new CConnectDb(model,this);
    mainWindow = new CMainTab(model,this);
    sqlComWindow = new CSQLTab(model,this);

    tbw->addTab(dbWindow,"Коннект к СУБД");
    tbw->addTab(mainWindow,"Редактор");
    tbw->addTab(sqlComWindow,"Direct Query");
    tbw->setGeometry(QRect(QPoint(0,0),QPoint(800,600)));

}


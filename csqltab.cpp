#include "csqltab.h"
#include "cpsqldatabase.h"

CSQLTab::CSQLTab(CModel * model, QWidget *parent) : QWidget(parent)
{
    this->model = model;
    commandLine = new QLineEdit(this);
    execCommB = new QPushButton("исполнить",this);
    result = new QLabel(this);


    connect(execCommB,SIGNAL(released()),this,SLOT(ExecCommand()));


    QGridLayout * glay = new QGridLayout(this);
    glay->addWidget(commandLine,0,0);
    glay->addWidget(execCommB,0,1);
    glay->addWidget(result);
}

void CSQLTab::ExecCommand()
{
    CPSQLDatabase * conn = model->GetConnectionTool();
    conn->ExecCommand(commandLine->text().toStdString());
    commandLine->clear();
}

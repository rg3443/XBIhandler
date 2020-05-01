#include "cconnectdb.h"

CConnectDb::CConnectDb(CModel * model,QWidget *parent) : QWidget(parent)
{
    this->model = model;
    connectionStatus = "Отсутствует";
    QPushButton * applySettings = new QPushButton("Соединиться",this);
    QPushButton * deffaultConnection = new QPushButton("Deffault connection",this);


    editFieldss[0] = new QLineEdit(this);
    editFieldss[1] = new QLineEdit(this); editFieldss[1]->setEchoMode(QLineEdit::Password);
    editFieldss[2] = new QLineEdit(this);
    editFieldss[3] = new QLineEdit(this);
    editFieldss[4] = new QLineEdit(this);


    QLabel *editFields[EDITLINE_AMMOUNT];
    editFields[0] = new QLabel("Логин");
    editFields[1] = new QLabel("Пароль");
    editFields[2] = new QLabel("Имя БД");
    editFields[3] = new QLabel("Адрес");
    editFields[4] = new QLabel("Порт");
    QLabel *connectionStatusText = new QLabel("Статус соединения");
    connS = new QLabel(connectionStatus);


    connect(applySettings,SIGNAL(released()),this,SLOT(ApplyConnect()));
    connect(deffaultConnection,SIGNAL(released()),this,SLOT(DeffaultConnection()));


    layout = new QGridLayout(this);
    for (int i=0;i<EDITLINE_AMMOUNT;i++) {
        layout->addWidget(editFields[i],i,0);
        layout->addWidget(editFieldss[i],i,1);
    }
    layout->addWidget(applySettings,EDITLINE_AMMOUNT,2);
    layout->addWidget(deffaultConnection,EDITLINE_AMMOUNT+1,2);
    layout->addWidget(connectionStatusText,EDITLINE_AMMOUNT+2,0);
    layout->addWidget(connS,EDITLINE_AMMOUNT+2,1);
}

void CConnectDb::ApplyConnect()
{
    connectionTool.Connect( editFieldss[0]->text().toStdString(),
                            editFieldss[1]->text().toStdString(),
                            editFieldss[2]->text().toStdString(),
                            editFieldss[3]->text().toStdString(),
                            editFieldss[4]->text().toStdString()
            );
    if(connectionTool.IsConnect()) {
        connectionStatus = "Присутствует";
    }
    connS->setText(connectionStatus);
    model->LoadConnectionTool(&connectionTool);
}

void CConnectDb::DeffaultConnection()
{
    connectionTool.Connect("postgres","[eqdgbplt1337","postgres","127.0.0.1","5432");
    if(connectionTool.IsConnect()) {
        connectionStatus = "Присутствует";
    }
    connS->setText(connectionStatus);
    model->LoadConnectionTool(&connectionTool);
}

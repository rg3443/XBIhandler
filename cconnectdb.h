#ifndef CCONNECTDB_H
#define CCONNECTDB_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QPair>

#include "cpsqldatabase.h"
#include "cmodel.h"

const int EDITLINE_AMMOUNT = 5;
class CConnectDb : public QWidget {
Q_OBJECT
public:
    explicit CConnectDb(CModel * model,QWidget *parent = nullptr);
    QGridLayout* GetLayout() { return layout; }
    CPSQLDatabase* GetConnectionTool() { return &connectionTool; }
private:
    QLineEdit *editFieldss[EDITLINE_AMMOUNT];
    QGridLayout * layout;
    QString login,password,dbname,addres,port;

    CPSQLDatabase connectionTool;
    QString connectionStatus;
    QLabel *connS;

    CModel * model;
private slots:
    void ApplyConnect();
    void DeffaultConnection();
signals:
};

#endif // CCONNECTDB_H

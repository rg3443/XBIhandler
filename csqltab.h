#ifndef CSQLTAB_H
#define CSQLTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "cmodel.h"

class CSQLTab : public QWidget {
Q_OBJECT
public:
    explicit CSQLTab(CModel * model, QWidget *parent = nullptr);

private:
    QPushButton * execCommB;
    QLineEdit * commandLine;
    QLabel * result;
    CModel * model;
private slots:
    void ExecCommand();


signals:

};

#endif // CSQLTAB_H

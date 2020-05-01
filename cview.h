#ifndef CVIEW_H
#define CVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>

#include "cmodel.h"
#include "cmaintab.h"
#include "cconnectdb.h"
#include "csqltab.h"

class CView : public QWidget {
Q_OBJECT
public:
    explicit CView(CModel * model, QWidget *parent = nullptr);
private:

    CModel * model;
    CMainTab * mainWindow;
    CConnectDb * dbWindow;
    CSQLTab * sqlComWindow;
signals:




};

#endif // CVIEW_H

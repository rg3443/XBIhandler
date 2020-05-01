#ifndef CMAINTAB_H
#define CMAINTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QSpinBox>

#include "cmodel.h"
#include "cconnectdb.h"

class CMainTab : public QWidget {
Q_OBJECT
public:
    explicit CMainTab(CModel * model, QWidget *parent = nullptr);
private:
    QGridLayout * slayout;
    QComboBox * fileList,*chainList;
    QTableWidget * tableView[2];
    QLineEdit * newFileName, * newChainName;
    QSpinBox * toDeleteRowId;
    //QVector<QPushButton*> buttonsList;
    CModel * model;

signals:

private slots:
    void NewFile(); //выбор имени->выбор директории
    void OpenFile();
    void OpenChain();
    void AddChain();
    void DeleteFile();
    void OpenDirectory(); // выбирает дир где брать файлы
    void OpenFiles();
    void AddObjectInToChain();
    void SaveChainTable();// SAVE ALL XBI FILE
    void DeleteRowInCurrentChain();
    void QuitProg();
};

#endif // CMAINTAB_H

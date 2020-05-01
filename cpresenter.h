#ifndef CPRESENTER_H
#define CPRESENTER_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;

#include "cmodel.h"
#include "cview.h"

class CPresenter : public QMainWindow {
Q_OBJECT
public:
    explicit CPresenter(QWidget *parent = nullptr);
    void Init();
    void Run();
private:
    CModel model;
    CView * view;
signals:

};

#endif // CPRESENTER_H

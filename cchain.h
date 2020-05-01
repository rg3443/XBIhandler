#ifndef CCHAIN_H
#define CCHAIN_H

#include <vector>
#include <string>
#include <stdio.h>
using namespace std;
#include <QString>
#include <QTableWidget>

struct SField {
    //row
    string name;
    int roditel;
    int fieldSize;
    string description;
    SField() {}
    SField(QString name_,QString rodit,QString fsize,QString desc) {
        name = name_.toStdString();
        roditel = rodit.toInt();
        fieldSize = fsize.toInt();
        description = desc.toStdString();
    }

};

class CChain {
public:
    CChain();
    CChain(string name) { this->name = name; }
    void Init();
    void AddField(SField newField);
    void EraseField(int id);
    SField* GetField(int id);
    string GetItem(int row,int column);
    void SetItem(QString val, int row, int column);
    string GetName() { return name; }

    int ColumnSize() { return 4; }
    int RowSize() { return fieldList.size(); }
    int GetColumnLineSize() { fieldList.size(); }

    void AddColumnName(string name) { columnNames.push_back(name); }
    string GetColumnName(int id) { return columnNames[id]; }

    void LoadTable(QTableWidget * table);
    void Clear();
private:
    string name;
    vector<string> columnNames;
    vector<SField> fieldList;

};

#endif // CCHAIN_H

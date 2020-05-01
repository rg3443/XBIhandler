#include "cchain.h"
#include <iostream>

CChain::CChain()
{

}

void CChain::Init()
{

}

void CChain::AddField(SField newField)
{
    fieldList.push_back( newField );
    std::cout << "field list size is " << fieldList.size() << endl;
}

void CChain::EraseField(int id)
{
    if(id > 0 || id < fieldList.size()) {
        fieldList.erase( fieldList.begin() + id );
    }
}

SField* CChain::GetField(int id)
{
    if(id > 0 || id < fieldList.size()) {
        return &fieldList[id];
    }
}

string CChain::GetItem(int row, int column)
{
    switch (column) {
    case 0://имя
        return fieldList[row].name;
    break;
    case 1://родитель
        return to_string(fieldList[row].roditel);
    break;
    case 2://колво полей
        return to_string(fieldList[row].fieldSize);
    break;
    case 3://описание
        return fieldList[row].description;
    break;
    }
}

void CChain::SetItem(QString val, int row, int column)
{
    switch (column) {
    case 0://имя
         fieldList[row].name = val.toStdString();
    break;
    case 1://родитель
        if(val == 'f')
            fieldList[row].roditel = 0;
        else if(val == 't')
            fieldList[row].roditel = 1;
        else
            fieldList[row].roditel = val.toInt();
        break;
    case 2://колво полей
         fieldList[row].fieldSize = val.toInt();
    break;
    case 3://описание
         fieldList[row].description = val.toStdString();
    break;
    }
}

void CChain::LoadTable(QTableWidget *table)
{
    fieldList.resize(0);
    for(int row=0;row<table->rowCount();row++) {
        fieldList.push_back(SField());
        for(int column=0;column<table->columnCount();column++) {
            this->SetItem(table->item(row,column)->text(),row,column);
        }
    }
}

void CChain::Clear()
{
    fieldList.resize(0);
}

#include "xbifile.h"
#include <QDebug>

XBIfile::XBIfile()
{

}

void XBIfile::Init(string name, string path)
{
    this->name = name;
     this->path = path;
}

void XBIfile::AddChain(string chainName)
{
    chainList.push_back(CChain(chainName));
}

CChain* XBIfile::GetChain(int id)
{
    return &chainList[id];
}

QStringList XBIfile::GetChainNames()
{
    QStringList list;
    for(int i=0;i<chainList.size();++i)
    {
        list.push_back(QString(chainList[i].GetName().c_str()));
        qDebug() << "узел №" << i << " =" <<  list[i] << endl;
    }
    return list;
}

CChain* XBIfile::GetNewChain(string name)
{
    chainList.push_back(CChain(name));
    return &chainList[chainList.size()-1];
}

void XBIfile::_ConsoleShow()
{
    qDebug() << "concole show" << endl;
    for(int chain=0;chain<chainList.size();chain++) {
      qDebug() << this->GetChain(chain)->GetName().c_str() << endl;
    for(int row=0;row<chainList[chain].RowSize();row++)
    {
        for(int column=0;column<4;column++)
        {
            qDebug() << " row" << row << "|column" << column << "|" << chainList[chain].GetItem(row,column).c_str() << "|";
        }
        //qDebug() << endl;
    }}
}

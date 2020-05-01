#ifndef XBIFILE_H
#define XBIFILE_H

#include <vector>
#include <string>
#include <stdio.h>
using namespace std;
#include "cchain.h"
//#include "FileSys/cfilesystem.h"

class XBIfile {
public:
    XBIfile();
    void Init( string name, string path );
    void AddChain( string chainName );
    CChain* GetChain(int id);
    CChain* GetNewChain(string name);

    string GetPath() { return path; }
    string GetName() { return name; }
    int GetChainSize() { return chainList.size(); }
    QStringList GetChainNames();

    void SetName(string name) { this->name = name; }
    void SetPath(string path) { this->path = path; }

    void _ConsoleShow();
private:
    string name,path;
    vector<CChain> chainList;
  //  CFileSystem fileStream;

};

#endif // XBIFILE_H

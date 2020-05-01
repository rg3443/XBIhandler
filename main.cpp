/*

 * Demo of libpq.

 * Build: g++ libpq-demo.cc -o libpq-demo -lpq

 * Run: ./libpq-demo

 */



//#include <arpa/inet.h>
#include <QApplication>
#include <iostream>
#include <libpq-fe.h>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "cpsqldatabase.h"
#include "mainwindow.h"
#include "cpresenter.h"
#include "FileSys/cfilesystem.h"
#include "FileSys/ctablesaver.h"
#include <QByteArray>
#include "xbifile.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    CPSQLDatabase db;
/*
    CXBISaver saver;
    QString filePath = "C:/c++/TESTFORTZPROG/vZnachinPizdec.xbi";
    XBIfile test = saver.LoadFile3(filePath);
    saver.SaveFile3(&test,"C:/c++/TESTFORTZPROG/real2.xbi");
    test._ConsoleShow();
    */
//

   // db.Connect("postgres","[eqdgbplt1337","postgres","127.0.0.1","5432");
    //db.SelectFromTable("heh");
  //  MainWindow app;
   // app.show();
    CPresenter prog;
    prog.Init();
    prog.Run();
    return a.exec();

}

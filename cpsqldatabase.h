#ifndef CPSQLDATABASE_H
#define CPSQLDATABASE_H

#include <QObject>
#include <QString>
#include <iostream>
#include <libpq-fe.h>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <QSqlDatabase>
#include <QTableWidget>
using namespace std;

inline char *myhton(char *src, int size) {
  char *dest = (char *)malloc(sizeof(char) * size);
  switch (size) {
  case 1:
    *dest = *src;
    break;
  case 2:
    //*(uint16_t *)dest = htobe16(*(uint16_t *)src);
    break;
  case 4:
    //*(uint32_t *)dest = htobe32(*(uint32_t *)src);
    break;
  case 8:
    //*(uint64_t *)dest = htobe64(*(uint64_t *)src);
    break;
  default:
    *dest = *src;
    break;
  }
  memcpy(src, dest, size);
  free(dest);
  return src;
}

inline void printPGresult(PGresult *res) {
  std::cout << PQntuples(res) << "tuples, " << PQnfields(res) << " fields" << std::endl;
  // print column name
  for (int i = 0; i < PQnfields(res); i++) {
    std::cout << PQfname(res, i) << "\t";
  }
  std::cout << std::endl;
  // print column values
  for (int i = 0; i < PQntuples(res); i++) {
    for (int j = 0; j < PQnfields(res); j++) {
      std::cout << PQgetvalue(res, i, j) << "\t";
    }
    std::cout << std::endl;
  }
}

class CPSQLDatabase {
public:
     CPSQLDatabase( );
    int Test();
    void Connect(string user,string password, string dbname, string hostdir, string port);
    void ExecCommand(string command);
    void SelectFromTable(string tableName);

    string GetData(int x,int y);
    void EditData(QString newData,QString chainName,QString columnName, QString rowName);
    void EditTable(QTableWidget * table,QString tableName);

    string TableConsoleShow(string tableName);

    bool IsConnect();

    int GetRowAmmount();
    int GetColumnsAmmount();


    string GetUser() { return user; }
    string GetDbName() { return dbname; }
    string GetAddres() { return hostdir; }
    string GetPort() { return port; }
private:
    PGconn * conn;
    PGresult * res;
    string user,password,dbname,hostdir,port;
    QSqlDatabase *db;
};

#endif // CPSQLDATABASE_H

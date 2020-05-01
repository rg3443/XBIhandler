#include "cpsqldatabase.h"
#include <QVariant>

CPSQLDatabase::CPSQLDatabase( )
{

}

void CPSQLDatabase::Connect(string user, string password, string dbname, string hostdir, string port)
{
    this->user = user.c_str();
    this->password = password.c_str();
    this->dbname = dbname.c_str();
    this->port = port.c_str();
    string connInfo = "user="+user+" password="+password+" dbname="+dbname+" hostaddr="+hostdir+" port="+port;
    //const char connInfoBuf[] = connInfo.c_str();
    conn = PQconnectdb(connInfo.c_str());
    if(PQstatus(conn) != CONNECTION_OK) {
        cout << "Connection to db failed: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return;
    } else {
        cout << "Connection to db succeed" << endl;
    }
    res = NULL;
}

void CPSQLDatabase::ExecCommand(string command)
{
    res = PQexec(conn,command.c_str());
    if(PQresultStatus(res) != PGRES_COMMAND_OK) {
        cout << "Command Exec is failed: " << PQresultErrorMessage(res) << endl;
        PQclear(res);
        return;
    }
}

void CPSQLDatabase::SelectFromTable(string tableName)
{
    res = PQexec(conn, "use postgres;");
    PQclear(res);
    string command = "select * from " + tableName + ";";
    res = PQexec(conn, command.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cout << "Select failed: " << PQresultErrorMessage(res) << std::endl;
    }
}

string CPSQLDatabase::GetData(int x, int y)
{
    return QString(PQgetvalue(res,y,x)).toStdString(); // ...
}

void CPSQLDatabase::EditData(QString newData,QString chainName,QString columnName, QString rowName)
{
    //QString command = "update "+chainName+" set "+columnName+" = '"+newData+"' where Имя = '"+rowName+"';";
    QString command = "update heh set Описание = 'dsds' where Имя = 'd';";
    this->ExecCommand(command.toStdString());
}

void CPSQLDatabase::EditTable(QTableWidget *table,QString tableName)
{
    string command1 = "drop table " + tableName.toStdString() + ";";
    string command2 = "create table " + tableName.toStdString() + "(Имя text,Родитель boolean, Размер_поля integer, Описание text);";
    this->ExecCommand(command1);
    this->ExecCommand(command2);
    for(int i=0;i<table->rowCount();i++) {
        string tileData0 = table->item(i,0)->text().toStdString();
        string tileData1 = table->item(i,1)->text().toStdString();
        string tileData2 = table->item(i,2)->text().toStdString();
        string tileData3 = table->item(i,3)->text().toStdString();
        if(tileData1 == "1") tileData1 = "true";
        else if(tileData1 == "0") tileData1 = "false";
            string insertCommand = "insert into " + tableName.toStdString() + " values('"+tileData0+"',"+tileData1+","+tileData2+",'"+tileData3+"');";

            this->ExecCommand(insertCommand);
    }
}

int CPSQLDatabase::GetColumnsAmmount()
{
    return PQnfields(res);
}


int CPSQLDatabase::GetRowAmmount()
{
    return PQntuples(res);
}

string CPSQLDatabase::TableConsoleShow(string tableName)
{
    string command = "select id from public." + tableName;
    res = PQexec(conn,command.c_str());
    if(PQresultStatus(res) != PGRES_TUPLES_OK) {
        cout << "Console Show failed: " << PQresultErrorMessage(res) << endl;
    } else {
        cout << "Get " << PQntuples(res) << " tuples, each tuple has " << PQnfields(res) << " fields" << endl;
        for(int  i=0; i<PQnfields(res); i++)
        {
            cout << PQfname(res,i) << "     ";
        }
        cout << endl;
    }
    for(int i=0; i<PQntuples(res); i++)
    {
        for(int j=0; j<PQnfields(res); j++)
        {
            cout << PQgetvalue(res,i,j) << "     ";
        }
        cout << endl;
    }
    //PQclear(res);
}

bool CPSQLDatabase::IsConnect()
{
    if(PQstatus(conn) != CONNECTION_OK)
        return false;
    else
        return true;
}



///////////////////////////////////////////////////////////////////////////

int CPSQLDatabase::Test()
{

    const char conninfo[] =
        "user=postgres password=[eqdgbplt1337 dbname=postgres hostaddr=127.0.0.1 port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK) {
      std::cout << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
      PQfinish(conn);
      return 1;
    } else {
      std::cout << "Connection to database succeed." << std::endl;
    }
    PGresult *res = NULL;

    /* create table demo */
    res = PQexec(conn, "create table if not exists t(id int, name text);");

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cout << "Create table failed: " << PQresultErrorMessage(res) << std::endl;
      PQclear(res);
      return 1;
    }
    PQclear(res);

    /* INSERT demo */
    res = PQexec(conn,"insert into t values(1, 'hello'), (2, 'world'),(3, '....');");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cout << "Insert into table failed: " << PQresultErrorMessage(res) << std::endl;
    }
    PQclear(res);

    /* UPDATE demo */
    res = PQexec(conn, "update t set id = 0 where id = 1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cout << "upate failed: " << PQresultErrorMessage(res) << std::endl;
    } else {
      std::cout << "Update counts: " << PQcmdTuples(res) << std::endl;
    }
    PQclear(res);


    const char command[] = "insert into t values($1, $2);";
    char cid[] = "10";
    char name[20] = "helloworld2";
    int nParams = 2;
    const char *const paramValues[] = {cid, name};
    const int paramLengths[] = {sizeof(cid), sizeof(name)};
    const int paramFormats[] = {0, 0};
    int resultFormat = 0;

    /* PQexecParams demo */
    res = PQexecParams(conn, command, nParams, NULL, paramValues, paramLengths,paramFormats, resultFormat);
   // if (PQresultStatus(res) != PGRES_COMMAND_OK) { << std::endl;
  //
   // }
    PQclear(res);

    /* PREPARE INSERT demo */
    res = PQprepare(conn, "insertStmt", command, nParams, NULL);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cout << "PQprepare failed:" << PQresultErrorMessage(res) << std::endl;
      PQclear(res);
    } else {
      PQclear(res);
      res = PQexecPrepared(conn, "insertStmt", nParams, paramValues, paramLengths,paramFormats, resultFormat);
      if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cout << "PQexecPrepared failed: " << PQresultErrorMessage(res) << std::endl;
      }
      PQclear(res);
    }

    /* SELECT demo */
    res = PQexec(conn, "select * from t;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cout << "Select failed: " << PQresultErrorMessage(res) << std::endl;
    } else {
      std::cout << "Get " << PQntuples(res) << "tuples, each tuple has " << PQnfields(res) << "fields" << std::endl;
      // print column name
      for (int i = 0; i < PQnfields(res); i++) {
        std::cout << PQfname(res, i) << "              ";
      }
      std::cout << std::endl;

      // print column values
      for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
          std::cout << PQgetvalue(res, i, j) << "   ";
        }
        std::cout << std::endl;
      }
    }
    PQclear(res);


    /* Binary COPY demo */
    char header[12] = "PGCOPY\n\377\r\n\0";
    int flag = 0;
    int extension = 0;
    char buffer[100];
    memcpy(buffer, header, 11);
    memcpy(&buffer[11], (void *)&flag, 4);
    memcpy(&buffer[15], (void *)&extension, 4);
    short fieldnum = 2;
    memcpy(&buffer[19], myhton((char *)&fieldnum, 2), 2);
    int size = 4;
    memcpy(&buffer[21], myhton((char *)&size, 4), 4);
    int id = 10;
    memcpy(&buffer[25], (void *)&id, 4);
    size = 10;
    memcpy(&buffer[29], myhton((char *)&size, 4), 4);
    memcpy(&buffer[33], "bbbbbccccc", 10);
    short negative = -1;
    memcpy(&buffer[43], myhton((char *)&negative, 2), 2);


    res = PQexec(conn, "COPY t FROM STDIN (FORMAT binary);");
    if (PQresultStatus(res) != PGRES_COPY_IN) {
      cout << "Not in COPY_IN mode";
      PQclear(res);
    } else {
      PQclear(res);
      cout << "Enter COPY_IN mode" << endl;
      int copyRes = PQputCopyData(conn, buffer, 45);
      if (copyRes == 1) {
        if (PQputCopyEnd(conn, NULL) == 1) {
          res = PQgetResult(conn);
          if (PQresultStatus(res) == PGRES_COMMAND_OK) {
            cout << "Insert a record successfully" << endl;
          } else {
            cout << PQerrorMessage(conn) << endl;
          }
          PQclear(res);
        } else {
          cout << PQerrorMessage(conn) << endl;
        }
      } else if (copyRes == 0) {
        cout << "Send no data, connection is in nonblocking mode" << endl;
      } else if (copyRes == -1) {
        cout << "Error occur: " << PQerrorMessage(conn) << endl;
      }
    }

    /* Text format COPY demo */
    res = PQexec(conn, "COPY t FROM STDIN with(delimiter ',');");
    if (PQresultStatus(res) != PGRES_COPY_IN) {
      cout << "Not in COPY_IN mode";
      PQclear(res);
    } else {
      PQclear(res);
      cout << "Enter COPY_IN mode" << endl;
      string str("1,luo haha\n");
      if (PQputCopyData(conn, str.c_str(), str.length()) == 1) {
        if (PQputCopyEnd(conn, NULL) == 1) {
          res = PQgetResult(conn);
          if (PQresultStatus(res) == PGRES_COMMAND_OK) {
            cout << "Copy " << PQcmdTuples(res) << endl;
          } else {
            cout << PQresultErrorMessage(res) << endl;
          }
          printPGresult(res);
          PQclear(res);
        } else {
          cout << PQerrorMessage(conn) << endl;
        }
      } else {
        cout << PQerrorMessage(conn) << endl;
      }
    }

    res = PQexec(conn, "drop table t;");
    PQclear(res);

    /* PQbackendPID demo */
    int pid = PQbackendPID(conn);
    if (pid == 0)
      cout << "Can't get conections's backend PID" << endl;
    else {
      // 当前连接调用pg_terminate_backend(pid)总是返回PGRES_FATAL_ERROR
      // 要用别的连接调用该函数，使用新连接的pid来终结这个connection
      stringstream ss;
      ss << "select pg_cancel_backend(" << pid << ")";
      PGresult *res = PQexec(conn, ss.str().c_str());
      ExecStatusType est = PQresultStatus(res);
      cout << PQresStatus(est) << endl;
      cout << PQresultErrorMessage(res);
      PQclear(res);
    }
    PQfinish(conn);
    return 1337;
}

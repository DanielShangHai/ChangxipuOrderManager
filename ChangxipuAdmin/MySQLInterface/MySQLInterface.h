#pragma once


#include <winsock.h>
#include "mysql.h"

#include "mutex.h"
#include <string> 
using namespace std;

class MySQLInterface
{


private:
	MySQLInterface();
	virtual ~MySQLInterface();
	MySQLInterface(MySQLInterface const&);
	MySQLInterface const& operator=(MySQLInterface const&);

    MYSQL   m_mysql;    
    mutable Mutex m_mutex;
	bool    m_dbConnected;

    string  m_sUser;
	string  m_sPassword;
	string  m_sHost;
	string  m_sDbName;
    int     m_iPort; 
	string  m_sCharaSet;

public:
	// Singleton
	static MySQLInterface* instance();
	bool initialize();
	bool connect();
    bool isConnected();
    bool UpdateInsertData(const string &Sql); 
   // bool DataQuery(const string &Sql,MYSQL_RES* sql_result,int *num);
	MYSQL_RES* DataQuery(const string &Sql,int *Field_num);
	void FreeQueryResult(MYSQL_RES* sql_result);
	MYSQL_ROW Fetch_Query_Row(MYSQL_RES* sql_result);
};

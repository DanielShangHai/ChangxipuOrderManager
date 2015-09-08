#include "MySQLInterface.h"
#include "automutex.h"



MySQLInterface* MySQLInterface::instance()
{
	static MySQLInterface fm;
	return(&fm);
}


MySQLInterface::MySQLInterface()
{
	/*
	m_sUser = "root";
	m_sPassword = "";
	m_sHost = "localhost";
	m_sDbName = "changxipu";
	m_iPort = 3306; 
	m_sCharaSet = "SET NAMES GBK";
	m_dbConnected = false;
*/

	m_sUser = "iniroot01";
	m_sPassword = "shenhuafc";
	m_sHost = "mysql56.rdsmcu90c4kacmw.rds.bj.baidubce.com";
	m_sDbName = "changxipu_db01";
	m_iPort = 3306; 
	m_sCharaSet = "SET NAMES GBK";
	m_dbConnected = false;


}


MySQLInterface::~MySQLInterface()
{
  mysql_close(&m_mysql);
}


bool MySQLInterface::initialize()
{

  AutoMutex locker(m_mutex);
  mysql_init(&m_mysql);

  return 0;
}

bool MySQLInterface::connect()
{
   if (isConnected())
   {
	   return true;
   }
   else
   {
	   AutoMutex locker(m_mutex);
       if (!mysql_real_connect(&m_mysql, m_sHost.c_str(),m_sUser.c_str(), m_sPassword.c_str(), m_sDbName.c_str(), m_iPort, NULL, 0)) {
		   return false;
	   }
	   m_dbConnected = true;
	   mysql_query(&m_mysql, m_sCharaSet.c_str());
   }
   return true;

}

bool MySQLInterface::isConnected()
{
	return m_dbConnected;
}

bool MySQLInterface::UpdateInsertData(const string &Sql)
{
   AutoMutex locker(m_mutex);
   if (isConnected())
   {
		    int r =  mysql_real_query(&m_mysql,Sql.c_str(),Sql.length());
			return r==0? true:false;
   }
   else
   {
       return false;  
   }
   return true;
}


MYSQL_RES* MySQLInterface::DataQuery(const string &Sql,int *Field_num)
{
   AutoMutex locker(m_mutex);
   if (isConnected())
   {
	   //int r =  mysql_real_query(&m_mysql,Sql.c_str(),Sql.length());
	   //mysql_query
	   int r =  mysql_query(&m_mysql,Sql.c_str());
	   if (r!=0)
	   {
		   return false;
	   }
       MYSQL_RES *sql_result = mysql_store_result(&m_mysql);
      // *Field_num = mysql_num_rows(sql_result);
	   *Field_num = mysql_num_fields(sql_result);
	   return sql_result;
   }
   else
   {
	   return NULL;  
   }
   return NULL;  


}


void MySQLInterface::FreeQueryResult(MYSQL_RES* sql_result)
{
    //AutoMutex locker(m_mutex);
	if (sql_result!=NULL)
	{
		mysql_free_result(sql_result);
	}
}

MYSQL_ROW MySQLInterface::Fetch_Query_Row(MYSQL_RES* sql_result)
{
	if (sql_result!=NULL)
	{
		return mysql_fetch_row(sql_result);
	}
	return NULL;

}
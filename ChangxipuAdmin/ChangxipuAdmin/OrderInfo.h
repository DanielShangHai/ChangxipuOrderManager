#ifndef   _ORDER_INFO_H
#define   _ORDER_INFO_H

#include <winsock.h>
#include "mysql.h"



class OrderInfo
{
public:
	OrderInfo(void);
	~OrderInfo(void);

	time_t getOrderTime();
    void FillDataFromSQLRow(MYSQL_ROW r_row,int Field_Num);


public:
	CString m_no;
	CString m_tel;
	CString m_name;
	CString m_address;
	CString m_smallbag;
	CString m_bigBag;
	CString m_getClothtime;
	CString m_openid;
	CString m_ordertime;
	CString m_orderID;
	CString m_orderStatus;
	CString m_AssesPoint;
	CString m_MainAddressID;
	CString m_SubAreaID;
	CString m_DetailAddressID;
	CString m_AddressName;
	CString m_PayMoney;
	CString m_OrderType;
	CString m_discount;
	bool datafilled;





};













#endif  //_ORDER_INFO_H
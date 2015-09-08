#include "StdAfx.h"
#include "OrderInfo.h"




OrderInfo::OrderInfo(void)
{
	 m_no = _T("");
	 m_tel = _T("");
	 m_name = _T("");
	 m_address =_T("");
	 m_smallbag = _T("");
	 m_bigBag =_T("");
	 m_getClothtime = _T("");
	 m_openid = _T("");
	 m_ordertime = _T("");
	 m_orderID = _T("");
	 m_orderStatus = _T("");
	 m_AssesPoint = _T("");
	 m_MainAddressID = _T("");
	 m_SubAreaID = _T("");
	 m_DetailAddressID = _T("");
	 m_AddressName = _T("");
	 m_PayMoney = _T("");
	 m_OrderType = _T("");
	 m_discount = _T("");
	 datafilled = false;
}

OrderInfo::~OrderInfo(void)
{
}


void OrderInfo::FillDataFromSQLRow(MYSQL_ROW r_row,int Field_Num)
{
	char temp[256];
	int i = 0;

	if(r_row!=NULL)
	{
		
	   m_no += r_row[0];
	   m_tel += r_row[1];
	   m_name += r_row[2];
	   m_address += r_row[3];
	   m_smallbag += r_row[4];
	   m_bigBag += r_row[5];
	   m_getClothtime += r_row[6];
	   m_openid += r_row[7];
	   m_ordertime += r_row[8];
	   m_orderID += r_row[9];
	   m_orderStatus += r_row[10];
	   m_AssesPoint += r_row[11];
	   m_MainAddressID += r_row[12];
	   m_SubAreaID += r_row[13];
	   m_DetailAddressID += r_row[14];
	   m_AddressName += r_row[15];
	   m_PayMoney += r_row[16];
	   m_OrderType += r_row[17];
	   m_discount += r_row[18];

	   datafilled = true;
	}

}


time_t OrderInfo::getOrderTime()
{
	unsigned long timeTemp;
    if (datafilled)
    {
		//t timeTemp = _wtol(m_ordertime.GetBuffer());
		timeTemp = atol(m_ordertime.GetBuffer());
		m_ordertime.ReleaseBuffer();
    }
	else
	{
		timeTemp = 0;
	}

	time_t ret = (time_t)timeTemp;
	return ret;
}
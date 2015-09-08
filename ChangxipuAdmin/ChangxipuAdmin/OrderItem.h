#pragma once

class COrderItem
{
public:
	COrderItem(void);
	~COrderItem(void);
public:
    CString orderID;
	CString orderTel;
	CString orderStatus;
    CString orderType;
	float  orderPayed;
	float  orderDiscount;
    int    orderBig;
	int    orderSmall;
	CString orderName;

    int iIndex;
};

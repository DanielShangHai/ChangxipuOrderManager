#pragma once

#include <vector>
using namespace std;


typedef struct OrderClothesDetails
{
	CString clothes_type;
	CString clothes_color;
	CString clothes_Num;
	CString clothes_OtherInfo;

}OrderClothesDetail_Item;

class OrderClothes
{
public:
	OrderClothes(void);
	~OrderClothes(void);

public:
	CString orderID;
	CString orderTel;
	CString confirmMessage;
	CString receiveMessage;
	CString totalClothes;
	CString detail_infoNum;
	CString otherInfos;

    typedef vector<OrderClothesDetail_Item>  OrderClothesVec;

    OrderClothesVec m_ClothesDetail;


};

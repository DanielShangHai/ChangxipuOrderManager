
#include <windows.h>
#include <string>

using namespace std;


char* QXUtf82Unicode(const char* utf, size_t *unicode_number)
{
	if(!utf || !strlen(utf))
	{
		*unicode_number = 0;
		return NULL;
	}
	int dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,utf,-1,NULL,0);
	size_t num = dwUnicodeLen*sizeof(wchar_t);
	wchar_t *pwText = (wchar_t*)malloc(num);
	memset(pwText,0,num);
	MultiByteToWideChar(CP_UTF8,0,utf,-1,pwText,dwUnicodeLen);
	*unicode_number = dwUnicodeLen - 1;
	return (char*)pwText;
}

char* QXUnicode2Utf8(const char* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, (const wchar_t*)unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (const wchar_t*)unicode, -1, szUtf8, len, NULL,NULL);
	return szUtf8;
}




/************************************************************************************************* 
 * 将UTF8编码转换成Unicode（UCS-2）编码 
 * 参数： 
 *    char* pInput  指向输入字符串（以'/0'结尾）的指针  
 *    char** ppOutput 指向输出字符串指针的指针 
 * 返回值： 
 *    返回转换后的Unicode字符串的字节数，如果出错则返回-1 
 * 注意： 
 *     1. UTF8没有字节序问题，但是Unicode字符有字节序， 
 *        字节序分为大端（Big Endian）和小端（Little Endian）两种， 
 *        在Intel处理器中采用小端法表示，因此本例中采用小端法表示。（低地址存低位） 
 *     2. 在调用本函数后需要手动释放 *ppOutput 指向的内存，否则将会造成内存泄漏。 
 **************************************************************************************************/  
int utf8_to_unicode(char* pInput, char** ppOutput)  
{  
    int outputSize = 0; //记录转换后的Unicode字符串的字节数  
    *ppOutput = (char *)malloc(strlen(pInput) * 2);  //为输出字符串分配足够大的内存空间  
    memset(*ppOutput, 0, strlen(pInput) * 2);  
    char *tmp = *ppOutput; //临时变量，用于遍历输出字符串  
   
    while (*pInput)  
    {  
        if (*pInput > 0x00 && *pInput <= 0x7F) //处理单字节UTF8字符（英文字母、数字）  
        {  
            *tmp = *pInput;  
            tmp++;  
            *tmp = 0; //小端法表示，在高地址填补0  
        }  
        else if (((*pInput) & 0xE0) == 0xC0) //处理双字节UTF8字符  
        {  
            char high = *pInput;  
            pInput++;  
            char low = *pInput;  
            if ((low & 0xC0) != 0x80)  //检查是否为合法的UTF8字符表示  
            {  
                return -1; //如果不是则报错  
            }  
     
            *tmp = (high << 6) + (low & 0x3F);  
            tmp++;  
            *tmp = (high >> 2) & 0x07;  
        }  
        else if (((*pInput) & 0xF0) == 0xE0) //处理三字节UTF8字符  
        {  
            char high = *pInput;  
            pInput++;  
            char middle = *pInput;  
            pInput++;  
            char low = *pInput;  
            if (((middle & 0xC0) != 0x80) || ((low & 0xC0) != 0x80))  
            {  
                return -1;  
            }  
            *tmp = (middle << 6) + (low & 0x7F);  
            tmp++;  
            *tmp = (high << 4) + ((middle >> 2) & 0x0F);   
        }  
        else //对于其他字节数的UTF8字符不进行处理  
        {  
            return -1;  
        }  
        pInput ++;  
        tmp ++;  
        outputSize += 2;  
    }  
    *tmp = 0;  
    tmp++;  
    *tmp = 0;  
    return outputSize;  
}  


// 注释：多字节包括GBK和UTF-8  
int GBK2UTF8(char *szGbk,char *szUtf8,int Len)  
{  
	// 先将多字节GBK（CP_ACP或ANSI）转换成宽字符UTF-16  
	// 得到转换后，所需要的内存字符数  
	int n = MultiByteToWideChar(CP_ACP,0,szGbk,-1,NULL,0);  
	// 字符数乘以 sizeof(WCHAR) 得到字节数  
	WCHAR *str1 = new WCHAR[sizeof(WCHAR) * n];  
	// 转换  
	MultiByteToWideChar(CP_ACP,  // MultiByte的代码页Code Page  
		0,            //附加标志，与音标有关  
		szGbk,        // 输入的GBK字符串  
		-1,           // 输入字符串长度，-1表示由函数内部计算  
		str1,         // 输出  
		n             // 输出所需分配的内存  
		);  

	// 再将宽字符（UTF-16）转换多字节（UTF-8）  
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);  
	if (n > Len)  
	{  
		delete[]str1;  
		return -1;  
	}  
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, szUtf8, n, NULL, NULL);  
	delete[]str1;  
	str1 = NULL;  

	return 0;  
}  


//UTF-8 GBK  
int UTF82GBK(char *szUtf8,char *szGbk,int Len)  
{  
	int n = MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, NULL, 0);  
	WCHAR * wszGBK = new WCHAR[sizeof(WCHAR) * n];  
	memset(wszGBK, 0, sizeof(WCHAR) * n);  
	MultiByteToWideChar(CP_UTF8, 0,szUtf8,-1, wszGBK, n);  

	n = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
	if (n > Len)  
	{  
		delete[]wszGBK;  
		return -1;  
	}  

	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGbk, n, NULL, NULL);  

	delete[]wszGBK;  
	wszGBK = NULL;  

	return 0;  
}  






BOOL WStringToString(const std::wstring &wstr,std::string &str)
{    
   int nLen = (int)wstr.length();    
   str.resize(nLen,' ');
   int nResult = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wstr.c_str(),nLen,(LPSTR)str.c_str(),nLen,NULL,NULL);
   if (nResult == 0)
   {
      return FALSE;
   }
   return TRUE;
}
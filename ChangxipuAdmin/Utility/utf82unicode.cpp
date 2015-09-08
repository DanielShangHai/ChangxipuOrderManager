
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
 * ��UTF8����ת����Unicode��UCS-2������ 
 * ������ 
 *    char* pInput  ָ�������ַ�������'/0'��β����ָ��  
 *    char** ppOutput ָ������ַ���ָ���ָ�� 
 * ����ֵ�� 
 *    ����ת�����Unicode�ַ������ֽ�������������򷵻�-1 
 * ע�⣺ 
 *     1. UTF8û���ֽ������⣬����Unicode�ַ����ֽ��� 
 *        �ֽ����Ϊ��ˣ�Big Endian����С�ˣ�Little Endian�����֣� 
 *        ��Intel�������в���С�˷���ʾ����˱����в���С�˷���ʾ�����͵�ַ���λ�� 
 *     2. �ڵ��ñ���������Ҫ�ֶ��ͷ� *ppOutput ָ����ڴ棬���򽫻�����ڴ�й©�� 
 **************************************************************************************************/  
int utf8_to_unicode(char* pInput, char** ppOutput)  
{  
    int outputSize = 0; //��¼ת�����Unicode�ַ������ֽ���  
    *ppOutput = (char *)malloc(strlen(pInput) * 2);  //Ϊ����ַ��������㹻����ڴ�ռ�  
    memset(*ppOutput, 0, strlen(pInput) * 2);  
    char *tmp = *ppOutput; //��ʱ���������ڱ�������ַ���  
   
    while (*pInput)  
    {  
        if (*pInput > 0x00 && *pInput <= 0x7F) //�����ֽ�UTF8�ַ���Ӣ����ĸ�����֣�  
        {  
            *tmp = *pInput;  
            tmp++;  
            *tmp = 0; //С�˷���ʾ���ڸߵ�ַ�0  
        }  
        else if (((*pInput) & 0xE0) == 0xC0) //����˫�ֽ�UTF8�ַ�  
        {  
            char high = *pInput;  
            pInput++;  
            char low = *pInput;  
            if ((low & 0xC0) != 0x80)  //����Ƿ�Ϊ�Ϸ���UTF8�ַ���ʾ  
            {  
                return -1; //��������򱨴�  
            }  
     
            *tmp = (high << 6) + (low & 0x3F);  
            tmp++;  
            *tmp = (high >> 2) & 0x07;  
        }  
        else if (((*pInput) & 0xF0) == 0xE0) //�������ֽ�UTF8�ַ�  
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
        else //���������ֽ�����UTF8�ַ������д���  
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


// ע�ͣ����ֽڰ���GBK��UTF-8  
int GBK2UTF8(char *szGbk,char *szUtf8,int Len)  
{  
	// �Ƚ����ֽ�GBK��CP_ACP��ANSI��ת���ɿ��ַ�UTF-16  
	// �õ�ת��������Ҫ���ڴ��ַ���  
	int n = MultiByteToWideChar(CP_ACP,0,szGbk,-1,NULL,0);  
	// �ַ������� sizeof(WCHAR) �õ��ֽ���  
	WCHAR *str1 = new WCHAR[sizeof(WCHAR) * n];  
	// ת��  
	MultiByteToWideChar(CP_ACP,  // MultiByte�Ĵ���ҳCode Page  
		0,            //���ӱ�־���������й�  
		szGbk,        // �����GBK�ַ���  
		-1,           // �����ַ������ȣ�-1��ʾ�ɺ����ڲ�����  
		str1,         // ���  
		n             // ������������ڴ�  
		);  

	// �ٽ����ַ���UTF-16��ת�����ֽڣ�UTF-8��  
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
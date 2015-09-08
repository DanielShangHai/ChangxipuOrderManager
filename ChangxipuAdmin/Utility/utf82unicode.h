#include <string>
using namespace std;

char* QXUtf82Unicode(const char* utf, size_t *unicode_number);
char* QXUnicode2Utf8(const char* unicode);

BOOL WStringToString(const std::wstring &wstr,std::string &str);
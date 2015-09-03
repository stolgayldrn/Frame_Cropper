#include "helpers_fc.h"
using namespace std;

int dirExists(const char *path)
{
       if( _access( path, 0 ) == 0 ){

        struct stat status;
        stat( path, &status );

        return (status.st_mode & S_IFDIR) != 0;
    }
    return false;
}
void pathControl(string Path)
{
	if(!dirExists(Path.c_str()))
	{
		wstring stemp = wstring(Path.begin(), Path.end());
		LPCWSTR szDirPath = stemp.c_str();

		// Create a new directory.
		if(!CreateDirectoryW(szDirPath, NULL))
			printf("\nCouldn't create %S directory.\n", szDirPath);
		else
			printf("\n%S directory successfully created.\n", szDirPath);

	} 
}



string int2string(int number)
{
    if (number == 0)
        return "0";
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}
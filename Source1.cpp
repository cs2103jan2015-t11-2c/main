#include <iostream>
#include <string>
#include <WinBase.h> 

using namespace std;

int main (void) {
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(L"c:\\directory\\*.*",&data);
	
	if( h!=INVALID_HANDLE_VALUE ) 
	{
		do
		{
			char*   nPtr = new char [lstrlen( data.cFileName ) + 1];
			for( int i = 0; i < lstrlen( data.cFileName ); i++ )
				nPtr[i] = char( data.cFileName[i] );

			nPtr[lstrlen( data.cFileName )] = '\0';
			cout << nPtr << endl;

		} while(FindNextFile(h,&data));
	} 
	else 
		cout << "Error: No such folder." << endl;
	
	FindClose(h);
	
	return 0;
}

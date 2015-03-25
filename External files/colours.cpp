#include <iostream>
#include <windows.h>
using namespace std;

void SetColour(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

int main(){
	SetColour(30);
	cout << "Hello World" << endl;
	system("PAUSE");
	SetColour(12);
	cout << "Hello World" << endl;
	system("PAUSE");
	SetColour(11);
	cout << "Hello World" << endl;
	SetColour(15);		//need to set back to white after desire word otherwise everything will be that colour later on

	
	return 0;
}

/*1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
7: Default white
8: Gray/Grey
9: Bright blue
10: Brigth green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white*
-Numbers after 15 are background colors-
*/

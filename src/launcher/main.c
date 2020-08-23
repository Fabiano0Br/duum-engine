/*
 * only solution that i could find to log output shit to a file, THANKS WINDOWS
 */ 

#include <stdio.h>
#include <stdlib.h>

int main(){
	#if __unix__
	system("./duum > log.txt");
	#elif __WIN32 || __WIN64
	system("duum.exe > log.txt");
	#endif
}

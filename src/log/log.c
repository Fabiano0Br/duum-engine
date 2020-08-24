/*
 * sytem information and logger 
 */

void sysInfo(){
	/* If something doesn't work for someone, we need to see what OS he's running */
	char * sysinfo;
	char * arch;
	#if __LINUX__ 
	isysinfo = "LINUX";
	#elif __WIN32
	sysinfo = "WINDOWS";
	arch = "32 bit";
	#elif __WIN64
	sysinfo = "WINDOWS";
	arch = "64 bit";
	#elif __ANDROID__
	sysinfo = "wait, are you running ANDROID? pls contact me";
	#elif __APPLE__
	sysinfo = "MacOS";
	#elif __FreeBSD__
	sysinfo = "FreeBSD"; // i'm only doing this cuz i have a freebsd machine LOL
	#elif __unix__ 
	sysinfo = "UNIX";
	#endif	
	#if UINTPTR_MAX == 0xffFFffFF
	arch = "32 bit";
	#elif UINTPTR_MAX == 0xffFFffFFffFFffFF
	arch = "64 bit";
	#else
	arch = "unknown arch";
	#endif
	printf("\nDUUM %s %s\n\n",sysinfo,arch);
}

// Logger for windows LOL
/*
void writeLog(){
	FILE *fp;
	
	fp = fopen("log.txt", "w+");
	fprintf(fp, "This is testing for fprintf...\n");
	printf("Hello world!");
	fputs("This is testing for fputs...\n", fp);
	fclose(fp);
}*/

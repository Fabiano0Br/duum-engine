/*
 * sytem information and logger 
 */

void sysInfo(){
	char * sysinfo;
	char * arch;
	#if __LINUX__
	sysinfo = "LINUX";
	#endif 	
	#if __WIN32
	sysinfo = "WINDOWS";
	arch = "32 bit";
	#elif __WIN64
	sysinfo = "WINDOWS";
	arch = "64 bit";
	#elif UINTPTR_MAX == 0xffFFffFF
	arch = "32 bit";
	#elif UINTPTR_MAX == 0xffFFffFFffFFffFF
	arch = "64 bit";
	#else
	arch = "unknown arch";
	#endif
	printf("\nDUUM %s %s\n\n",sysinfo,arch);
}

// Logger for windows LOL

void writeLog(){
	FILE *fp;
	
	fp = fopen("log.txt", "w+");
	fprintf(fp, "This is testing for fprintf...\n");
	printf("Hello world!");
	fputs("This is testing for fputs...\n", fp);
	fclose(fp);
}

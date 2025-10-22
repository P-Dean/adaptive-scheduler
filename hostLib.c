//Written by Barry Porter, 2016

#include "dana_lib_defs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static CoreAPI *api;

#ifdef WINDOWS
#include <Windows.h>
#endif 

#ifdef LINUX
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#endif

#include "nli_util.h"
#include "vmi_util.h"

INSTRUCTION_DEF corecount(VFrame *cframe)
{
	#ifdef WINDOWS
		//return_int (cframe, 8);
		SYSTEM_INFO siSysInfo;

		// Copy the hardware information to the SYSTEM_INFO structure.

		GetSystemInfo(&siSysInfo);

		// Display the contents of the SYSTEM_INFO structure.

		//printf("Hardware information: \n");
		//printf("  OEM ID: %u\n", siSysInfo.dwOemId);
		//printf("  Number of processors: %u\n",siSysInfo.dwNumberOfProcessors);
		return_int(cframe, siSysInfo.dwNumberOfProcessors);
		//printf("  Page size: %u\n", siSysInfo.dwPageSize);
		//printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
		//printf("  Minimum application address: %lx\n",siSysInfo.lpMinimumApplicationAddress);
		//printf("  Maximum application address: %lx\n",siSysInfo.lpMaximumApplicationAddress);
		//printf("  Active processor mask: %u\n",siSysInfo.dwActiveProcessorMask);
	#endif
	#ifdef LINUX
		int numcore = sysconf(_SC_NPROCESSORS_ONLN);
		return_int(cframe, numcore);
	#endif
	return RETURN_OK;
}

INSTRUCTION_DEF memorytotal(VFrame *cframe)
{
	//return_int (cframe, 1000);
#ifdef WINDOWS
// Use to convert bytes to KB
#define DIV 1024


// Specify the width of the field in which to print the numbers.
// The asterisk in the format specifier "%*I64d" takes an integer
// argument and uses it to pad and right justify the number.
#define WIDTH 7


	MEMORYSTATUSEX statex;


	statex.dwLength = sizeof (statex);


	GlobalMemoryStatusEx (&statex);


	//printf (TEXT("There is  %*ld percent of memory in use.\n"),WIDTH, statex.dwMemoryLoad);
	//printf (TEXT("There are %*I64d total KB of physical memory.\n"),WIDTH, statex.ullTotalPhys/DIV);
	//printf (TEXT("There are %*I64d free  KB of physical memory.\n"),WIDTH, statex.ullAvailPhys/DIV);
	//printf (TEXT("There are %*I64d total KB of paging file.\n"),WIDTH, statex.ullTotalPageFile/DIV);
	//printf (TEXT("There are %*I64d free  KB of paging file.\n"),WIDTH, statex.ullAvailPageFile/DIV);
	//printf (TEXT("There are %*I64d total KB of virtual memory.\n"),WIDTH, statex.ullTotalVirtual/DIV);
	//printf (TEXT("There are %*I64d free  KB of virtual memory.\n"),WIDTH, statex.ullAvailVirtual/DIV);
	return_int(cframe, statex.ullTotalPhys/DIV);
#endif

#ifdef LINUX
	int totalmemory = sysconf(_SC_PHYS_PAGES);
	int pageSize =  sysconf(_SC_PAGE_SIZE);
	int availmem = sysconf(_SC_AVPHYS_PAGES);
	return_int(cframe, (pageSize/1024)*totalmemory);
#endif

	return RETURN_OK;
}


INSTRUCTION_DEF globalmemorytotal(VFrame *cframe)
{

	#ifdef WINDOWS
	#define DIV 1024


	// Specify the width of the field in which to print the numbers.
	// The asterisk in the format specifier "%*I64d" takes an integer
	// argument and uses it to pad and right justify the number.
	#define WIDTH 7

MEMORYSTATUSEX statex;


statex.dwLength = sizeof (statex);


GlobalMemoryStatusEx (&statex);


//printf (TEXT("There is  %*ld percent of memory in use.\n"),WIDTH, statex.dwMemoryLoad);
//printf (TEXT("There are %*I64d total KB of physical memory.\n"),WIDTH, statex.ullTotalPhys/DIV);
//printf (TEXT("There are %*I64d free  KB of physical memory.\n"),WIDTH, statex.ullAvailPhys/DIV);
//printf (TEXT("There are %*I64d total KB of paging file.\n"),WIDTH, statex.ullTotalPageFile/DIV);
//printf (TEXT("There are %*I64d free  KB of paging file.\n"),WIDTH, statex.ullAvailPageFile/DIV);
//printf (TEXT("There are %*I64d total KB of virtual memory.\n"),WIDTH, statex.ullTotalVirtual/DIV);
//printf (TEXT("There are %*I64d free  KB of virtual memory.\n"),WIDTH, statex.ullAvailVirtual/DIV);

#endif
return RETURN_OK;
}


Interface* load(CoreAPI *capi)
{
	api = capi;

	setInterfaceFunction("getcores", corecount);
	setInterfaceFunction("getmemory", memorytotal);
	setInterfaceFunction("getglobalmemory", globalmemorytotal);

	return getPublicInterface();
}

void unload()
{

}

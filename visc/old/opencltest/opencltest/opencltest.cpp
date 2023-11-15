// opencltest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <utility>

#include <vector>
//#define __NO_STD_VECTOR
#include <cl/cl.hpp>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

inline void
checkErr(cl_int err, const char * name)
{
	if (err != CL_SUCCESS) {
		std::cerr << "ERROR: " << name
			<< " (" << err << ")" << std::endl;
		exit(EXIT_FAILURE);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	cl_int err;
	std::vector< cl::Platform > platformList;
	cl::Platform::get(&platformList);
	checkErr(platformList.size()!=0 ? CL_SUCCESS : -1, "cl::Platform::get");
	std::cerr << "Platform number is: " << platformList.size() << std::endl;

	std::string platformVendor;
	platformList[0].getInfo((cl_platform_info)CL_PLATFORM_VENDOR, &platformVendor);
	std::cerr << "Platform is by: " << platformVendor << "\n";
	cl_context_properties cprops[3] = 
	{CL_CONTEXT_PLATFORM, (cl_context_properties)(platformList[0])(), 0};

	cl::Context context(
		CL_DEVICE_TYPE_CPU, 
		cprops,
		NULL,
		NULL,
		&err);
	checkErr(err, "Conext::Context()");        

	return 0;
}


/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include <iostream>
#include <limits>

#include "DebugTools.h"

#undef max

DebugTools::DebugTools(void)
{
}

DebugTools::~DebugTools(void)
{
}

void DebugTools::ShowError(RakString errorString,bool pause, unsigned int lineNum,const char *fileName)
{
	printf("%s\nFile:%s \nLine: %i\n",errorString.C_String(),fileName,lineNum);

	if (pause)
	{
		printf("Press enter to continue \n");
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		char pauseChar = std::cin.get();
	}
}

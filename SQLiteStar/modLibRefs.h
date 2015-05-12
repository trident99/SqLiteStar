/*
**  SQLiteStar Developer is a wrapper interface around the SQLite3 Database engine
**  Author: Anthony S. Daniels
**  Copyright Pyramid Solutions(2013)
**  <http://www.pyramidsolutions.com>
**
**  SQLiteStar Developer (SQD) is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.  It may be used as is in proprietary software.
**  However, if you make modifications to the code they must be published.
**
**  SQD is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with SQD.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#pragma warning (disable : 4251 ) /* sprintf, sscanf unsafe */

//Htl Dynamic Link Library definitions
#ifndef SQD_LIB_REFS_H
#define SQD_LIB_REFS_H

#ifdef SQD_DLLEXPORT
	//configure for dll export
	#define SQD_DLLAPI __declspec(dllexport)
#else
	//configure for dll import
	#define SQD_DLLAPI __declspec(dllimport)
#endif

#ifndef SQD_EXPORT
#define SQD_EXPORT __declspec(dllexport)
#endif

#ifndef SQD_IMPORT
#define SQD_IMPORT __declspec(dllimport)
#endif


#ifndef SQD_CPP_TYPEDEFS
#define SQD_CPP_TYPEDEFS
//!Unsigned 
	typedef unsigned int uint;
	typedef unsigned int size_t;
	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned char uchar;
#define NULL 0
#endif

//Standard Template Library Includes
#ifndef SQD_STD_LIB_INCLUDES
	#define SQD_STD_LIB_INCLUDES
    #include <string>
    #include <vector>
    #include <map>
	#include <stdarg.h>
	#include <typeinfo>
	//streaming input / output
	//#include <conio.h>
	#include <istream>
	#include <ostream>
	#include <iostream>
	#include <sstream>
	#include <fstream>
	#include <stdio.h>
#endif

#ifndef SQLITE_INCLUDES
#define SQLITE_INCLUDES
	#include "..\SQLite3\sqlite3.h"
#endif

#endif


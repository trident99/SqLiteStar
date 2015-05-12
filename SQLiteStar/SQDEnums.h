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

#ifndef SQDEnums_H
#define SQDEnums_H

#include "modLibRefs.h"

namespace SQD
{

	//!These are the template functions for conversion of enumerated types
	//to and from string form.

	template <typename T>
	SQD_EXPORT void EnumToString(T enumVal, std::string & strReturn){return;};
	
	template <typename T>
	SQD_EXPORT void StringToEnum(std::string & strVal, T & enumValReturn){return;};


	//!SQDFieldType is an enumerated type that provides base class information
	/*!
	SQDFieldType is an enumerated type that provides base class information.
	It is often used in serialization and object querying and as a template argument. 
	The default is UnknownType.
	*/
	enum SQD_DLLAPI SQDFieldType
	{
		UnknownType = -1,
		CPP_BOOL = 0,
		CPP_CHAR = 1,
		CPP_UCHAR = 2,
		CPP_SHORT = 3,
		CPP_USHORT = 4,
		CPP_INT = 5,
		CPP_UINT = 6, 
		CPP_LONG = 7,
		CPP_ULONG = 8,
		CPP_FLOAT = 9,
		CPP_DOUBLE = 10,
		SQL_STRING = 20,
		SQL_BLOB = 21
	};

	//!Enumerated Type To String for SQDFieldType
	template <>
	SQD_EXPORT void EnumToString<SQDFieldType>(SQDFieldType enumVal, std::string & strReturn);
	//!String to Enumerated Type for SQDFieldType
	template <>
	SQD_EXPORT void StringToEnum<SQDFieldType>(std::string & strVal, SQDFieldType & enumValReturn);

};//end namespace SQD

#endif //SQDEnums_H
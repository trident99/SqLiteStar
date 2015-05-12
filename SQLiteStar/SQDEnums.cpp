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
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\SQDEnums.h"

namespace SQD{
	//!Enumerated Type To String for SQDFieldType
	template <>
	void EnumToString<SQDFieldType>(SQDFieldType enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			//SQD CPLUSPLUS NATIVE TYPES
			case UnknownType: {strReturn = "UnknownType";  return; break;};
			case CPP_BOOL: {strReturn = "CPP_BOOL";  return; break;};
			case CPP_CHAR: {strReturn = "CPP_CHAR";  return; break;};
			case CPP_UCHAR: {strReturn = "CPP_UCHAR";  return; break;};
			case CPP_SHORT: {strReturn = "CPP_SHORT";  return; break;};
			case CPP_USHORT: {strReturn = "CPP_USHORT";  return; break;};
			case CPP_INT: {strReturn = "CPP_INT";  return; break;};
			case CPP_UINT: {strReturn = "CPP_UINT";  return; break;};
			case CPP_LONG: {strReturn = "CPP_LONG";  return; break;};
			case CPP_ULONG: {strReturn = "CPP_ULONG";  return; break;};
			case CPP_FLOAT: {strReturn = "CPP_FLOAT";  return; break;};
			case CPP_DOUBLE: {strReturn = "CPP_DOUBLE";  return; break;};
				//SQLite
			case SQL_STRING: {strReturn = "SQL_STRING";  return; break;};
			case SQL_BLOB: {strReturn = "SQL_BLOB";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "UnknownType";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;
	};
	//!String to Enumerated Type for SQDFieldType	
	template <>
	void StringToEnum<SQDFieldType>(std::string & strVal, SQDFieldType & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = UnknownType; return;};
			//check by comparison
			//SQD CPLUSPLUS NATIVE TYPES
			if(strVal == "CPP_BOOL"){enumValReturn = CPP_BOOL; return;};
			if(strVal == "CPP_CHAR"){enumValReturn = CPP_CHAR; return;};
			if(strVal == "CPP_UCHAR"){enumValReturn = CPP_UCHAR; return;};
			if(strVal == "CPP_SHORT"){enumValReturn = CPP_SHORT; return;};
			if(strVal == "CPP_USHORT"){enumValReturn = CPP_USHORT; return;};
			if(strVal == "CPP_INT"){enumValReturn = CPP_INT; return;};
			if(strVal == "CPP_UINT"){enumValReturn = CPP_UINT; return;};
			if(strVal == "CPP_LONG"){enumValReturn = CPP_LONG; return;};
			if(strVal == "CPP_ULONG"){enumValReturn = CPP_ULONG; return;};
			if(strVal == "CPP_FLOAT"){enumValReturn = CPP_FLOAT; return;};
			if(strVal == "CPP_DOUBLE"){enumValReturn = CPP_DOUBLE; return;};
			//HTL SERIALIZABLE OBJECTS
			if(strVal == "SQL_STRING"){enumValReturn = SQL_STRING; return;};
			if(strVal == "SQL_BLOB"){enumValReturn = SQL_BLOB; return;};


			//DEFUALT UNKNOWN
			enumValReturn = UnknownType;
			return;
		}catch(...){
			enumValReturn = UnknownType;
			return;
		};
	};

};//end namespace HTL
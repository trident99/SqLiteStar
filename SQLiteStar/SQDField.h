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

#ifndef SQDField_H
#define SQDField_H

#include ".\modLibRefs.h"
#include ".\modMemVarMacros.h"
#include ".\SQDEnums.h"
#include ".\SQDField.h"

namespace SQD
{
	//!SQDRecord Forward Declaration
	class SQDRecord;

	/*!The SQDField class is a name value pair wrapper for an individual field of data
	*It has conveinience accessor functions for varying data types.  However, 
	*all data is natively as text and then converted as necessary.  
	*It handles all data types other than BLOB.
	*SQDField will not handle the BLOB data type from SQLite.
	*This functionality is intended to be added at a later date.  
	*/
	//!The SQDField class is a name value pair wrapper for an individual field of data.
	class SQD_DLLAPI SQDField
	{
	public:
		//!Void constructor
		SQDField();
		//!Copy constructor
		SQDField(SQDField & rhs);
		//!Virtual destructor
		virtual ~SQDField(void);
		//PUBLIC OPERATOR OVERLOADS
		//!Assignment Operator
		SQDField & operator = (SQDField & rhs);
		
		//!Field Name
		HTLMEMVAR_BYVAL_STYLE1(public,std::string,strName);
		//!Pointer to Parent Record
		HTLMEMVAR_BYVAL_STYLE1(public,SQDRecord*,ptrParent);
		//!Field Type
		HTLMEMVAR_BYVAL_STYLE1(public,SQDFieldType,objType);

		//!Set and Get for Node Value
		void Set_strValue(const std::string & strValue);
		void Set_strValue(const char * ptrCharString);
		void Set_strValue(bool blnVal);
		void Set_strValue(short shrtVal);
		void Set_strValue(unsigned short ushrtVal);
		void Set_strValue(int intVal);
		void Set_strValue(unsigned int uint);
		void Set_strValue(long lngVal);
		void Set_strValue(unsigned long ulngVal);
		void Set_strValue(float sngVal);
		void Set_strValue(double dblVal);
		void Set_strValue(char chrVal);
		void Set_strValue(unsigned char uchrVal);

		//!Set and Get for Node Value
		std::string Get_strValue(void);
		void Get_strValue(bool & blnValReturn);
		void Get_strValue(short & shrtValReturn);
		void Get_strValue(unsigned short & ushrtValReturn);
		void Get_strValue(int & intValReturn);
		void Get_strValue(unsigned int & uintValReturn);
		void Get_strValue(long & lngValReturn);
		void Get_strValue(unsigned long & ulngValReturn);
		void Get_strValue(float & sngValReturn);
		void Get_strValue(double & dblValReturn);
		void Get_strValue(char & chrValReturn);
		void Get_strValue(unsigned char & uchrValReturn);
		void Get_strValue(std::string & strValReturn);

	protected:
		//!String field value
		std::string m_strValue;


	};//end class SQDField

};//end namespace SQD
#endif //SQDField_H
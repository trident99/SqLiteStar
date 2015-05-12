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
#define SQD_DLLEXPORT
#pragma warning(pop)

#include ".\SQDField.h"


namespace SQD{
	//!Void Constructor
	SQDField::SQDField()
	{
		m_ptrParent = NULL;
		return;
	};
	//!Copy constructor
	SQDField::SQDField(SQDField & rhs)
	{
		//self assignment check
		if(this == &rhs)
			return;
		m_ptrParent = NULL;
		this->m_strName = rhs.Get_strName();
		this->m_strValue = rhs.Get_strValue();

		return;
	};
	//!Virtual destructor
	SQDField::~SQDField(void)
	{
		m_ptrParent = NULL;
		this->m_strName.clear();
		this->m_strValue.clear();
		return;
	};
	//PUBLIC OPERATOR OVERLOADS
	//!Assignment Operator
	SQDField & SQDField::operator = (SQDField & rhs)
	{
		//self assignment check
		if(this == &rhs)
			return *this;

		this->m_strName = rhs.Get_strName();
		this->m_strValue = rhs.Get_strValue();

		return *this;
	};
	//!Get and Set Accessors for Field Value
	void SQDField::Set_strValue(const std::string & strValue)
	{
		m_strValue = strValue;
		m_objType = SQL_STRING;
	};

	void SQDField::Set_strValue(const char * ptrCharString)
	{
		m_strValue = ptrCharString;
		m_objType = SQL_STRING;
	};

	void SQDField::Set_strValue(bool blnVal)
	{
		if(blnVal)
		{
			m_strValue = '1';
		}else{
			m_strValue = '0';
		};
		m_objType = CPP_BOOL;
	};

	void SQDField::Set_strValue(short shrtVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%d",shrtVal);
			m_strValue = chrBuf;
			m_objType = CPP_SHORT;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(unsigned short ushrtVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%u",ushrtVal);
			m_strValue = chrBuf;
			m_objType = CPP_USHORT;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(int intVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%d",intVal);
			m_strValue = chrBuf;
			m_objType = CPP_INT;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(unsigned int uint)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%u",uint);
			m_strValue = chrBuf;
			m_objType = CPP_UINT;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(long lngVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%ld",lngVal);
			m_strValue = chrBuf;
			m_objType = CPP_LONG;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(unsigned long ulngVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%lu",ulngVal);
			m_strValue = chrBuf;
			m_objType = CPP_ULONG;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(float sngVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%f",sngVal);
			m_strValue = chrBuf;
			m_objType = CPP_FLOAT;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(double dblVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%lf",dblVal);
			m_strValue = chrBuf;
			m_objType = CPP_DOUBLE;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(char chrVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%s",chrVal);
			m_strValue = chrBuf;
			m_objType = CPP_CHAR;
		}catch(...){
			return;
		}
	};

	void SQDField::Set_strValue(unsigned char uchrVal)
	{
		try{
			char chrBuf[256];
			sprintf(chrBuf,"%s",uchrVal);
			m_strValue = chrBuf;
			m_objType = CPP_UCHAR;
		}catch(...){
			return;
		}
	};

	std::string SQDField::Get_strValue(void)
	{
		return m_strValue;
	};

	void SQDField::Get_strValue(bool & blnValReturn)
	{
		if((m_objType == CPP_BOOL)||(m_objType == SQL_STRING))
		{
			if(m_strValue == "1")
			{
				//return true
				blnValReturn = true;
			}else{
				//return false
				blnValReturn = false;
			};
		}else{
			//not a boolean attribute type
			//return default value
			blnValReturn = false;
		};
		return;
	};

	void SQDField::Get_strValue(short & shrtValReturn)
	{		
		short shrtTemp;
		const char * chrBuffer;
		if((m_objType == CPP_SHORT)||(m_objType == SQL_STRING))
		{
			chrBuffer = m_strValue.c_str();
			sscanf(m_strValue.c_str(),"%d",&shrtTemp);
			shrtValReturn = shrtTemp;
		}else{
			//not a short attribute type
			//return default value
			shrtValReturn = 0;
		};
		return;
	};

	void SQDField::Get_strValue(unsigned short & ushrtValReturn)
	{		
		unsigned short ushrtTemp;
		const char * chrBuffer;
		if((m_objType == CPP_USHORT)||(m_objType == SQL_STRING))
		{
			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%u",&ushrtTemp);
			ushrtValReturn = ushrtTemp;
		}else{
			//not a short attribute type
			//return default value
			ushrtValReturn = 0;
		};
		return;
	};

	void SQDField::Get_strValue(int & intValReturn)
	{		
		int intTemp;
		const char * chrBuffer;
		if((m_objType == CPP_INT)||(m_objType == SQL_STRING))
		{
			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%d",&intTemp);
			intValReturn = intTemp;
		}else{
			//not a int attribute type
			//return default value
			intValReturn = 0;
		};
		return;
	};

	void SQDField::Get_strValue(unsigned int & uintValReturn)
	{		
		unsigned int uintTemp;
		const char * chrBuffer;
		if((m_objType == CPP_UINT)||(m_objType == SQL_STRING))
		{
			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%u",&uintTemp);
			uintValReturn = uintTemp;
		}else{
			//not a int attribute type
			//return default value
			uintValReturn = 0;
		};
		return;
	};

	void SQDField::Get_strValue(long & lngValReturn)
	{		
		long lngTemp;
		const char * chrBuffer;
		if((m_objType == CPP_LONG)||(m_objType == SQL_STRING))
		{
			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%ld",&lngTemp);
			lngValReturn = lngTemp;
		}else{
			//not a long attribute type
			//return default value
			lngValReturn = 0;
		};
		return;
	};

	void SQDField::Get_strValue(unsigned long & ulngValReturn)
	{
		unsigned long ulngTemp;
		const char * chrBuffer;
		if((m_objType == CPP_ULONG)||(m_objType == SQL_STRING))
		{
			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%lu",&ulngTemp);
			ulngValReturn = ulngTemp;
		}else{
			//not a long attribute type
			//return default value
			ulngValReturn = 0;
		};
		return;
	};

	void SQDField::Get_strValue(float & sngValReturn)
	{
		float sngTemp;
		const char * chrBuffer;
		if((m_objType == CPP_FLOAT)||(m_objType == SQL_STRING))
		{

			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%f",&sngTemp);
			sngValReturn = sngTemp;
		}else{
			//not a float attribute type
			//return default value
			sngValReturn = 0.0f;
		};
		return;
	};

	void SQDField::Get_strValue(double & dblValReturn)
	{
		double dblTemp;
		const char * chrBuffer;
		if((m_objType == CPP_DOUBLE)||(m_objType == SQL_STRING))
		{
			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%lf",&dblTemp);
			dblValReturn = dblTemp;
		}else{
			//not a double attribute type
			//return default value
			dblValReturn = 0.0f;
		};
		return;
	};

	void SQDField::Get_strValue(char & chrValReturn)
	{	
		char chrTemp;
		const char * chrBuffer;
		if((m_objType == CPP_CHAR)||(m_objType == SQL_STRING))
		{
			std::string strTemp = m_strValue;

			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%c",&chrTemp);
			chrValReturn = chrTemp;
		}else{
			//not a char attribute type
			//return default value
			chrValReturn = NULL;
		};
		return;
	};

	void SQDField::Get_strValue(unsigned char & uchrValReturn)
	{	
		unsigned char uchrTemp;
		const char * chrBuffer;
		if((m_objType == CPP_UCHAR)||(m_objType == SQL_STRING))
		{		
			std::string strTemp = m_strValue;

			chrBuffer = m_strValue.c_str();
			sscanf(chrBuffer,"%c",&uchrTemp);
			uchrValReturn = uchrTemp;
		}else{
			//not a char attribute type
			//return default value
			uchrValReturn = NULL;
		};
		return;
	};

	void SQDField::Get_strValue(std::string & strValReturn)
	{	
		strValReturn = m_strValue;
	};

};//end namespace SQD

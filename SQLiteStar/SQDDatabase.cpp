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

#include ".\SQDDatabase.h"

namespace SQD{
	//!void constructor
	SQDDatabase::SQDDatabase()
	{
		m_ptrDB = NULL;
	};
	//!void destructor
	SQDDatabase::~SQDDatabase()
	{
		sqlite3_close(m_ptrDB);
		//delete m_ptrDB;
		m_ptrDB = NULL;
	};

	//!Get the pointer to the RAW DATABASE
	sqlite3* SQDDatabase::Get_ptrDB(void)
	{
		if(m_ptrDB)
		{
			return m_ptrDB;	
		}else{
			return NULL;
		}
	};

	//!Open the database connection
	int SQDDatabase::OpenDB(void)
	{
		int intResult;
		std::string strFullPathName;
		intResult = sqlite3_open(m_strDBPathName.c_str(),&m_ptrDB);
		if(intResult == SQLITE_OK)
		{
			m_blnIsOpen = true;
			return 1;
		}else{
			m_blnIsOpen = false;
			return 0;
		};
	};
	//!Close the database Connection
	int SQDDatabase::CloseDB(void)
	{
		int intResult;
		std::string strFullPathName;
		intResult = sqlite3_close(m_ptrDB);
		if(intResult == SQLITE_OK)
		{
			m_blnIsOpen = false;
			return 1;
		}else{
			m_blnIsOpen = true;
			return 0;
		};
	};
	//!Returns if the database is open
	bool SQDDatabase::IsOpen(void)
	{
		return this->m_blnIsOpen;		
	};

	//!Returns a list of table names for the database.
	std::vector<std::string> SQDDatabase::GetTableNames(void)
	{
		int intRes;
		std::vector<std::string> arrStrNames, arrStrColNames;
		if(m_blnIsOpen)
		{
			//SELECT name FROM sqlite_master
			//WHERE type='table'
			//ORDER BY name;
			std::string strCom, strColName;
			strCom = "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name";
			sqlite3_stmt* ptrStatement;
			intRes = sqlite3_prepare(m_ptrDB, strCom.c_str(), -1, &ptrStatement, 0);
			if(intRes == SQLITE_OK)
			{
				size_t i, UboundI, intColName;
				bool blnNext = true;
				string strVal;
				//if no statement abort
				if(!ptrStatement){return arrStrNames;};
				//get all of the column names
				UboundI = sqlite3_column_count(ptrStatement);
				arrStrColNames.clear();
				for(i = 0; i < UboundI; i++)
				{
					strColName = (char*)sqlite3_column_name(ptrStatement,i);
					arrStrColNames.push_back(strColName);
					if(strColName == "name")
					{
						intColName = i;//mark the tablename index
					};
				};
				//get the rows
				while (blnNext)
				{
					intRes = sqlite3_step(ptrStatement);
					if(intRes == SQLITE_ROW)
					{
						strVal = (char*)sqlite3_column_text(ptrStatement, intColName);
						arrStrNames.push_back(strVal);
					}
					if((intRes == SQLITE_DONE) || (intRes == SQLITE_ERROR))
					{
						blnNext = false;
					}
				}//end while loop
				return arrStrNames;
			};//int result SQLITE_OK
		};//end database open check
		return arrStrNames;
	};

}

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

#include ".\SQDRecord.h"
#include ".\SQDDatabase.h"

namespace SQD{
	//void constructor
	SQDRecord::SQDRecord()
	{
		m_blnNewRecord = false;
		m_blnDeleteRecord = false;
		m_blnModified = false;
		m_ptrDatabase = NULL;
	};
	//!copy constructor
	SQDRecord::SQDRecord(SQDRecord & rhs)
	{
		//don't allow cloning
		m_blnNewRecord = false;
		m_blnDeleteRecord = false;
		m_blnModified = false;
		m_ptrDatabase = NULL;
	};
	//void destructor
	SQDRecord::~SQDRecord()
	{
		this->DeleteAllFields();
	};
	//PUBLIC OPERATOR OVERLOADS
	SQDRecord & SQDRecord::operator = (SQDRecord & rhs)
	{
		//don't allow assignment
		return *this;
	};

	//DB====>Active Memory
	//Updates all fields 
	int SQDRecord::UpdateAll(void)
	{
		int intRes;
		size_t i, UboundI;
		sqlite3_stmt * ptrStatement;
		std::stringstream strRet;
		std::vector<std::string> arrStrColNames;
		SQDField* ptrKey = this->AtField(0);
		if(ptrKey)
		{
			//ASSUMES THE FIRST FIELD IS THE PRIMARY KEY
			strRet << "SELECT rowid,* FROM " << m_strTableName.c_str() <<
				"WHERE " << ptrKey->Get_strName().c_str() <<
				" = '" << ptrKey->Get_strValue().c_str() << "'";
		}else{
			//no primary key field
			return -1;
		}

		if(m_ptrDatabase)
		{
			intRes = sqlite3_prepare(m_ptrDatabase->Get_ptrDB(), 
				strRet.str().c_str(), -1, &ptrStatement, 0);
			//get all of the column names
			UboundI = sqlite3_column_count(ptrStatement);
			arrStrColNames.clear();
			for(i = 0; i < UboundI; i++)
			{
				arrStrColNames.push_back((char*)sqlite3_column_name(ptrStatement,i));
			};
			if(intRes == SQLITE_OK)
			{
				intRes = sqlite3_step(ptrStatement);
				if(intRes == SQLITE_ROW)
				{
					for(i = 0; i < UboundI; i++)
					{
						string strVal = (char*)sqlite3_column_text(ptrStatement, i);
						SQDField * ptrField = this->GetField(arrStrColNames.at(i));
						if(ptrField)
						{
							ptrField->Set_strValue(strVal);
						}//end valid field
					}//end loop through columns
					return 1;
				}//end row check	
			}//end valid Query
		}//end database check

		return 0;
	};

	//!Update the value for the selected field
	int SQDRecord::UpdateField(size_t index)
	{
		int intRes;
		size_t i, UboundI;
		sqlite3_stmt * ptrStatement;
		std::stringstream strRet;
		std::vector<std::string> arrStrColNames;
		//ASSUMES FIELD 0 IS THE KEY
		SQDField* ptrKey = this->AtField(0);
		if(ptrKey)
		{

		strRet << "SELECT rowid,* FROM " << m_strTableName.c_str() <<
				"WHERE " << ptrKey->Get_strName().c_str() <<
				" = '" << ptrKey->Get_strValue().c_str() << "'";
		}else{
			return -1;
		}

		if(m_ptrDatabase)
		{
			intRes = sqlite3_prepare(m_ptrDatabase->Get_ptrDB(), 
				strRet.str().c_str(), -1, &ptrStatement, 0);
			//get all of the column names
			UboundI = sqlite3_column_count(ptrStatement);
			arrStrColNames.clear();
			for(i = 0; i < UboundI; i++)
			{
				arrStrColNames.push_back((char*)sqlite3_column_name(ptrStatement,i));
			};
			if(intRes == SQLITE_OK)
			{
				intRes = sqlite3_step(ptrStatement);
				if(intRes == SQLITE_ROW)
				{
					string strVal = (char*)sqlite3_column_text(ptrStatement, index);
					SQDField * ptrField = this->GetField(arrStrColNames.at(index));
					ptrField->Set_strValue(strVal);
					return 1;
				}	
			}
		}//end database check

		return 0;
	};

	//Active Memory====>DB
	//!Commit all values for all fields
	int SQDRecord::CommitAll(void)
	{
		//check to see if deleting record,
		//new record insert or just modified record

		int intRet = 0;
		if(m_blnDeleteRecord)
		{
			intRet = this->CommitDeleteRecord();
			return intRet;
		}
		if(m_blnNewRecord)
		{
			intRet = this->CommitNewRecord();
			return intRet;
		}
		//otherwise treat as a modified
		intRet = this->CommitModifiedRecord();
		return intRet;
	};

	//!Commit the value of the selected field to the database
	int SQDRecord::CommitField(size_t index)
	{
		//UPDATE table_name
		//SET column1 = value1, column2 = value2...., columnN = valueN
		//WHERE [condition];
		size_t i, UboundI;
		char * zErrMsg;
		//safety check array size
		UboundI = m_arrPtrFields.size();
		if(UboundI <= 0){return 0;};

		if((index >= 0) && (index < UboundI))
		{
			SQDField* ptrCurrField = m_arrPtrFields.at(index);
			std::stringstream strCom;
			SQDField* ptrKey = this->AtField(0);
			if(ptrKey)
			{
				strCom << "UPDATE " << m_strTableName.c_str() << "SET " <<
					ptrCurrField->Get_strName().c_str() << "= '" << ptrCurrField->Get_strValue().c_str() << "' " <<
					" WHERE " << ptrKey->Get_strName().c_str() <<
					" = '" << ptrKey->Get_strValue().c_str() << "'";
				sqlite3_exec(m_ptrDatabase->Get_ptrDB(),strCom.str().c_str(),NULL,NULL,&zErrMsg);
			}else{
				return -1;
			}
			return 1;
		}
		return 0;
	};

	//!Get the field collection pointer
	SQDFieldCollection * SQDRecord::GetFieldCollPtr(void)
	{
		return &m_arrPtrFields;
	};

	//CONTAINER ACCESSORS FOR TABLE COLLECTION
	//!Does the Table with strName Exist
	bool SQDRecord::DoesFieldExist(std::string strName)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrFields.size();
		for(i = 0; i < UboundI; i++)
		{
			strTemp = m_arrPtrFields.at(i)->Get_strName();
			if(strTemp == strName)
			{
				return true;
			};//end field name check
		};//end loop i
		//field wasn't found, return illegal index
		return false;
	};

	//!Does the Table with strName Exist
	SQDField * SQDRecord::GetField(std::string strName)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrFields.size();
		for(i = 0; i < UboundI; i++)
		{
			strTemp = m_arrPtrFields.at(i)->Get_strName();
			if(strTemp == strName)
			{
				return m_arrPtrFields.at(i);
			};//end field name check
		};//end loop i
		//field wasn't found, return illegal index
		return NULL;
	};

	//!Gets the field index number
	int SQDRecord::GetFieldLoc(std::string strName)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrFields.size();
		for(i = 0; i < UboundI; i++)
		{
			strTemp = m_arrPtrFields.at(i)->Get_strName();
			if(strTemp == strName)
			{
				return i;
			};//end field name check
		};//end loop i
		//field wasn't found, return illegal index
		return -1;
	};

	//!Returns the table at the desired index
	SQDField * SQDRecord::AtField(size_t index)
	{
		if((index >= 0) && (index < m_arrPtrFields.size()))
		{
			return m_arrPtrFields.at(index);
		}else{
			return NULL;
		};
	};

	//!Returns the number of fields in the record
	int SQDRecord::CountFields(void)
	{
		return m_arrPtrFields.size();
	};
	//!Returns the 
	int SQDRecord::Size(void)
	{
		return m_arrPtrFields.size();
	};
	//!Get the FieldName at the index
	std::string SQDRecord::GetFieldName(size_t index)
	{
		std::string strTemp;
		if((index >= 0) &&(index < m_arrPtrFields.size()))
		{
			strTemp = m_arrPtrFields.at(index)->Get_strName();
		}
		return strTemp;
	};

	//!Get the first table in the collection iterator
	SQDFieldIterator SQDRecord::BeginField(void)
	{
		m_ptrCursor = m_arrPtrFields.begin();
		return m_ptrCursor;
	};

	//!Get the last table in the collection iterator
	SQDFieldIterator SQDRecord::EndField(void)
	{
		if(m_arrPtrFields.size() > 0)
		{
			if(m_ptrCursor != m_arrPtrFields.end())
			{
				m_ptrCursor = m_arrPtrFields.end();
				--m_ptrCursor;
				return m_ptrCursor;
			};
		}else{
			//no elements go to the beginning instead
			m_ptrCursor = m_arrPtrFields.begin();
		};
		return m_ptrCursor;
	};

	//!Get the next field iterator
	SQDFieldIterator SQDRecord::NextField(void)
	{
		if(m_ptrCursor != m_arrPtrFields.end())
		{
			++m_ptrCursor;
		};
		return m_ptrCursor;
	};

		//!Get the current cursor
	SQDFieldIterator SQDRecord::GetCursor(void)
	{
		return m_ptrCursor;
	};

	//!Create a Table with the supplied table definition
	SQDField * SQDRecord::CreateField(std::string strName, SQDFieldType enmType)
	{
		SQDField* ptrNewField = new SQDField();
		ptrNewField->Set_strName(strName);
		ptrNewField->Set_objType(enmType);
		ptrNewField->Set_ptrParent(this);
		m_arrPtrFields.push_back(ptrNewField);
		return(ptrNewField);
	};
	//!Delete the table with the provided name
	int SQDRecord::DeleteField(std::string strName)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrFields.size();
		for(i = 0; i < UboundI; i++)
		{
			strTemp = m_arrPtrFields.at(i)->Get_strName();
			if(strTemp == strName)
			{
				delete m_arrPtrFields.at(i);
				m_arrPtrFields.erase(m_arrPtrFields.begin() + i);
				return 1;
			};//end field name check
		};//end loop i
		//field wasn't found, return illegal index
		return 0;
	};
	//!Delete all of the tables
	int SQDRecord::DeleteAllFields(void)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrFields.size();
		for(i = 0; i < UboundI; i++)
		{
			delete m_arrPtrFields.at(i);
		};//end loop i	
		m_arrPtrFields.clear();
		return 1;
	};

	int SQDRecord::CommitModifiedRecord(void)
	{
		//UPDATE table_name
		//SET column1 = value1, column2 = value2...., columnN = valueN
		//WHERE [condition];
		size_t i, UboundI;
		char * zErrMsg;
		//safety check array size
		UboundI = m_arrPtrFields.size();
		if(UboundI <= 0){return 0;};
		if(!m_ptrDatabase){return 0;};
		//ASSUMES KEY FIELD IS COLUMN 0
		SQDField* ptrKey = m_arrPtrFields.at(0);
		if(ptrKey)
		{
			for(i = 0; i < UboundI;i++)
			{
				SQDField* ptrCurrField = m_arrPtrFields.at(i);
				if((i != 0)&&(ptrCurrField->Get_strValue() != "rowid"))
				{//then not primary key
					std::stringstream strCom;
					strCom << "UPDATE " << m_strTableName.c_str() << " SET " <<
						ptrCurrField->Get_strName().c_str() << "= '" << ptrCurrField->Get_strValue().c_str() << "' " <<
						"WHERE " << ptrKey->Get_strName().c_str() <<
						" = '" << ptrKey->Get_strValue().c_str() << "'";
					sqlite3_exec(m_ptrDatabase->Get_ptrDB(),strCom.str().c_str(),NULL,NULL,&zErrMsg);
				}//end primary key check
			}//end loop i
		}//end valid key field
		return 0;
	};

	int SQDRecord::CommitNewRecord(void)
	{
		char chrID[50];
		size_t i, UboundI;
		char * zErrMsg;	
		//safety check
		UboundI = m_arrPtrFields.size();
		if(UboundI <= 0){return 0;};
		if(!m_ptrDatabase){return 0;};
		//insert the new row, get the row id, input the fields
		std::stringstream strCom;
		strCom << "INSERT INTO " << m_strTableName.c_str() << " DEFAULT VALUES";
		sqlite3_exec(m_ptrDatabase->Get_ptrDB(),strCom.str().c_str(),NULL,NULL,&zErrMsg);

		//Get the inserted row ID
		long intRowID = sqlite3_last_insert_rowid(m_ptrDatabase->Get_ptrDB());
		sprintf(chrID,"%ld",intRowID);


		//ASSUMES KEY FIELD IS COLUMN 0
		for(i = 0; i < UboundI; i++)
		{
			SQDField* ptrCurrField = m_arrPtrFields.at(i);
			if((i != 0)&&(ptrCurrField->Get_strValue() != "rowid"))
			{//then not primary key
				std::stringstream strCom2;
				strCom2 << "UPDATE " << m_strTableName.c_str() << " SET " <<
					ptrCurrField->Get_strName().c_str() << "= '" << ptrCurrField->Get_strValue().c_str() << "' " <<
					" WHERE " << "rowid" << " = '" << chrID << "'";

				sqlite3_exec(m_ptrDatabase->Get_ptrDB(),strCom2.str().c_str(),NULL,NULL,&zErrMsg);
			}
		}

		return 1;
	};

	int SQDRecord::CommitDeleteRecord(void)
	{
		size_t i, UboundI;
		char * zErrMsg;
		//safety check array size
		UboundI = m_arrPtrFields.size();
		if(UboundI <= 0){return 0;};
		if(!m_ptrDatabase){return 0;};
		//ASSUMES KEY FIELD IS COLUMN 0
		SQDField* ptrKey = m_arrPtrFields.at(0);
		if(ptrKey)
		{
			std::stringstream strCom;
			strCom << "DELETE FROM " << m_strTableName.c_str() << 
				" WHERE " << ptrKey->Get_strName().c_str() <<
				" = '" << ptrKey->Get_strValue().c_str() << "'";
			sqlite3_exec(m_ptrDatabase->Get_ptrDB(),strCom.str().c_str(),NULL,NULL,&zErrMsg);
		}//end valid key field
		return 0;
	};

};//end namespace SQD
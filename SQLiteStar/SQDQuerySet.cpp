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

#include ".\SQDQuerySet.h"
#include ".\SQDDatabase.h"

namespace SQD{
	//void constructor
	SQDQuerySet::SQDQuerySet()
	{
		m_ptrDatabase = NULL;
		m_ptrStatement = NULL;
	};
	//!copy constructor
	SQDQuerySet::SQDQuerySet(SQDQuerySet & rhs)
	{
		//do not allow cloning
	};
	//void destructor
	SQDQuerySet::~SQDQuerySet()
	{
		this->DeleteAllRecords();
	};
	//PUBLIC OPERATOR OVERLOADS
	SQDQuerySet & SQDQuerySet::operator = (SQDQuerySet & rhs)
	{
		//do not allow assignment
		return *this;
	};

	//!Database Accessors
	void SQDQuerySet::Set_ptrDatabase(SQDDatabase* ptrDB)
	{
		size_t i, UboundI;
		m_ptrDatabase = ptrDB;
		if(m_arrPtrRecords.size() > 0)
		{
			UboundI = m_arrPtrRecords.size();
			for(i = 0; i < UboundI;i++)
			{
				m_arrPtrRecords.at(i)->Set_ptrDatabase(ptrDB);
			};
		};
	};
	SQDDatabase* SQDQuerySet::Get_ptrDatabase(void)
	{
		if(m_ptrDatabase)
		{
			return m_ptrDatabase;
		}else{
			return NULL;
		}
	};
	//Promulgate table name to all records
	void SQDQuerySet::Set_AllTableNames(std::string strTableName)
	{
		size_t i, UboundI;
		UboundI = m_arrPtrRecords.size();
		m_strTableName = strTableName;
		for(i = 0; i < UboundI;i++)
		{
			m_arrPtrRecords.at(i)->Set_strTableName(strTableName);
		};
	};

	//!Promulgate database pointer to all records.  This is important to do before trying commits.
	//Execute does this automatically at the end of a query recordset build.
	void SQDQuerySet::Set_AllDatabasePtrs(SQDDatabase* ptrDB)
	{
		size_t i, UboundI;
		UboundI = m_arrPtrRecords.size();
		m_ptrDatabase = ptrDB;
		for(i = 0; i < UboundI;i++)
		{
			m_arrPtrRecords.at(i)->Set_ptrDatabase(ptrDB);
		};		
	};

	//!Update All Records from the Database to the Recordset
	int SQDQuerySet::Execute(void)
	{
		int intRes;
		size_t i, UboundI;
		bool blnNext = true;
		//clear the recordset
		this->RemoveAllRecords();
		m_intResult = sqlite3_prepare(m_ptrDatabase->Get_ptrDB(), 
			this->m_strQuery.c_str(), -1, &m_ptrStatement, 0);

		if(m_intResult == SQLITE_OK)
		{
			//get all of the column names
			UboundI = sqlite3_column_count(m_ptrStatement);
			m_arrStrColNames.clear();
			for(i = 0; i < UboundI; i++)
			{
				m_arrStrColNames.push_back((char*)sqlite3_column_name(m_ptrStatement,i));
			};
			//get the rows

			//reset t
			while (blnNext)
			{
				intRes = sqlite3_step(m_ptrStatement);
				if(intRes == SQLITE_ROW)
				{
					SQDRecord* ptrNewRec = new SQDRecord();
					for(i = 0; i < UboundI; i++)
					{
						char* ptrStrVal = NULL;
						SQDField * ptrNewField = ptrNewRec->CreateField(m_arrStrColNames.at(i),SQL_STRING);
						ptrStrVal = (char*)sqlite3_column_text(m_ptrStatement, i);
						if(ptrStrVal)
						{
							string strVal = ptrStrVal;
							ptrNewField->Set_strValue(strVal);
						};
					}
					m_arrPtrRecords.push_back(ptrNewRec);
				}
				if((intRes == SQLITE_DONE) || (intRes == SQLITE_ERROR))
				{
					blnNext = false;
				}
			}
			this->Set_AllTableNames(m_strTableName);
			return 1;
		}
		return 0;
	};

	//!Update Row from the Database to the Recordset
	int SQDQuerySet::UpdateAll(void)
	{
		if(m_ptrStatement)
		{
			sqlite3_reset(m_ptrStatement);
			this->Execute();
			return 1;
		};
		return 0;
	};

	//!Update Row from the Database to the Recordset
	int SQDQuerySet::UpdateRow(size_t intRow)
	{
		if((intRow >= 0) && (intRow < m_arrPtrRecords.size()))
		{
			m_arrPtrRecords.at(intRow)->UpdateAll();
			return 1;
		};
		return 0;
	};

	//!Commit All Changes to the database
	int SQDQuerySet::CommitAll(void)
	{
		int intResult;
		size_t i, UboundI;
		SQDRecordIterator iter;
		if(m_arrPtrRecords.size() > 0)
		{
			for(iter = m_arrPtrRecords.begin(); iter != m_arrPtrRecords.end();++iter)
			{
				//commit all for the record
				(*iter)->Set_ptrDatabase(m_ptrDatabase);
				intResult &= (*iter)->CommitAll();
			}
			//successul
			return intResult;
		}else{
			return 0;
		};
	};
	//!Commit Row Changes to the database
	int SQDQuerySet::CommitRow(size_t index)
	{
		if((index >= 0) && (index < m_arrPtrRecords.size()))
		{
			return m_arrPtrRecords.at(index)->CommitAll();
		}else{
			return 0;
		};
	};
	//!Get the table collection pointer
	SQDRecordCollection * SQDQuerySet::GetRecordCollPtr(void)
	{
		return &m_arrPtrRecords;
	};

	//!Returns the table at the desired index
	SQDRecord * SQDQuerySet::AtRecord(size_t index)
	{
		if((index >= 0) && (index < m_arrPtrRecords.size()))
		{
			return m_arrPtrRecords.at(index);
		}else{
			return NULL;
		};
	};
	//!Returns the number of records in the table
	size_t SQDQuerySet::CountRecords(void)
	{
		return m_arrPtrRecords.size();
	};
	size_t SQDQuerySet::Size(void)
	{
		return m_arrPtrRecords.size();
	};
	//!Gets the number of columns in the set
	size_t SQDQuerySet::CountColumns (void)
	{
		if(m_arrPtrRecords.size() > 0)
		{
			return m_arrPtrRecords.at(0)->CountFields();
		};
		return 0;
	};
	//!Gets the specified column name
	std::string SQDQuerySet::GetColumnName (int index)
	{
		std::string strTemp;
		if(m_arrPtrRecords.size() > 0)
		{
			SQDRecord* ptrRec = m_arrPtrRecords.at(0);
			strTemp = ptrRec->GetFieldName(index);
		}else{
			if((index >= 0)&&(index	< m_arrPtrRecords.size()))
			{
				m_arrStrColNames.at(index);
			};
		};
		return strTemp;
	};
	//!Get all column names 
	std::vector<std::string> SQDQuerySet::GetColumnNames (void)
	{
		size_t i, UboundI;
		std::vector<std::string> arrNames;
		std::string strTemp;
		if(m_arrPtrRecords.size() > 0)
		{
			SQDRecord* ptrRec = m_arrPtrRecords.at(0);
			UboundI = ptrRec->CountFields();
			for(i = 0; i < UboundI;i++)
			{
				strTemp = ptrRec->GetFieldName(i);
				arrNames.push_back(strTemp);
			};
		}else{
			return m_arrStrColNames;
		};
		return arrNames;
	};

	//!Get the first table in the collection iterator
	SQDRecordIterator SQDQuerySet::BeginRecord(void)
	{
		m_ptrCursor = m_arrPtrRecords.begin();
		return m_ptrCursor;
	};
	//!Get the last table in the collection iterator
	SQDRecordIterator SQDQuerySet::EndRecord(void)
	{
		if(m_arrPtrRecords.size() > 0)
		{
			if(m_ptrCursor != m_arrPtrRecords.end())
			{
				m_ptrCursor = m_arrPtrRecords.end();
				--m_ptrCursor;
				return m_ptrCursor;
			};
		}else{
			//no elements go to the beginning instead
			m_ptrCursor = m_arrPtrRecords.begin();
		};
		return m_ptrCursor;
	};
	//!Get the next record in the list
	SQDRecordIterator SQDQuerySet::NextRecord(void)
	{
		if(m_ptrCursor != m_arrPtrRecords.end())
		{
			++m_ptrCursor;
		};
		return m_ptrCursor;
	};
	//!Get the current cursor
	SQDRecordIterator SQDQuerySet::GetCursor(void)
	{
		return m_ptrCursor;
	};

	//!Create a Record with the supplied table definition
	SQDRecord * SQDQuerySet::CreateRecord()
	{
		SQDRecord* ptrNew = new SQDRecord();
		ptrNew->Set_ptrDatabase(this->m_ptrDatabase);
		ptrNew->Set_strTableName(this->m_strTableName);
		ptrNew->Set_blnNewRecord(true);//flag it as a new record
		size_t i, intNumFields;
		intNumFields = this->m_arrStrColNames.size();

		for(i = 0; i < intNumFields; i++)
		{
			ptrNew->CreateField(m_arrStrColNames.at(i),SQL_STRING);
		};
		this->m_arrPtrRecords.push_back(ptrNew);
		return ptrNew;
	};
	//!Create a Table with the supplied table definition
	int SQDQuerySet::InsertRecord(SQDRecord * ptrRec)
	{
		ptrRec->Set_ptrDatabase(this->m_ptrDatabase);
		ptrRec->Set_strTableName(this->m_strTableName);
		this->m_arrPtrRecords.push_back(ptrRec);
		return 1;
	};

	//The Deletes destroy the records in the LOCAL COPY ONLY
	//!Delete the table with the provided name
	int SQDQuerySet::DeleteRecord(size_t index)
	{
		if((index >= 0)&&(index < m_arrPtrRecords.size()))
		{
			m_arrPtrRecords.at(index)->Set_blnDeleteRecord(true);
			return 1;
		}
		return 0;
	};
	//!Delete all of the tables
	int SQDQuerySet::DeleteAllRecords(void)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrRecords.size();
		for(i = 0; i < UboundI; i++)
		{
			m_arrPtrRecords.at(i)->Set_blnDeleteRecord(true);
		};//end loop i	
		return 1;
	};
	//The Deletes destroy the records in the LOCAL COPY ONLY
	//!Delete the table with the provided name
	int SQDQuerySet::UnDeleteRecord(size_t index)
	{
		if((index >= 0)&&(index < m_arrPtrRecords.size()))
		{
			m_arrPtrRecords.at(index)->Set_blnDeleteRecord(false);
			return 1;
		}
		return 0;
	};
	//!Delete all of the tables
	int SQDQuerySet::UnDeleteAllRecords(void)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrRecords.size();
		for(i = 0; i < UboundI; i++)
		{
			m_arrPtrRecords.at(i)->Set_blnDeleteRecord(false);
		};//end loop i	
		return 1;
	};


	//The Remove destroy the records in the LOCAL COPY ONLY
	//!Remove the Record with the provided index
	int SQDQuerySet::RemoveRecord(size_t index)
	{
		if((index >= 0)&&(index < m_arrPtrRecords.size()))
		{
			delete m_arrPtrRecords.at(index);
			m_arrPtrRecords.erase(m_arrPtrRecords.begin() + index);
			return 1;
		}
		return 0;
	};
	//!Delete all of the tables
	int SQDQuerySet::RemoveAllRecords(void)
	{
		size_t i, UboundI;
		std::string strTemp;
		UboundI = m_arrPtrRecords.size();
		for(i = 0; i < UboundI; i++)
		{
			delete m_arrPtrRecords.at(i);
		};//end loop i	
		m_arrPtrRecords.clear();
		return 1;
	};
	//The DeleteCommits destroy the records IN THE DATABASE
	//!Delete the table with the provided name
	int SQDQuerySet::DeleteCommitRecord(size_t index)
	{
		//SQL Statement assumes field 0 is the guid key for the table
		//DELETE FROM table_name WHERE key=some_value;
		if(!m_ptrDatabase){return 0;};
		char *zErrMsg = 0;

		if((index >=0) && (index < m_arrPtrRecords.size()))
		{
			std::stringstream strDel;
			SQDField* ptrKey = m_arrPtrRecords.at(index)->AtField(0);
			if(ptrKey)
			{
				strDel << "DELETE FROM " << m_strTableName.c_str() <<
					"WHERE " << ptrKey->Get_strName().c_str() <<
					" = '" << ptrKey->Get_strValue().c_str() << "'";
				sqlite3_exec(m_ptrDatabase->Get_ptrDB(),strDel.str().c_str(),NULL,NULL,&zErrMsg);
			}

			this->RemoveRecord(index);
			return 1;
		};
		return 0;
	};
	//!Delete all of the tables
	int SQDQuerySet::DeleteCommitAllRecords(void)
	{
		size_t i, UboundI;
		std::stringstream strDel;
		char *zErrMsg = 0;
		strDel << "DELETE FROM " << m_strTableName.c_str() ;
		sqlite3_exec(m_ptrDatabase->Get_ptrDB(),strDel.str().c_str(),NULL,NULL,&zErrMsg);
		//now clear the in memory 
		this->RemoveAllRecords();
		return 1;
	};
};//end namespace SQD
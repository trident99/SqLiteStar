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

#ifndef SQDQuerySet_H
#define SQDQuerySet_H
#include ".\modLibRefs.h"
#include ".\modMemVarMacros.h"
#include ".\SQDRecord.h"

namespace SQD
{
	typedef std::vector<SQDRecord*>::iterator SQDRecordIterator;

	typedef std::vector<SQDRecord*> SQDRecordCollection;

	//!Forward declaration of database
	class SQD_DLLAPI SQDDatabase;

	/*!SQDQuerySet is a wrapper around the query exec() and prepare() functionality in SQLite3.
	* It will handle any SQL statement and will provide RecordSet access to data as the result of a SELECT statement.
	*BEST PRACTICE!!!
	*ALWAYS include rowid as the first column of any SELECT statement.
	*example:  SELECT rowid,* FROM strTableName
	*If you don't specifically ask for rowid SQLite doesn't give it to you and you have no way of saving your changes
	*to the rows that you have edited.
	*ASSUMPTION:
	*This class assumes the first column of the recordset is the PRIMARY KEY for record identification.
	*If you forgot rowid, your changes might not be saved correctly.
	*/
	//!SQDQuerySet is a wrapper around the query exec() and prepare() functionality in SQLite3.
	class SQD_DLLAPI SQDQuerySet
	{
	public:
		//!Void constructor
		SQDQuerySet();
		//!Copy constructor
		SQDQuerySet(SQDQuerySet & rhs);
		//!Void destructor
		virtual ~SQDQuerySet();
		//PUBLIC OPERATOR OVERLOADS
		//!Assignment Operator
		SQDQuerySet & operator = (SQDQuerySet & rhs);

		//!The string query to be executed
		HTLMEMVAR_BYVAL_STYLE1(public,std::string,strQuery)
		//!The integer code query result
		HTLMEMVAR_BYVAL_STYLE1(public,int,intResult)

		//!The string user name
		HTLMEMVAR_BYVAL_STYLE1(public, std::string, strTableName)
		//!The pointer to the native sqlite3 statement object
		HTLMEMVAR_BYVAL_STYLE1(public, sqlite3_stmt *, ptrStatement)

		//!Database Accessors
		void Set_ptrDatabase(SQDDatabase* ptrDB);
		SQDDatabase* Get_ptrDatabase(void);
		//!Promulgate table name to all records.  This is important to do before trying commits.
		//Execute does this automatically at the end of a query recordset build.
		void Set_AllTableNames(std::string strTableName);
		//!Promulgate database pointer to all records.  This is important to do before trying commits.
		//Execute does this automatically at the end of a query recordset build.
		void Set_AllDatabasePtrs(SQDDatabase* ptrDB);
		//!Executes the SQL Call to the database
		int Execute(void);
		//!Update All Records from the Database to the Recordset
		//This calls an sqlite3 reset function before executing the query again.
		int UpdateAll(void);
		//!Update Row from the Database to the Recordset
		int UpdateRow(size_t intRow);

		//!Commit All Changes to the database
		int CommitAll(void);
		//!Commit Row Changes to the database
		int CommitRow(size_t index);
		//!Get the recordset collection pointer
		SQDRecordCollection * GetRecordCollPtr(void);

		//!Returns the record at the desired index
		SQDRecord * AtRecord(size_t index);
		//!Returns the number of records in the recordset
		size_t CountRecords(void);
		size_t Size(void);
		//!Gets the number of columns in the recordset
		size_t CountColumns (void);
		//!Gets the specified column name
		std::string GetColumnName (int index);
		//!Get all column names 
		std::vector<std::string> GetColumnNames (void);

		//!Get the first record in the collection iterator
		SQDRecordIterator BeginRecord(void);
		//!Get the last record in the collection iterator
		SQDRecordIterator EndRecord(void);
		//!Get the next record in the list
		SQDRecordIterator NextRecord(void);
		//!Get the current cursor iterator
		SQDRecordIterator GetCursor(void);

		//!Create a Record with the supplied table definition
		SQDRecord * CreateRecord();
		//!Create a Record with the supplied record definition
		int InsertRecord(SQDRecord * ptrRec);

		//!Mark a Record for Deletion = TRUE
		int DeleteRecord(size_t index);
		//!Mark all Records for Deletion = TRUE
		int DeleteAllRecords(void);
		//!Mark a Record for Deletion = FALSE
		int UnDeleteRecord(size_t index);
		//!Mark all Records for Deletion = FALSE
		int UnDeleteAllRecords(void);
		//The Remove destroys the records in the LOCAL COPY ONLY, NOT THE DATABASE
		//!Delete the record with the provided index
		int RemoveRecord(size_t index);
		//!Delete all of the records
		int RemoveAllRecords(void);
		//The DeleteCommits destroy the records IN THE DATABASE
		//!Delete the record with the provided index
		int DeleteCommitRecord(size_t index);
		//!Delete all of the records
		int DeleteCommitAllRecords(void);
	protected:
		//!Vector of the Column Names
		std::vector<std::string> m_arrStrColNames;
		//!The pointer to the database object
		SQDDatabase* m_ptrDatabase;
		//!Cursor pointer in the record set
		SQDRecordIterator m_ptrCursor;
		//!The collection of records
		SQDRecordCollection m_arrPtrRecords;
	};//end class SQDQuerySet
};//end namespace SQD

#endif //SQDQuery_H
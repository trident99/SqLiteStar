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

#ifndef SQDRecord_H
#define SQDRecord_H
#include ".\modLibRefs.h"
#include ".\modMemVarMacros.h"
#include ".\SQDField.h"

namespace SQD
{
	typedef std::vector<SQDField*>::iterator SQDFieldIterator;

	typedef std::vector<SQDField*> SQDFieldCollection;
	//!Forward declaration of database
	class SQDDatabase;

	/*!
	*SQDRecord is a container that holds one record of a query and contains fields of data.
	*Each Record contains a list of the column names as well as the collection of SQDFields
	*for that record.  It also contains conveinience accessor functions for fields as well
	*as the ability of comitting changes back to the database.
	*/
	//!SQDRecord is a container that holds one record of a query and contains fields of data.

	class SQD_DLLAPI SQDRecord
	{
	public:
		//!Void constructor
		SQDRecord();
		//!Copy constructor
		SQDRecord(SQDRecord & rhs);
		//!virtual void destructor
		virtual ~SQDRecord();
		//PUBLIC OPERATOR OVERLOADS
		//!Assignment operator
		SQDRecord & operator = (SQDRecord & rhs);

	public:			
		//!Boolean Flag for New Record
		HTLMEMVAR_BYVAL_STYLE1(public,bool,blnNewRecord);
		//!Boolean Flag for Delete Record
		HTLMEMVAR_BYVAL_STYLE1(public,bool,blnDeleteRecord);
		//!Boolean Flag for whether the Record was Modified or Edited
		HTLMEMVAR_BYVAL_STYLE1(public,bool,blnModified);
		//!String Table Name this record belongs to
		HTLMEMVAR_BYVAL_STYLE1(public,std::string,strTableName)
		//!The pointer to the database object
		HTLMEMVAR_BYVAL_STYLE1(public,SQDDatabase*,ptrDatabase)
	public:
		//DB====>Active Memory
		//Updates all fields 
		int UpdateAll(void);
		//!Update the value for the selected field
		int UpdateField(size_t index);

		//Active Memory====>DB
		//!Commit all values for all fields
		int CommitAll(void);
		//!Commit the value of the selected field to the database
		int CommitField(size_t index);

		//!Get the field collection pointer
		SQDFieldCollection * GetFieldCollPtr(void);

		//CONTAINER ACCESSORS FOR TABLE COLLECTION
		//!Does the Table with strName Exist
		bool DoesFieldExist(std::string strName);
		//!Does the Table with strName Exist
		SQDField * GetField(std::string strName);
		//!Gets the field index number
		int GetFieldLoc(std::string strName);
		//!Returns the table at the desired index
		SQDField * AtField(size_t index);
		//!Returns the number of fields in the record
		int CountFields(void);
		//!Returns the 
		int Size(void);
		//!Get the FieldName at the index
		std::string GetFieldName(size_t index);

		//!Get the first table in the collection iterator
		SQDFieldIterator BeginField(void);
		//!Get the last table in the collection iterator
		SQDFieldIterator EndField(void);
		//!Get the next field iterator
		SQDFieldIterator NextField(void);
		//!Get the cursor directly
		SQDFieldIterator GetCursor(void);
		//!Create a Table with the supplied table definition
		SQDField * CreateField(std::string strName, SQDFieldType enmType);
		//!Delete the table with the provided name
		int DeleteField(std::string strName);
		//!Delete all of the tables
		int DeleteAllFields(void);

	protected:
		//!The cursor of the current field
		SQDFieldIterator m_ptrCursor;
		//!The collection of fields
		SQDFieldCollection m_arrPtrFields;

	private:
		//!Commit a Modfied Record that already exists
		int CommitModifiedRecord(void);
		//!Commit a New Record
		int CommitNewRecord(void);
		//!Delete a Record
		int CommitDeleteRecord(void);


	};//end class SQDRecord

};//end namespace SQD
#endif//end SQDRecord_H
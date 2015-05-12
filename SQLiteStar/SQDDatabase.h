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

#ifndef SQDDatabase_H
#define SQDDatabase_H
#include ".\modLibRefs.h"
#include ".\modMemVarMacros.h"
//#include ".\SQDRecord.h"
#include <vector>
using namespace std;

namespace SQD
{
	/*The SQDDatabase class is a wrapper around the SQLite3 native database pointer.
	*It provides Open Close status and file path information.
	*/
	//!The SQDDatabase class is a wrapper around the SQLite3 native database pointer.
	class SQD_DLLAPI SQDDatabase
	{
	public:
		//void constructor
		SQDDatabase();
		//void destructor
		~SQDDatabase();

	public:
    	public:
		//!The string user name
		HTLMEMVAR_BYVAL_STYLE1(public,std::string,strUserName)
		//!The string password
		HTLMEMVAR_BYVAL_STYLE1(public,std::string,strPassword)
		//!The string database path name
		HTLMEMVAR_BYVAL_STYLE1(public,std::string,strDBPathName)
		//!The integer port number
		HTLMEMVAR_BYVAL_STYLE1(public,int,intPort)
        //!Boolean flage for is open		
		HTLMEMVAR_BYVAL_STYLE1(public,bool,blnIsOpen)
		//!The string last error
		HTLMEMVAR_BYVAL_STYLE1(public,std::string,strError)

        //MEMBER FUNCTIONS//////////////////////////
	public:
        //!Get the pointer to the RAW DATABASE
        sqlite3* Get_ptrDB(void);

        //!Open the database connection
        int OpenDB(void);
        //!Close the database Connection
        int CloseDB(void);
        //!Returns if the database is open
        bool IsOpen(void);
		//!Returns a list of table names for the database.
		std::vector<std::string> GetTableNames(void);
	protected:
        //!The pointer to the actual SQLite Database
        sqlite3* m_ptrDB;

	};//end class SQDDatabase
};//end namespace SQD

#endif //SQDQuery_H
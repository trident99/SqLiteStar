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


#include <QtWidgets\QFileDialog>

#include "SQLiteViewer.h"
#include "QFieldEditDialog.h"

SQLiteViewer::SQLiteViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_ptrTableNamesModel = NULL;
	m_ptrQuerySetModel = NULL;

	InitializeActions();
	InitializeMenu();
	InitializeControls();
}

SQLiteViewer::~SQLiteViewer()
{

}


//!Initialize the Actions of the GUI
void SQLiteViewer::InitializeActions(void)
{
	connect(ui.cmdShowTable,SIGNAL(clicked()),this,SLOT(OnShowTable_Click()));
	connect(ui.cmdHideTable,SIGNAL(clicked()),this,SLOT(OnHideTable_Click()));
	connect(ui.cmdUpdateAll,SIGNAL(clicked()),this,SLOT(OnUpdateAll_Click()));
	connect(ui.cmdCommitAll,SIGNAL(clicked()),this,SLOT(OnCommitAll_Click()));

	connect(ui.cmdAddRecord,SIGNAL(clicked()),this,SLOT(OnAddRecord_Click()));
	connect(ui.cmdDeleteRecord,SIGNAL(clicked()),this,SLOT(OnDeleteRecord_Click()));
	connect(ui.cmdDeleteAllRecords,SIGNAL(clicked()),this,SLOT(OnDeleteAllRecords_Click()));
	connect(ui.cmdUnDeleteRecord,SIGNAL(clicked()),this,SLOT(OnUnDeleteRecord_Click()));
	connect(ui.cmdUnDeleteAllRecords,SIGNAL(clicked()),this,SLOT(OnUnDeleteAllRecords_Click()));

	connect(ui.tblRecords,SIGNAL(doubleClicked ( const QModelIndex & )),this,SLOT(OnEditField_DoubleClick(const QModelIndex & )));

};
//!Initialize the Controls
void SQLiteViewer::InitializeControls(void)
{
	if(!m_ptrTableNamesModel)
	{
		m_ptrTableNamesModel= new QStringListModel(ui.lstTableNames);
	};
	ui.lstTableNames->setModel(m_ptrTableNamesModel);
	connect(ui.lstTableNames,SIGNAL(clicked(const QModelIndex &)),this,SLOT(OnSelectTable(const QModelIndex &)));

	if(!m_ptrQuerySetModel)
	{
		m_ptrQuerySetModel= new QQuerySetModel(ui.tblRecords);
	};
	ui.tblRecords->setModel(m_ptrQuerySetModel);
	ui.tblRecords->horizontalHeader()->setVisible(true);
};
//!Initialize the Menu
void SQLiteViewer::InitializeMenu(void)
{
	connect(ui.actionOpen_DB,SIGNAL(triggered()),this,SLOT(OnFileOpen()));
	connect(ui.actionClose_DB,SIGNAL(triggered()),this,SLOT(OnFileClose()));

	connect(ui.actionCreate_DemoDB01,SIGNAL(triggered()),this,SLOT(OnCreateDemoDB01()));
	connect(ui.actionCreate_DemoDB02,SIGNAL(triggered()),this,SLOT(OnCreateDemoDB02()));
	connect(ui.actionCreate_DemoDB03,SIGNAL(triggered()),this,SLOT(OnCreateDemoDB03()));
};

//!On File Open Slot
void SQLiteViewer::OnFileOpen(void)
{
	int intRet;
	QString strFile = QFileDialog::getOpenFileName(this,
         tr("Open SQLite File"), "", tr(("SQL (*.sql *.sq3);; All files (*.*)")) );
	std::string strFullPathName;
	if(!strFile.isEmpty())
	{
		strFullPathName = strFile.toStdString();

		this->m_objSqlDB.Set_strDBPathName(strFullPathName);
		intRet = this->m_objSqlDB.OpenDB();
		//gather the table names
		std::vector<std::string> arrStrTableNames;
		arrStrTableNames = m_objSqlDB.GetTableNames();
		QStringList qstrList;
		size_t i, UboundI;
		UboundI = arrStrTableNames.size();
		for(i = 0 ; i < UboundI;i++)
		{
			qstrList.push_back(arrStrTableNames.at(i).c_str());
		}
		//set the tablenames to the model for display
		this->m_ptrTableNamesModel->setStringList(qstrList);
	};
	return;
};
//!OnFileClose Slot
void SQLiteViewer::OnFileClose(void)
{
	this->m_objSqlDB.CloseDB();

	//clear the table names
	QStringList qEmpty;
	if(m_ptrTableNamesModel)
	{
	this->m_ptrTableNamesModel->setStringList(qEmpty);
	};

	if(m_ptrQuerySetModel)
	{
		m_ptrQuerySetModel->Set_ptrQuerySet(NULL);
		m_ptrQuerySetModel->update();
	};
	//clear the recordset table
};
//!OnShowTable
void SQLiteViewer::OnShowTable_Click(void)
{
	int intRes;
	std::stringstream strCom;
	strCom << "SELECT rowid,* FROM  " << m_strSelTableName.toStdString().c_str();
	m_objQuery.Set_ptrDatabase(&m_objSqlDB);
	m_objQuery.Set_strQuery(strCom.str());
	intRes = m_objQuery.Execute();
	if(intRes >= 0)
	{
		m_objQuery.Set_AllTableNames(m_strSelTableName.toStdString());
		m_ptrQuerySetModel->Set_ptrQuerySet(&m_objQuery);		
	};

};

//!OnHideTable slot
void SQLiteViewer::OnHideTable_Click(void)
{
	if(m_ptrQuerySetModel)
	{
		m_ptrQuerySetModel->Set_ptrQuerySet(NULL);
		m_ptrQuerySetModel->update();
	};	

};

//!Update All Records for the selected table
void SQLiteViewer::OnUpdateAll_Click(void)
{
	m_objQuery.UpdateAll();
	if(m_ptrQuerySetModel)
	{
		m_ptrQuerySetModel->update();
	}
};
//!Commit All Records for the selected table
void SQLiteViewer::OnCommitAll_Click(void)
{
	m_objQuery.CommitAll();
	if(m_ptrQuerySetModel)
	{
		m_ptrQuerySetModel->update();
	}
};

void SQLiteViewer::OnEditField_DoubleClick(const QModelIndex & index )
{
	if(m_ptrQuerySetModel)
	{
		SQD::SQDField* ptrField = m_ptrQuerySetModel->GetFieldPtr(index.row(),index.column());
		if(ptrField)
		{
			QFieldEditDialog objEdit;
			QString strVal;
			strVal = ptrField->Get_strValue().c_str();
			objEdit.Set_strFieldValue(strVal);
			if(objEdit.exec())
			{
				ptrField->Set_strValue(objEdit.Get_strFieldValue().toStdString());
				SQD::SQDRecord* ptrParent = ptrField->Get_ptrParent();
				if(ptrParent)
				{
					ptrParent->Set_blnModified(true);
					m_ptrQuerySetModel->updateVerticalHeaders();
				}//end parent record check
			}//end popup dialog execute
		}//end Field check
	}//end model pointer check
};


void SQLiteViewer::OnAddRecord_Click(void)
{
	if(m_ptrQuerySetModel)
	{
		SQD::SQDRecord* ptrNew = m_objQuery.CreateRecord();
		m_ptrQuerySetModel->update();
	}
};

void SQLiteViewer::OnDeleteRecord_Click(void)
{
	QItemSelectionModel* ptrSelModel = ui.tblRecords->selectionModel();
	if((ptrSelModel)&&(m_ptrQuerySetModel))
	{
		QModelIndex objSel = ptrSelModel->currentIndex();
		m_objQuery.DeleteRecord(objSel.row() );
		m_ptrQuerySetModel->updateVerticalHeaders();
	};
};

void SQLiteViewer::OnDeleteAllRecords_Click(void)
{
	if(m_ptrQuerySetModel)
	{
		m_objQuery.DeleteAllRecords();
		m_ptrQuerySetModel->updateVerticalHeaders();
	};
};

void SQLiteViewer::OnUnDeleteRecord_Click(void)
{
	QItemSelectionModel* ptrSelModel = ui.tblRecords->selectionModel();
	if((ptrSelModel)&&(m_ptrQuerySetModel))
	{
		QModelIndex objSel = ptrSelModel->currentIndex();
		m_objQuery.UnDeleteRecord(objSel.row() );
		m_ptrQuerySetModel->updateVerticalHeaders();
	};
};

void SQLiteViewer::OnUnDeleteAllRecords_Click(void)
{
	if(m_ptrQuerySetModel)
	{
		m_objQuery.UnDeleteAllRecords();
		m_ptrQuerySetModel->updateVerticalHeaders();
	};
};


void SQLiteViewer::OnCreateDemoDB01(void)
{
	int intRes;
	std::string strDBName = ".\\TestDB01.sql";
	m_objSqlDB.Set_strDBPathName(strDBName);
	intRes = m_objSqlDB.OpenDB();
	std::stringstream strTable01;

	//CREATE TABLE database_name.table_name(
	//column1 datatype  PRIMARY KEY(one or more columns),
	// column2 datatype,
	//column3 datatype,
	//.....
	//columnN datatype,
	//);
	char * zErrMsg = NULL;
	strTable01 << "CREATE TABLE tblContactInfo(" << 
				"ID INT PRIMARY KEY," <<
				"strName TEXT, " <<
				"strAddress TEXT, " <<
				"intAge INT, " <<
				"chrGender VARCHAR(10), " <<
				"strCareer VARCHAR(50) " << ");" ;

	intRes = sqlite3_exec(m_objSqlDB.Get_ptrDB(),strTable01.str().c_str(),NULL,NULL,&zErrMsg);

};

void SQLiteViewer::OnCreateDemoDB02(void)
{
		int intRes;
	std::string strDBName = ".\\TestDB02.sql";
	m_objSqlDB.Set_strDBPathName(strDBName);
	intRes = m_objSqlDB.OpenDB();
	std::stringstream strTable01,strTable02, strTable03;

	//CREATE TABLE database_name.table_name(
	//column1 datatype  PRIMARY KEY(one or more columns),
	// column2 datatype,
	//column3 datatype,
	//.....
	//columnN datatype,
	//);
	char * zErrMsg = NULL;
	strTable01 << "CREATE TABLE tblContactInfo(" << 
				"ID INT PRIMARY KEY," <<
				"strName TEXT, " <<
				"strAddress TEXT, " <<
				"intAge INT, " <<
				"chrGender VARCHAR(10), " <<
				"strCareer VARCHAR(50) " << ");" ;

	intRes = sqlite3_exec(m_objSqlDB.Get_ptrDB(),strTable01.str().c_str(),NULL,NULL,&zErrMsg);

	strTable02 << "CREATE TABLE tblTableString(" << 
				"ID INT PRIMARY KEY," <<
				"strOne TEXT, " <<
				"strTwo TEXT, " <<
				"intOne INT, " <<
				"strThree VARCHAR(10), " <<
				"strFour VARCHAR(50) " << ");" ;

	intRes = sqlite3_exec(m_objSqlDB.Get_ptrDB(),strTable02.str().c_str(),NULL,NULL,&zErrMsg);

	strTable03 << "CREATE TABLE tblNameValPair(" << 
				"ID INT PRIMARY KEY," <<
				"strOne TEXT, " <<
				"sngVal REAL, " <<
				"intVal INT" <<");" ;

	intRes = sqlite3_exec(m_objSqlDB.Get_ptrDB(),strTable03.str().c_str(),NULL,NULL,&zErrMsg);

};

void SQLiteViewer::OnCreateDemoDB03(void)
{

};

void SQLiteViewer::OnSelectTable(const QModelIndex & index)
{
	m_strSelTableName =	m_ptrTableNamesModel->data(index,0).toString();
};

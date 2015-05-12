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


#ifndef SQLITEVIEWER_H
#define SQLITEVIEWER_H

#include "modLibRefs.h"
#include "QQuerySetModel.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets\QMainWindow>
#include <QStringListModel>


#include "ui_SQLiteViewer.h"



class SQLiteViewer : public QMainWindow
{
	Q_OBJECT

public:
	SQLiteViewer(QWidget *parent = 0);
	~SQLiteViewer();

	//!Initialize the Actions of the GUI
	void InitializeActions(void);
	//!Initialize the Controls
	void InitializeControls(void);
	//!Initialize the 
	void InitializeMenu(void);


	public slots:
		//!On File Open Slot
		void OnFileOpen(void);
		//!OnFileClose Slot
		void OnFileClose(void);
		//!OnShowTable slot
		void OnShowTable_Click(void);
		//!OnHideTable slot
		void OnHideTable_Click(void);
		//!Update All Records for the selected table
		void OnUpdateAll_Click(void);
		//!Commit All Records for the selected table
		void OnCommitAll_Click(void);
		//!Creates Blank Demonstration Database01
		void OnCreateDemoDB01(void);
		//!Creates Blank Demonstration Database02
		void OnCreateDemoDB02(void);
		//!Creates Blank Demonstration Database03
		void OnCreateDemoDB03(void);
		//!Select the Table and 
		void OnSelectTable(const QModelIndex & index);
		
		//! Add Record Event Handler
		void OnAddRecord_Click(void);
		//!Delete Record Event Handler
		void OnDeleteRecord_Click(void);
		//!UnDelete All Records Event Handler
		void OnDeleteAllRecords_Click(void);
		//!UnDeleteRecord Event Handler
		void OnUnDeleteRecord_Click(void);
		//!UnDelete All Records Event Handler
		void OnUnDeleteAllRecords_Click(void);
		//!Edit individual field event handler
		void OnEditField_DoubleClick(const QModelIndex & index );

private:
	Ui::SQLiteViewerClass ui;
	//!String List Model for the 
	SQD::SQDDatabase m_objSqlDB;
	//!Table Names List
	QStringListModel * m_ptrTableNamesModel;
	//!RecordSet Model Interface for the Table View
	QQuerySetModel * m_ptrQuerySetModel;
	//!Query Object
	SQD::SQDQuerySet m_objQuery;
	//!The string name of the selected table
	QString m_strSelTableName;

};

#endif // SQLITEVIEWER_H

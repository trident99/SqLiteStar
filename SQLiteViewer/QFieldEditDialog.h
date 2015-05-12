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


#ifndef QFIELDEDITDIALOG_H
#define QFIELDEDITDIALOG_H

#include <QtWidgets\QDialog>
#include "ui_QFieldEditDialog.h"

class QFieldEditDialog : public QDialog
{
	Q_OBJECT

public:
	QFieldEditDialog(QWidget *parent = 0);
	~QFieldEditDialog();
	//!Initialize the Dialog's controls and signals / slots
	void InitializeDialog(void);
	
	//!Accessor functions for Field Value
	QString Get_strFieldValue(void);
	void Set_strFieldValue(QString & strVal);

	public slots:
	//!Event handler for OK click
	void OnOK_Click(void);
	//!Event handler for Cancel Click
	void OnCancel_Click(void);

protected:
	//!The String value displayed
	QString m_strFieldValue;

private:
	Ui::QFieldEditDialogClass ui;
};

#endif // QFIELDEDITDIALOG_H

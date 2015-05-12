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


#include "QFieldEditDialog.h"

QFieldEditDialog::QFieldEditDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	InitializeDialog();
}

QFieldEditDialog::~QFieldEditDialog()
{
	m_strFieldValue.clear();
}

void QFieldEditDialog::InitializeDialog(void)
{
	connect(ui.cmdOK, SIGNAL(clicked()),this,SLOT(OnOK_Click()));
	connect(ui.cmdCancel, SIGNAL(clicked()),this,SLOT(OnCancel_Click()));
};

QString QFieldEditDialog::Get_strFieldValue(void)
{
	return m_strFieldValue;
};

void QFieldEditDialog::Set_strFieldValue(QString & strVal)
{
	m_strFieldValue = strVal;
	ui.txtField->setText(strVal);
	return;
};

void QFieldEditDialog::OnOK_Click(void)
{
	m_strFieldValue = ui.txtField->toPlainText();
	this->accept();
};
void QFieldEditDialog::OnCancel_Click(void)
{
	this->reject();
};
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

#ifndef QRecordSetModel_H
#define QRecordSetModel_H

#include ".\modLibRefs.h"
#include <QAbstractItemModel.h>
#include <QAbstractTableModel>

 class QQuerySetModel : public QAbstractTableModel
 {
     Q_OBJECT

 public:
	 QQuerySetModel();
     QQuerySetModel(QObject *parent = 0);
     ~QQuerySetModel();
	 //QT Override Methods REQUIRED for QAbstractItemModel
	 //!Gets the data of the cell at the index supplied
     QVariant data(const QModelIndex &index, int role) const;
	 //!Gets the item flags of the cell at the index supplied
     Qt::ItemFlags flags(const QModelIndex &index) const;
	 //!Gets the header data of the cell at the index supplied in the orientation desired.
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
	 //!Sets the header data to the value supplied
	 bool setHeaderData(int section, Qt::Orientation orientation,
                                   const QVariant &value, int role);
	 //!Gets the QModelIndex at the row and column of the parent cell
	 QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
	 //!Gets the parent model cell index. In this case it is always QModelIndex()
     QModelIndex parent(const QModelIndex &index) const;
	 //!Gets the number of rows in the model
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
	 //!Gets the number of columns in the model
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

	 //!Accessor functions for the queryset model
	 void Set_ptrQuerySet( SQD::SQDQuerySet* ptrSet);
	 SQD::SQDQuerySet* Get_ptrQuerySet(void);
	 //!Get the field pointer for the selected row and column
	 SQD::SQDField * GetFieldPtr(int row, int column);
	 //!Get the record pointer for the selected row
	 SQD::SQDRecord * GetRecordPtr(int row);
	 public slots:
	 //!Triggers full model reset
	 void update(void);
	 //!Triggers a full horizontal header refresh
	 void updateHorizontalHeaders(void);
	 //!Triggers a full vertical header refresh
	 void updateVerticalHeaders(void);

 private:
	 //!Pointer to the Actual Query Set
     SQD::SQDQuerySet * m_ptrQuerySet;
 };



#endif
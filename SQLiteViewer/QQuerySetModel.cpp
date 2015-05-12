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

 #include ".\QQuerySetModel.h"

QQuerySetModel::QQuerySetModel()
	: QAbstractTableModel(NULL)
{
	m_ptrQuerySet = NULL;
};

 QQuerySetModel::QQuerySetModel(QObject *parent)
     : QAbstractTableModel(parent)
 {
	m_ptrQuerySet = NULL;
 }

 QQuerySetModel::~QQuerySetModel()
 {
	 m_ptrQuerySet = NULL;
 }



 int QQuerySetModel::rowCount(const QModelIndex &parent) const
 {
	 if(m_ptrQuerySet)
	 {
		 return m_ptrQuerySet->CountRecords();
	 }else{
		 return 0;
	 }
 }


 int QQuerySetModel::columnCount(const QModelIndex &parent) const
 {
	 if(m_ptrQuerySet)
	 {
		 int i = m_ptrQuerySet->CountColumns();
		 return i;
	 }else{
		 return 0;
	 };
	 return 0;
 }

 QVariant QQuerySetModel::data(const QModelIndex &index, int role) const
 {
	 if(!m_ptrQuerySet){return QVariant();};

     if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
		 return QVariant();

	 int intRow, intCol;
	 intRow = index.row(); intCol = index.column();
	 if(m_ptrQuerySet)
	 {
		 SQD::SQDRecord* ptrRec = m_ptrQuerySet->AtRecord(intRow);
		 if(ptrRec)
		 {
			 SQD::SQDField * ptrField = ptrRec->AtField(intCol);
			 if(ptrField)
			 {
				 std::string strTemp;
				 strTemp = ptrField->Get_strValue();
				 return strTemp.c_str();
			 }
		 }else{
			 return QVariant();
		 }//end record
	 }else{
		 return QVariant();
	 }//end recordset
	     
     return QVariant();
 }

 Qt::ItemFlags QQuerySetModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return 0;

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }

 QVariant QQuerySetModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
	 if(!m_ptrQuerySet){return QVariant();};

	 if(role != Qt::DisplayRole)
	 {
		return QVariant();
	 };

	 if(orientation == Qt::Horizontal)
	 {
		 if(m_ptrQuerySet)
		 {
			 std::string strTemp;
			 strTemp = m_ptrQuerySet->GetColumnName(section);
			 return strTemp.c_str();
		 }
	 }//end orientation
	 if(orientation == Qt::Vertical)
	 {
		//verticle, display the row number
		 QString strRow;
		 strRow.setNum(section);
		 SQD::SQDRecord* ptrRec = m_ptrQuerySet->AtRecord(section);
		 if(ptrRec)
		 {
			 if(ptrRec->Get_blnNewRecord()){strRow += '*';};
			 if(ptrRec->Get_blnModified()){strRow += '!';};
			 if(ptrRec->Get_blnDeleteRecord()){strRow += 'X';};
		 }
		 return strRow;
	 }//end orientation
     return QVariant();
 }

 bool QQuerySetModel::setHeaderData(int section, Qt::Orientation orientation,
                                   const QVariant &value, int role)
{
    emit headerDataChanged(orientation, section, section);
    return true;
}

 QModelIndex QQuerySetModel::index(int row, int column, const QModelIndex &parent)
             const
 {

     if (!hasIndex(row, column, parent))
         return QModelIndex();
	 if (m_ptrQuerySet)
	 {
		  SQD::SQDRecord* ptrRec = m_ptrQuerySet->AtRecord(row);
		 if(ptrRec)
		 {
			 SQD::SQDField * ptrField = ptrRec->AtField(column);
			 if(ptrField)
			 {
				 return createIndex(row, column, ptrField);
			 }
		 }else{
			 return QModelIndex();
		 }//end record

         return QModelIndex();
	 }else{
         return QModelIndex();
	 }//end recordset check
 }

 QModelIndex QQuerySetModel::parent(const QModelIndex &index) const
 {
	 return QModelIndex();
 }

 void QQuerySetModel::Set_ptrQuerySet( SQD::SQDQuerySet* ptrSet)
 {
	 if(ptrSet)
	 {
		 this->beginResetModel();
		 m_ptrQuerySet = ptrSet;
		 this->endResetModel();

		 emit headerDataChanged(Qt::Horizontal, 0, m_ptrQuerySet->CountColumns());
	 }else{
		 m_ptrQuerySet = NULL;
	 };
 };

 SQD::SQDQuerySet* QQuerySetModel::Get_ptrQuerySet(void)
 {
	 if(m_ptrQuerySet)
	 {
		 return m_ptrQuerySet;
	 }else{
		 return NULL;
	 }
 };

 SQD::SQDField * QQuerySetModel::GetFieldPtr(int row, int column)
 {
	if (m_ptrQuerySet)
	 {
		  SQD::SQDRecord* ptrRec = m_ptrQuerySet->AtRecord(row);
		 if(ptrRec)
		 {
			 SQD::SQDField * ptrField = ptrRec->AtField(column);
			 if(ptrField)
			 {
				 return ptrField;
			 }
		 }else{
			 return NULL;
		 }//end record

         return NULL;
	 }else{
         return NULL;
	 }//end recordset check

 };

 SQD::SQDRecord * QQuerySetModel::GetRecordPtr(int row)
 {
	 if (m_ptrQuerySet)
	 {
		  SQD::SQDRecord* ptrRec = m_ptrQuerySet->AtRecord(row);
		 if(ptrRec)
		 {
			 return ptrRec;
		 }else{
			 return NULL;
		 }//end record

         return NULL;
	 }else{
         return NULL;
	 }//end recordset check
 };



 void QQuerySetModel::update(void)
 {
	 this->beginResetModel();
	 this->endResetModel(); 
 };

 //!Triggers a full horizontal header refresh
 void QQuerySetModel::updateHorizontalHeaders(void)
 {
	 size_t i, intCols;
	 intCols = this->columnCount();
	 if(m_ptrQuerySet)
	 {
		 for(i = 0; i < intCols;i++)
		 {
			 QString strItem = m_ptrQuerySet->GetColumnName(i).c_str();
			 this->setHeaderData(i,Qt::Horizontal,strItem,Qt::DisplayRole);
		 };
	 };

 };
 //!Triggers a full vertical header refresh
 void QQuerySetModel::updateVerticalHeaders(void)
 {
	 size_t i, intRows;
	 SQD::SQDRecord * ptrCurrRec = NULL;
	 intRows = this->rowCount();
	 if(m_ptrQuerySet)
	 {
		 for(i = 0; i < intRows;i++)
		 {
			 QString strItem;
			 strItem.setNum(i);
			 ptrCurrRec = m_ptrQuerySet->AtRecord(i);
			 if(ptrCurrRec)
			 {
				 if(ptrCurrRec->Get_blnNewRecord()){strItem += "*";};
				 if(ptrCurrRec->Get_blnModified()){strItem += "!";};
				 if(ptrCurrRec->Get_blnDeleteRecord()){strItem += "X";};
			 };//end record check
			 this->setHeaderData(i,Qt::Vertical,strItem,Qt::DisplayRole);
		 };//end loop i
	 };//end queryset check
	 this->update();
 };




#include "pch.h"
#include "DataRow.h"

DataRow::DataRow(CString _actionType, CString _Attributes)
	:actionType(_actionType), Attributes(_Attributes)
{
	
}

DataRow::~DataRow()
{
	
}

CString DataRow::getActionType() const
{
	return actionType;
}

void DataRow::SetActionType(const CString& _actionType)
{
	this->actionType = _actionType;
}

CString DataRow::getAttributes() const
{
	return Attributes;
}

void DataRow::setAttributes(const CString& _Attributes)
{
	this->Attributes = _Attributes;
}


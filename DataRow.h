#pragma once
class DataRow
{
private:
	CString actionType;
	CString Attributes;

public:
	DataRow(CString _actionType, CString _Attributes);
	~DataRow();

	CString getActionType() const;
	void SetActionType(const CString& _actionType);
	CString getAttributes() const;
	void setAttributes(const CString& _Attributes);

};


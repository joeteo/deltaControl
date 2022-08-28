
// deltaControlDlg.h: 헤더 파일
//

#pragma once

#include "SerialCom.h"	// 추가 for SerialCom
#include <vector>

using namespace std;

// CdeltaControlDlg 대화 상자
class CdeltaControlDlg : public CDialogEx
{
// 생성입니다.
public:
	CdeltaControlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CSerialComm* m_comm;	// 추가 for SerialCom

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELTACONTROL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	BOOL comport_state;						// 추가 for SerialCom

	CString m_str_comport;					// 추가 for SerialCom
	CComboBox m_combo_comport_list;			// 추가 for SerialCom
	CString m_combo_baudrate;				// 추가 for SerialCom
	CComboBox m_combo_baudrate_list;		// 추가 for SerialCom

	afx_msg void OnBnClickedBtConnect();
	vector<char> rx;

protected:
	afx_msg LRESULT OnReceive(WPARAM length, LPARAM lParam);		// 추가 for SerialCom
	afx_msg LRESULT OnThreadClosed(WPARAM length, LPARAM lParam);	// 추가 for SerialCom
public:
	afx_msg void OnBnClickedBtTorque();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedBtPump();
	afx_msg void OnBnClickedBtRead();
	CString m_readX;
	CString m_readY;
	CString m_readZ;
	afx_msg void OnBnClickedBtConveyorOnR();
	afx_msg void OnBnClickedBtConveyorOnL();
	afx_msg void OnBnClickedBtConveyorOff();
};

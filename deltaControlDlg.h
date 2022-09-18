
// deltaControlDlg.h: 헤더 파일
//

#pragma once

#include "SerialCom.h"	// 추가 for SerialCom

#include "DataController.h"

typedef enum {
	THREAD_STOP,
	THREAD_RUNNING,
	THREAD_PAUSE
}_ThreadStatus;

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
	afx_msg void OnBnClickedBtDefaultPos();
	afx_msg void OnBnClickedBtPick();
	afx_msg void OnBnClickedBtThrow();
	void SliderInit(CSliderCtrl* slider);
	CSliderCtrl m_sliderX;
	CString m_strX;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_sliderY;
	CSliderCtrl m_sliderZ;
	CString m_strY;
	CString m_strZ;
	afx_msg void OnBnClickedBtMove();
	CListCtrl m_list;
	int m_radio;
	afx_msg void OnBnClickedRadio(UINT id);


	void EnableSerialRelatedControls(bool option);
	DataController DC;
	void renewListControl();

	void pump(bool option);
	void wait(int time);
	void move(int x, int y, int z);

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonToRight();
	afx_msg void OnBnClickedButtonToLeft();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonSuspend();
	CString m_delay;

	CWinThread* m_pThread;
	_ThreadStatus m_threadStatus;

	int m_radio2;
	afx_msg void OnBnClickedButtonStop();

	void terminateThread();

	int currentRow;

	afx_msg void OnCustomdrawMyList(NMHDR* pNMHDR, LRESULT* pResult);
};

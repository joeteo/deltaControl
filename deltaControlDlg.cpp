
// deltaControlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "deltaControl.h"
#include "deltaControlDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdeltaControlDlg 대화 상자



CdeltaControlDlg::CdeltaControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELTACONTROL_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_combo_baudrate(_T(""))
	, m_readX(_T(""))
	, m_readY(_T(""))
	, m_readZ(_T(""))
	, m_strX(_T(""))
	, m_strY(_T(""))
	, m_strZ(_T(""))
	, comport_state(false)
	, m_comm(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdeltaControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_str_comport);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport_list);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate_list);
	DDX_Text(pDX, IDC_EDIT_READ_X, m_readX);
	DDX_Text(pDX, IDC_EDIT_READ_Y, m_readY);
	DDX_Text(pDX, IDC_EDIT_READ_Z, m_readZ);
	DDX_Control(pDX, IDC_SLIDER_X, m_sliderX);
	DDX_Text(pDX, IDC_EDIT_COORD_X, m_strX);
	DDX_Control(pDX, IDC_SLIDER_Y, m_sliderY);
	DDX_Control(pDX, IDC_SLIDER_Z, m_sliderZ);
	DDX_Text(pDX, IDC_EDIT_COORD_Y, m_strY);
	DDX_Text(pDX, IDC_EDIT_COORD_Z, m_strZ);
}

BEGIN_MESSAGE_MAP(CdeltaControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_CONNECT, &CdeltaControlDlg::OnBnClickedBtConnect)
	ON_MESSAGE(WM_MYRECEIVE, &CdeltaControlDlg::OnReceive)
	ON_MESSAGE(WM_MYCLOSE, &CdeltaControlDlg::OnThreadClosed)
	ON_BN_CLICKED(IDC_BT_TORQUE, &CdeltaControlDlg::OnBnClickedBtTorque)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BT_PUMP, &CdeltaControlDlg::OnBnClickedBtPump)
	ON_BN_CLICKED(IDC_BT_READ, &CdeltaControlDlg::OnBnClickedBtRead)
	ON_BN_CLICKED(IDC_BT_CONVEYOR_ON_R, &CdeltaControlDlg::OnBnClickedBtConveyorOnR)
	ON_BN_CLICKED(IDC_BT_CONVEYOR_ON_L, &CdeltaControlDlg::OnBnClickedBtConveyorOnL)
	ON_BN_CLICKED(IDC_BT_CONVEYOR_OFF, &CdeltaControlDlg::OnBnClickedBtConveyorOff)
	ON_BN_CLICKED(IDC_BT_DEFAULT_POS, &CdeltaControlDlg::OnBnClickedBtDefaultPos)
	ON_BN_CLICKED(IDC_BT_PICK, &CdeltaControlDlg::OnBnClickedBtPick)
	ON_BN_CLICKED(IDC_BT_THROW, &CdeltaControlDlg::OnBnClickedBtThrow)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BT_MOVE, &CdeltaControlDlg::OnBnClickedBtMove)
END_MESSAGE_MAP()


// CdeltaControlDlg 메시지 처리기

BOOL CdeltaControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));
	m_combo_comport_list.AddString(_T("COM5"));
	m_combo_comport_list.AddString(_T("COM6"));
	m_combo_comport_list.AddString(_T("COM7"));
	m_combo_comport_list.AddString(_T("COM8"));
	m_combo_comport_list.AddString(_T("COM9"));
	m_combo_comport_list.AddString(_T("COM10"));
	m_combo_comport_list.AddString(_T("COM29"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("115200"));


	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM29");
	m_combo_baudrate = _T("115200");


	SliderInit(&m_sliderX);
	SliderInit(&m_sliderY);
	SliderInit(&m_sliderZ);
	m_strX.Format(_T("%d"), 0);
	m_strY.Format(_T("%d"), 0);
	m_strZ.Format(_T("%d"), -260);



	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CdeltaControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CdeltaControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CdeltaControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CdeltaControlDlg::OnBnClickedBtConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			//GetDlgItem(IDC_BT_SEND)->EnableWindow(false);
		}
	}
	else
	{
		m_comm = new CSerialComm(_T("\\\\.\\") + m_str_comport, m_combo_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
			//GetDlgItem(IDC_BT_SEND)->EnableWindow(true);
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}


afx_msg LRESULT CdeltaControlDlg::OnReceive(WPARAM length, LPARAM lParam)
{
	CString str;
	char* data = new char[length + 1];

	if (m_comm)
	{
		m_comm->Receive(data, length);	// Length 길이만큼 데이터 받음.

		for (int i = 0; i < (int)length; i++)
		{
			rx.push_back(data[i]);
		}

		while (rx.size() >= 14)
		{
			if (rx.at(0) == 'C')
			{
				int tempValue = 0;
				if (rx.at(1) == 'X')
				{					
					tempValue = (rx.at(2) - '0') * 100 + (rx.at(3) - '0') * 10 + (rx.at(4) - '0') * 1;
					m_readX.Format(_T("%d"), tempValue);
					UpdateData(false);
				}
				if (rx.at(5) == 'Y')
				{
					tempValue = (rx.at(6) - '0') * 100 + (rx.at(7) - '0') * 10 + (rx.at(8) - '0') * 1;
					m_readY.Format(_T("%d"), tempValue);
					UpdateData(false);
				}
				if (rx.at(9) == 'Z')
				{
					tempValue = (rx.at(10) - '0') * 100 + (rx.at(11) - '0') * 10 + (rx.at(12) - '0') * 1;
					m_readZ.Format(_T("%d"), tempValue);
					UpdateData(false);
				}

				rx.erase(rx.begin(), rx.begin() + 13);

			}
			else if (rx.at(0) != 'C')
			{
				rx.erase(rx.begin());

			}
			//else if (rx.at(14) != '\n')
			//{
			//	rx.erase(rx.begin(), rx.begin() + 13);
			//}

		}

		UpdateData(false);

		str = "";
	}
	delete[] data;


	return 0;

}


afx_msg LRESULT CdeltaControlDlg::OnThreadClosed(WPARAM length, LPARAM lParam)
{
	((CSerialComm*)lParam)->HandleClose();
	delete ((CSerialComm*)lParam);

	return 0;
}


void CdeltaControlDlg::OnBnClickedBtTorque()
{
	CString str;
	static int toggle = 0;
	
	if (toggle) {
		str = _T("DT1");
		GetDlgItem(IDC_BT_TORQUE)->SetWindowText(_T("TORQUE OFF"));
	}
	else {
		str = _T("DT0");
		GetDlgItem(IDC_BT_TORQUE)->SetWindowText(_T("TORQUE ON"));
	}

	toggle = ~toggle;

	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnBnClickedBtPump()
{
	CString str;
	static int toggle = 0;

	toggle = ~toggle;

	if (toggle) {
		str = _T("DP1");
		GetDlgItem(IDC_BT_PUMP)->SetWindowText(_T("PUMP OFF"));
	}
	else {
		str = _T("DP0");
		GetDlgItem(IDC_BT_PUMP)->SetWindowText(_T("PUMP ON"));
	}
	
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}

void CdeltaControlDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint(1200, 800);
	lpMMI->ptMaxTrackSize = CPoint(1400, 1000);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}





void CdeltaControlDlg::OnBnClickedBtRead()
{
	CString str = _T("DR");
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnBnClickedBtConveyorOnR()
{
	CString str = _T("DC1R");
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnBnClickedBtConveyorOnL()
{
	CString str = _T("DC1L");
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnBnClickedBtConveyorOff()
{
	CString str = _T("DC0");
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnBnClickedBtDefaultPos()
{
	CString str = _T("DO");
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnBnClickedBtPick()
{
	CString str = _T("DA");
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnBnClickedBtThrow()
{
	CString str = _T("DB");
	str += _T("\n");
	m_comm->Send(str, str.GetLength());
}


void CdeltaControlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//CSliderCtrl* pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_X);
	CSliderCtrl* pSlidCtrl = (CSliderCtrl*)pScrollBar;
	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_X) {
		m_strX.Format(_T("%d"), pSlidCtrl->GetPos());
	}
	else if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_Y) {
		m_strY.Format(_T("%d"), pSlidCtrl->GetPos());
	}
	else if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_Z) {
		m_strZ.Format(_T("%d"), pSlidCtrl->GetPos());
	}

	UpdateData(FALSE);

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CdeltaControlDlg::SliderInit(CSliderCtrl* slider)
{
	if (slider->GetDlgCtrlID() == IDC_SLIDER_X || slider->GetDlgCtrlID() == IDC_SLIDER_Y) {
		slider->SetRange(-150, 150);
		slider->SetPos(0);

	}
	else if (slider->GetDlgCtrlID() == IDC_SLIDER_Z) {
		slider->SetRange(-380, -260);
		slider->SetPos(-260);

	}

	slider->SetTicFreq(1);
	slider->SetLineSize(10);

}


void CdeltaControlDlg::OnBnClickedBtMove()
{
	UpdateData(TRUE);

	CString str = _T("DZ");
	CString temp;
	if (m_sliderX.GetPos() >= 0) {
		str += _T("+");
	}
	else {
		str += _T("-");
	}
	temp.Format(_T("%03d"), abs(m_sliderX.GetPos()));
	str += temp;
	if (m_sliderY.GetPos() >= 0) {
		str += _T("+");
	}
	else {
		str += _T("-");
	}
	temp.Format(_T("%03d"), abs(m_sliderY.GetPos()));
	str += temp;

	str += m_strZ;
	
	str += _T("\n");

	m_comm->Send(str, str.GetLength());


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

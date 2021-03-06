
// BatchTextCodepageConvertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatchTextCodepageConvert.h"
#include "BatchTextCodepageConvertDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBatchTextCodepageConvertDlg 对话框



CBatchTextCodepageConvertDlg::CBatchTextCodepageConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBatchTextCodepageConvertDlg::IDD, pParent)
	, m_szCurFileName(_T(""))
	, m_szCodepage(_T(""))
	, m_szPreView(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBatchTextCodepageConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FileName, m_oFileName);
	DDX_Control(pDX, IDC_EDIT_Codepage, m_oCodepage);
	DDX_Control(pDX, IDC_EDIT_PreView, m_oPreView);
	DDX_Control(pDX, IDC_LIST_FilesList, m_oFilesList);
	DDX_Text(pDX, IDC_EDIT_FileName, m_szCurFileName);
	DDX_Text(pDX, IDC_EDIT_Codepage, m_szCodepage);
	DDX_Text(pDX, IDC_EDIT_PreView, m_szPreView);
}

BEGIN_MESSAGE_MAP(CBatchTextCodepageConvertDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST_FilesList, &CBatchTextCodepageConvertDlg::OnLbnSelchangeListFileslist)
	ON_LBN_DBLCLK(IDC_LIST_FilesList, &CBatchTextCodepageConvertDlg::OnLbnDblclkListFileslist)
END_MESSAGE_MAP()


// CBatchTextCodepageConvertDlg 消息处理程序

BOOL CBatchTextCodepageConvertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBatchTextCodepageConvertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBatchTextCodepageConvertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBatchTextCodepageConvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBatchTextCodepageConvertDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFilePathName[MAX_PATH + 1] = { 0 };

	// 得到文件个数     
	UINT nNumOfFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	for (UINT nIndex = 0; nIndex < nNumOfFiles; ++nIndex) {
		// 得到文件名  
		DragQueryFile(hDropInfo, nIndex, (LPTSTR)szFilePathName, MAX_PATH);
		// 插入列表
		m_oFilesList.AddString(szFilePathName);
	}

	DragFinish(hDropInfo);

	// CDialogEx::OnDropFiles(hDropInfo);
}


void CBatchTextCodepageConvertDlg::OnLbnSelchangeListFileslist()
{
	int nIndex = m_oFilesList.GetCurSel();
	if (nIndex != LB_ERR)
	{
		m_oFilesList.GetText(m_oFilesList.GetCurSel(), m_szCurFileName);
		UpdateData(FALSE);
	}	
}


void CBatchTextCodepageConvertDlg::OnLbnDblclkListFileslist()
{
	int nIndex = m_oFilesList.GetCurSel();
	if (nIndex != LB_ERR) {
		TCHAR szFilePathName[MAX_PATH + 1] = { 0 };
		m_oFilesList.GetText(nIndex, szFilePathName);
		HANDLE hFile = CreateFile(szFilePathName,
			GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS,
			NULL);

		DWORD len = GetFileSize(hFile, NULL);
		HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, _T("GuessCodepage"));
		LPBYTE lpBuf = (LPBYTE)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, len);
		//m_szPreView = lpBuf;
		
		ucsd_t obj = NULL;
		obj = ucsd_Create();
		int ret = ucsd_Parse(obj, (const char*)lpBuf, len);
		if (ret != 0) {
			m_szCodepage = _T("Guess codepage failed!");
		}
		else {
			ucsd_DataEnd(obj);
			const char *result = ucsd_GetCharset(obj);
			if (result == NULL) {
				m_szCodepage = _T("Unknown character set!");
			}
			else {
				m_szCodepage = result;
				WCHAR szPreViewBuffer[2048 + 1] = { 0 };
				iconv_t icd = 0;
				icd = iconv_open("UTF-16LE//TRANSLIT//IGNORE", result);
				size_t ret = 0;
				size_t inbufleft = len;
				size_t outbufleft = 2048;
				const char *inbuf = (const char *)lpBuf;
				char *outbuf = (char*)&szPreViewBuffer;
				ret = iconv(icd, &inbuf, &inbufleft, &outbuf, &outbufleft);
				iconv_close(icd);
				m_szPreView = szPreViewBuffer;
			}
		}

		ucsd_Reset(obj);
		ucsd_Destroy(obj);

		UnmapViewOfFile(lpBuf);
		CloseHandle(hMap);
		CloseHandle(hFile);
	}
	else {
		m_szCodepage = _T("没有双击任何文件条目");
	}
	
	UpdateData(FALSE);
}

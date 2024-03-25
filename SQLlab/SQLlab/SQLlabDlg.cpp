
// SQLlabDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SQLlab.h"
#include "SQLlabDlg.h"
#include "afxdialogex.h"
#include "mysql.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString account ;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
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


// CSQLlabDlg 对话框



CSQLlabDlg::CSQLlabDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SQLLAB_DIALOG, pParent)
	, m_name(_T(""))
	, m_psw(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSQLlabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_texttest, n_txt);
}

BEGIN_MESSAGE_MAP(CSQLlabDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSQLlabDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CSQLlabDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CSQLlabDlg 消息处理程序

BOOL CSQLlabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSQLlabDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSQLlabDlg::OnPaint()
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
HCURSOR CSQLlabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSQLlabDlg::OnBnClickedButtonOk()
{
	// Login Button
	//CDialogEx::OnOK();

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(m_name); //获得输入的用户名
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(m_psw); //获得输入的密码

	const char user[] = "root"; //填写你的 mysql 用户名
	const char pswd[] = "tt123456";  //填写你的 mysql 密码
	const char host[] = "localhost";
	const char database[] = "order_system";  //填写你的 mysql 数据库名称
	unsigned int port = 3306;

	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL mysqlCon;

	if (m_name.IsEmpty() || m_psw.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空!"), _T("用户登录信息"));
		return;
	}

	mysql_init(&mysqlCon);
	if (!mysql_real_connect(&mysqlCon, host, user, pswd, database, port, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
	}
	else
	{
		mysql_query(&mysqlCon, "SET USER GBK"); //设置字符集
		//AfxMessageBox(_T("访问数据库成功!"));
	}


	//mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文 
	// 如果你的用户名是中文，加上上面这句；

	int ress = mysql_query(&mysqlCon, "select account, password from users");

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
		res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			AfxMessageBox(_T("用户不存在"));
		}
		else
		{
			int flag = 0;
			while (row = mysql_fetch_row(res)) {
				if (m_name==row[0] && m_psw == row[1])
					{
						account = row[0];
						mysql_free_result(res);
						MessageBox(_T("登录成功，欢迎！"));;
						CDialog::OnCancel();
						CMainFrame main_frame;
						main_frame.DoModal();
						flag = 1;
						
						break;
					}	
			}
			if (flag == 0) {
				AfxMessageBox(_T("密码错误!"));
			}
		}
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}

	mysql_close(&mysqlCon);
}


void CSQLlabDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

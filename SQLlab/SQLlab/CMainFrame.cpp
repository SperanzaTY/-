// CMainFrame.cpp: 实现文件
//

#include "pch.h"
#include "SQLlab.h"
#include "CMainFrame.h"
#include "afxdialogex.h"
#include "CChangeInfo.h"
#include "CChangePwd.h"
#include "CDishOrder.h"
#include "CMyOrder.h"
#include "SQLlabDlg.h"
#include "winsock.h"
#include "mysql.h"

extern CString account;
CString stu_id;
BOOL OnInitDialog();

// CMainFrame 对话框

IMPLEMENT_DYNAMIC(CMainFrame, CDialogEx)

CMainFrame::CMainFrame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_FRAME, pParent)
{	
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_name, m_name);
	DDX_Control(pDX, IDC_id, m_id);
	DDX_Control(pDX, IDC_addr, m_addr);
}


BEGIN_MESSAGE_MAP(CMainFrame, CDialogEx)
	ON_BN_CLICKED(IDC_DISH_ORDER, &CMainFrame::OnBnClickedDishOrder)
	ON_BN_CLICKED(IDC_MY_ORDER, &CMainFrame::OnBnClickedMyOrder)
	ON_BN_CLICKED(IDC_CHANGE_INFO, &CMainFrame::OnBnClickedChangeInfo)
	ON_BN_CLICKED(IDC_CHANGE_PSD, &CMainFrame::OnBnClickedChangePsd)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainFrame::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_EXIT, &CMainFrame::OnBnClickedExit)
END_MESSAGE_MAP()


// CMainFrame 消息处理程序

void CMainFrame::OnBnClickedDishOrder()
{
	// TODO: 在此添加控件通知处理程序代码
	CDishOrder dishorder;
	dishorder.DoModal();
}


void CMainFrame::OnBnClickedMyOrder()
{
	// TODO: 在此添加控件通知处理程序代码
	CMyOrder myorder;
	myorder.DoModal();
}


void CMainFrame::OnBnClickedChangeInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CChangeInfo changeinfo;
	changeinfo.DoModal();
}


void CMainFrame::OnBnClickedChangePsd()
{
	// TODO: 在此添加控件通知处理程序代码
	CChangePwd changepassword;
	changepassword.DoModal();
}


BOOL CMainFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const char user[] = "root"; //填写你的 mysql 用户名
	const char pswd[] = "tt123456";  //填写你的 mysql 密码
	const char host[] = "localhost";
	const char database[] = "order_system";  //填写你的 mysql 数据库名称
	unsigned int port = 3306;

	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL mysqlCon;

	mysql_init(&mysqlCon);
	if (!mysql_real_connect(&mysqlCon, host, user, pswd, database, port, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
	}
	else
	{
		mysql_query(&mysqlCon, "SET USER GBK"); //设置字符集
		//AfxMessageBox(_T("框架连接数据库成功!"));
	}

	//初始化填写用户信息
	int ress = mysql_query(&mysqlCon, "SELECT account,name,student.id,doom FROM student, address where student.id = address.id");

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
		res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			AfxMessageBox(_T("查找失败！"));
		}
		else
		{
			while (row = mysql_fetch_row(res)) {
				if (account == row[0])
				{
					//MessageBox(_T("初始化成功！"));
					//初始化填写个人信息
					m_name.SetWindowText(row[1]);
					m_id.SetWindowText(row[2]);
					m_addr.SetWindowText(row[3]);
					stu_id = row[2];
					mysql_free_result(res);
					break;
				}
			}
		}
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}

	mysql_close(&mysqlCon);

	return TRUE;
}

void CMainFrame::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
	CMainFrame update;
	update.DoModal();
}


void CMainFrame::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
	CSQLlabDlg login;
	login.DoModal();
}

// CChangePwd.cpp: 实现文件
//

#include "pch.h"
#include "SQLlab.h"
#include "CChangePwd.h"
#include "afxdialogex.h"
#include "WinSock.h"
#include "mysql.h"
extern CString account;

// CChangePwd 对话框

IMPLEMENT_DYNAMIC(CChangePwd, CDialogEx)

CChangePwd::CChangePwd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHANGE_PASSWORD, pParent)
{

}

CChangePwd::~CChangePwd()
{
}

void CChangePwd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangePwd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChangePwd::OnBnClickedButton1)
END_MESSAGE_MAP()


// CChangePwd 消息处理程序


void CChangePwd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString old_psw;
	CString new_psw;
	GetDlgItem(IDC_EDIT1)->GetWindowText(old_psw); 
	GetDlgItem(IDC_EDIT2)->GetWindowText(new_psw);

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

	sprintf_s(query, "select password from users where account = \'%s\'", account);
	mysql_query(&mysqlCon, query);
	res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
	row = mysql_fetch_row(res);
	if (old_psw == row[0])
	{
		sprintf_s(query, "update users set password = \'%s\' where account = \'%s\ '", new_psw,account);
		int res_psw = mysql_query(&mysqlCon, query);
		if (res_psw == 0)
		{
			MessageBox("密码修改成功！");
			CDialog::OnCancel();
		}
		else
		{
			MessageBox("修改失败！");
		}
	}
	else
	{
		MessageBox("密码错误！");
	}
}

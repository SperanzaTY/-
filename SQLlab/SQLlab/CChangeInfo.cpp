// CChangeInfo.cpp: 实现文件
//

#include "pch.h"
#include "SQLlab.h"
#include "CChangeInfo.h"
#include "afxdialogex.h"
#include "WinSock.h"
#include "mysql.h"
extern CString account;
extern CString stu_id;

// CChangeInfo 对话框

IMPLEMENT_DYNAMIC(CChangeInfo, CDialogEx)

CChangeInfo::CChangeInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHANGE_INFO, pParent)
{

}

CChangeInfo::~CChangeInfo()
{
}

void CChangeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangeInfo, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON1, &CChangeInfo::OnBnClickedButton1)
END_MESSAGE_MAP()


// CChangeInfo 消息处理程序




void CChangeInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString new_name;
	CString new_addr;

	GetDlgItemText(IDC_EDIT1, new_name);///是取该输入框的值
	GetDlgItemText(IDC_EDIT3, new_addr);

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

	//修改信息
	sprintf_s(query, "update student set name = \'%s\' where account = \'%s\' ",new_name, account);
	int res_name = mysql_query(&mysqlCon, query);
	sprintf_s(query, "update address set doom = \'%s\' where  address.id = \'%s\' ", new_addr, stu_id);
	int res_addr = mysql_query(&mysqlCon, query);

	if (res_name == 0  && res_addr == 0) //检测查询成功为0，不成功则非0
	{
		AfxMessageBox(_T("修改成功!"));
		CDialog::OnCancel();
	}
	else
	{
		AfxMessageBox(_T("修改失败!"));
	}


	mysql_close(&mysqlCon);
}

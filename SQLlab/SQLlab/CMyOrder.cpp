// CMyOrder.cpp: 实现文件
//

#include "pch.h"
#include "SQLlab.h"
#include "CMyOrder.h"
#include "afxdialogex.h"
#include "winsock.h"
#include "mysql.h"

extern CString account;
// CMyOrder 对话框

IMPLEMENT_DYNAMIC(CMyOrder, CDialogEx)

CMyOrder::CMyOrder(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_ORDER, pParent)
{

}

CMyOrder::~CMyOrder()
{
}

void CMyOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


BEGIN_MESSAGE_MAP(CMyOrder, CDialogEx)

END_MESSAGE_MAP()


// CMyOrder 消息处理程序


BOOL CMyOrder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_list.InsertColumn(0, "订单号", LVCFMT_CENTER, 80);
	m_list.InsertColumn(1, "菜品名", LVCFMT_CENTER, 250);
	m_list.InsertColumn(2, "数量", LVCFMT_CENTER, 110);
	m_list.InsertColumn(3, "价格", LVCFMT_CENTER, 110);

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
		//AfxMessageBox(_T("访问数据库成功!"));
	}


	mysql_query(&mysqlCon, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文 


	sprintf_s(query, "select orders.o_id,d_name,d_num,o_price from orders,dish where orders.d_id=dish.d_id && orders.account = \'%s\'", account);
	int ress = mysql_query(&mysqlCon,query);

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
		res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			AfxMessageBox(_T("订单为空！"));
		}
		else
		{
			int i = 0;
			while (row = mysql_fetch_row(res)) {
				m_list.InsertItem(i, "");
				m_list.SetItemText(i, 0, row[0]);
				m_list.SetItemText(i, 1, row[1]);
				m_list.SetItemText(i, 2, row[2]);
				m_list.SetItemText(i, 3, row[3]);
			}
			mysql_free_result(res);
		}
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}

	mysql_close(&mysqlCon);

	return TRUE;
}
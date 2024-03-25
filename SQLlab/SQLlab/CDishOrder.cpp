// CDishOrder.cpp: 实现文件
//

#include "pch.h"
#include "SQLlab.h"
#include "CDishOrder.h"
#include "afxdialogex.h"
#include "winsock.h"
#include "mysql.h"
extern CString account;

// CDishOrder 对话框

IMPLEMENT_DYNAMIC(CDishOrder, CDialogEx)

CDishOrder::CDishOrder(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DISH_ORDER, pParent)
{

}

CDishOrder::~CDishOrder()
{
}

void CDishOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CANTEEN, m_canteen);
	DDX_Control(pDX, IDC_DISH, m_dish);
	DDX_Control(pDX, IDC_NUM, m_num);
}


BEGIN_MESSAGE_MAP(CDishOrder, CDialogEx)

	ON_CBN_SELCHANGE(IDC_CANTEEN, &CDishOrder::OnCbnSelchangeCanteen)
	ON_BN_CLICKED(IDC_EXIT, &CDishOrder::OnBnClickedExit)
	ON_BN_CLICKED(IDC_PAY, &CDishOrder::OnBnClickedPay)
END_MESSAGE_MAP()


// CDishOrder 消息处理程序
BOOL CDishOrder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_num.AddString(TEXT("1"));
	m_num.AddString(TEXT("2"));
	m_num.AddString(TEXT("3"));
	m_num.AddString(TEXT("4"));
	m_num.AddString(TEXT("5"));
	m_num.AddString(TEXT("6"));
	m_num.AddString(TEXT("7"));
	m_num.AddString(TEXT("8"));
	m_num.AddString(TEXT("9"));
	m_num.SetCurSel(0);

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

	int ress = mysql_query(&mysqlCon, "SELECT canteen FROM order_system.canteen");

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
		res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			AfxMessageBox(_T("餐厅为空！"));
		}
		else
		{
			int i = 0;
			while (row = mysql_fetch_row(res)) {
				m_canteen.InsertString(i,TEXT(row[0]));
				i++;
			}
			mysql_free_result(res);
			m_canteen.SetCurSel(0);
		}
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}

	CString str;
	m_canteen.GetLBText(m_canteen.GetCurSel(), str);//获取餐厅号

	sprintf_s(query, "SELECT d_name FROM dish,canteen where dish.canteen = canteen.canteen && dish.canteen = \'%s\' ", str);
	ress = mysql_query(&mysqlCon, query);

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
		res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			AfxMessageBox(_T("菜品为空！"));
		}
		else
		{
			while (row = mysql_fetch_row(res)) {
				m_dish.AddString(TEXT(row[0]));
			}
			mysql_free_result(res);
			m_dish.SetCurSel(0);
		}
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}
	mysql_close(&mysqlCon);

	return TRUE;
}

void CDishOrder::OnCbnSelchangeCanteen()
{
	// TODO: 菜单栏选项改变
	m_dish.ResetContent();

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

	CString str;
	m_canteen.GetLBText(m_canteen.GetCurSel(),str);//获取餐厅号

	sprintf_s(query, "SELECT d_name FROM dish,canteen where dish.canteen = canteen.canteen && dish.canteen = \'%s\' ",str);
	int ress = mysql_query(&mysqlCon, query);

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
		res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			AfxMessageBox(_T("菜品为空！"));
		}
		else
		{
			while (row = mysql_fetch_row(res)) {
				m_dish.AddString(TEXT(row[0]));	
			}
			mysql_free_result(res);
			m_dish.SetCurSel(0);
		}
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}

	mysql_close(&mysqlCon);
}


void CDishOrder::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CDishOrder::OnBnClickedPay()
{
	// TODO: 在此添加控件通知处理程序代码
	int index_canteen = m_canteen.GetCurSel();
	int index_dish = m_dish.GetCurSel();
	int index_num = m_num.GetCurSel();

	dish_num = index_num + 1;	//得到d_num

	CString dish_name;
	int idx = m_dish.GetCurSel();
	m_dish.GetLBText(idx, dish_name);	//获取到菜名

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

	sprintf_s(query, "SELECT d_id,d_price FROM dish WHERE d_name = \'%s\' ", dish_name);
	int ress = mysql_query(&mysqlCon, query);

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
		res = mysql_store_result(&mysqlCon); //保存查询到的数据到 res
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			AfxMessageBox(_T("结果为空！"));
		}
		else
		{
			row = mysql_fetch_row(res);
			CString str;
			str = row[0];
			dish_id = _ttoi(str);//得到d_id

			str = row[1];
			order_price = (_ttoi(str)) * dish_num;		//	获得一单价格
		}
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}

	//订单写入数据库

	int next_order;
	ress = mysql_query(&mysqlCon," select count(1) from orders");
	res = mysql_store_result(&mysqlCon);
	row = mysql_fetch_row(res);
	next_order = _ttoi(row[0])+1;

	CString test;
	test.Format("订单号：%d", next_order);
	MessageBox(test);

	sprintf_s(query, "insert into orders(o_id,account,d_id,d_num,o_price) values (\'%d\',\'%s\',\'%d\',\'%d\',\'%d\');", next_order,account,dish_id,dish_num,order_price);
	ress = mysql_query(&mysqlCon, query);

	if (ress == 0) //检测查询成功为0，不成功则非0
	{
			CString info;
			info.Format("购买成功!\n本次消费%d元", order_price);
			MessageBox(info);
	}
	else
	{
		AfxMessageBox(_T("访问失败!"));
	}
	mysql_close(&mysqlCon);

}

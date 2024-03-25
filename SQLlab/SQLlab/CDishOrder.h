#pragma once


// CDishOrder 对话框

class CDishOrder : public CDialogEx
{
	DECLARE_DYNAMIC(CDishOrder)

public:
	CDishOrder(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDishOrder();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISH_ORDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

private:
	CComboBox m_canteen;
	CComboBox m_dish;
	CComboBox m_num;
	BOOL OnInitDialog();
	char query[150];
public:
	afx_msg void OnCbnSelchangeCanteen();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedPay();
	afx_msg void OnCbnSelchangeDish();

	int dish_num;
	int dish_id;
	int order_price;
};

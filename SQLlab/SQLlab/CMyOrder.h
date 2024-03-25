#pragma once


// CMyOrder 对话框

class CMyOrder : public CDialogEx
{
	DECLARE_DYNAMIC(CMyOrder)

public:
	CMyOrder(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyOrder();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_ORDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
private:
	BOOL OnInitDialog();
	char query[150];
};

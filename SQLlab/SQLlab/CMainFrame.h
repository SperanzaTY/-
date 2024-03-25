#pragma once


// CMainFrame 对话框

class CMainFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CMainFrame)

public:
	CMainFrame(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMainFrame();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_FRAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedDishOrder();
	afx_msg void OnBnClickedMyOrder();
	afx_msg void OnBnClickedChangeInfo();
	afx_msg void OnBnClickedChangePsd();
	CStatic m_name;
	CStatic m_id;
	CStatic m_addr;
	BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedExit();
};

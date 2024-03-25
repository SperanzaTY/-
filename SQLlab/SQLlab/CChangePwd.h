#pragma once


// CChangePwd 对话框

class CChangePwd : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePwd)

public:
	CChangePwd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChangePwd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGE_PASSWORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	char query[150];
};

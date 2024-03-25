#pragma once


// CChangeInfo 对话框

class CChangeInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeInfo)

public:
	CChangeInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChangeInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGE_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButton1();
private:
	char query[150];
};

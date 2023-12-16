// SpaceHogDlg.h : header file
//

#if !defined(AFX_SPACEHOGDLG_H__7993BB98_B28E_4201_B649_FFEBF9C72970__INCLUDED_)
#define AFX_SPACEHOGDLG_H__7993BB98_B28E_4201_B649_FFEBF9C72970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSpaceHogDlg dialog

class CSpaceHogDlg : public CDialog
{
// Construction
public:
	CSpaceHogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpaceHogDlg)
	enum { IDD = IDD_SPACEHOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpaceHogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpaceHogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPACEHOGDLG_H__7993BB98_B28E_4201_B649_FFEBF9C72970__INCLUDED_)

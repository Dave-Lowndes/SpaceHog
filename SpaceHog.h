// SpaceHog.h : main header file for the SPACEHOG application
//

#if !defined(AFX_SPACEHOG_H__E5F596C6_56F1_4ABB_BB9E_1A4FB77459C4__INCLUDED_)
#define AFX_SPACEHOG_H__E5F596C6_56F1_4ABB_BB9E_1A4FB77459C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpaceHogApp:
// See SpaceHog.cpp for the implementation of this class
//

class CSpaceHogApp : public CWinApp
{
public:
	CSpaceHogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpaceHogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpaceHogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPACEHOG_H__E5F596C6_56F1_4ABB_BB9E_1A4FB77459C4__INCLUDED_)

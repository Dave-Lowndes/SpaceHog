// SpaceHogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpaceHog.h"
#include "SpaceHogDlg.h"

#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpaceHogDlg dialog

CSpaceHogDlg::CSpaceHogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpaceHogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpaceHogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpaceHogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpaceHogDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpaceHogDlg, CDialog)
	//{{AFX_MSG_MAP(CSpaceHogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpaceHogDlg message handlers

BOOL CSpaceHogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	/* Populate the combo box with the available disk drives.
	 * For some odd reason, I have to specify a valid string as the last parameter.
	 */
	HWND hCombo = ::GetDlgItem( m_hWnd, IDC_DRIVE );
	ComboBox_Dir( hCombo, DDL_DRIVES, _T("") );
	ComboBox_SetCurSel( hCombo, 1 );

	/* Default to creating remaining space */
	CheckRadioButton( IDC_REMAIN, IDC_FSIZE, IDC_REMAIN );

	/* Default 10MB size */
	SetDlgItemInt( IDC_SIZE_LEFT, 10*1000*1000/*1024*1024*/, FALSE );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpaceHogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSpaceHogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpaceHogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

#define HOGFILENAME _T("SpaceHog.tmp")

void CSpaceHogDlg::OnOK() 
{
	// TODO: Add extra validation here
	BOOL bTrans;

	LARGE_INTEGER uSpace;
	CString sVal;
	GetDlgItemText( IDC_SIZE_LEFT, sVal );
	if ( sVal.GetLength() != 0 )
	{
		bTrans = true;
		uSpace.QuadPart = _ttoi64( sVal );
	}
	else
	{
		bTrans = false;
		uSpace.QuadPart = 0;	// Prevent compiler warning
	}

//	uSpace.QuadPart = ::GetDlgItemInt( m_hWnd, IDC_SIZE_LEFT, &bTrans, FALSE );

	if ( bTrans )
	{
		TCHAR szPath[_MAX_PATH];

		DlgDirSelectComboBoxEx( m_hWnd, szPath, _countof( szPath ), IDC_DRIVE );

		szPath[2] = _T('\\');
		szPath[3] = _T('\0');

		UINT dt = GetDriveType( szPath );

		bool bContinue;

		/* Warn about doing it on network and CD-ROM drives */
		if ( ( dt == DRIVE_CDROM ) || ( dt == DRIVE_REMOTE ) )
		{
			bContinue = IDYES == AfxMessageBox( _T("You've selected a CD/DVD drive, or a network drive.\n\n")
				_T("Are you sure you want to do this?"), MB_YESNO | MB_DEFBUTTON2 );
		}
		else
		{
			bContinue = true;
		}

		if ( bContinue )
		{
			lstrcpy( &szPath[3], HOGFILENAME );

			/* Delete the existing temporary file */
			DeleteFile( szPath );

			/* Do we want to create a file of this size, or try to leave this amount of space on disk? */
			if ( IsDlgButtonChecked( IDC_REMAIN ) == BST_CHECKED )
			{
				/* Temporarily botch the file name to leave just the drive */
				TCHAR chTmp = szPath[2];
				szPath[2] = _T('\0');

				/* Find how much disk space we have */
				ULARGE_INTEGER CallerFree, TotBytes, TotFree;
				GetDiskFreeSpaceEx( szPath, &CallerFree, &TotBytes, &TotFree );
				uSpace.QuadPart = TotFree.QuadPart - uSpace.QuadPart;

				szPath[2] = chTmp;
			}

			bool bOK = false;

			DWORD dwErr = 0;	// Init to prevent compiler warning
			{
				/* This could take a long time if the file is large */
				CWaitCursor wait;

				/* Create/Overwrite the temporary hog file on the root of the drive */
				HANDLE hFile = CreateFile( szPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL );

				if ( hFile != INVALID_HANDLE_VALUE )
				{
					if ( -1 != SetFilePointer( hFile, uSpace.LowPart, &uSpace.HighPart, FILE_BEGIN ) )
					{
						if ( SetEndOfFile( hFile ) )
						{
							bOK = true;
						}
					}

					if ( !CloseHandle( hFile ) )
					{
						bOK = false;
					}
				}

				if ( !bOK )
				{
					dwErr = GetLastError();
				}
			}

			if ( !bOK )
			{
				LPVOID lpMsgBuf;
				FormatMessage( 
					FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | 
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					dwErr,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL 
				);

				// Process any inserts in lpMsgBuf.
				// ...
				// Display the string.
				::MessageBox( m_hWnd, (LPCTSTR)lpMsgBuf, _T("Failed to create file"), MB_OK | MB_ICONINFORMATION );
				// Free the buffer.
				LocalFree( lpMsgBuf );
			}
		}
	}
	else
	{
		AfxMessageBox( _T("Invalid Space Value") );
	}
}


void CSpaceHogDlg::OnDelete() 
{
	CWaitCursor wait;

	TCHAR szDrives[4*26 + 1];
	GetLogicalDriveStrings( sizeof( szDrives ), szDrives );
	LPCTSTR pDrive = szDrives;

	while ( pDrive[0] != _T('\0') )
	{
		UINT dt = GetDriveType( pDrive );

		/* Skip network and CD-ROM drives */
		if ( ( dt == DRIVE_CDROM ) || ( dt == DRIVE_REMOTE ) )
		{
		}
		else
		{
			TCHAR szPath[_MAX_PATH];

			/* Create the hog file path name */
			lstrcpy( szPath, pDrive );
			lstrcpy( &szPath[3], HOGFILENAME );

			DeleteFile( szPath );
		}

		/* Next drive */
		pDrive += sizeof( "C:\\" );
	}
}

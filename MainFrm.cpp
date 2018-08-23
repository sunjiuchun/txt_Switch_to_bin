
// MainFrm.cpp : CMainFrame 类的实现
//
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
#include "Switch.h"
#include <stdio.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

	BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
		ON_WM_CREATE()
		ON_WM_SETFOCUS()
		ON_COMMAND(ID_32771, &CMainFrame::On32771)
	END_MESSAGE_MAP()

	static UINT indicators[] =
	{
		ID_SEPARATOR,           // 状态行指示器
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
	};

	// CMainFrame 构造/析构

	CMainFrame::CMainFrame()
	{
		// TODO: 在此添加成员初始化代码
	}

	CMainFrame::~CMainFrame()
	{
	}

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;

		// 创建一个视图以占用框架的工作区
		if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
		{
			TRACE0("未能创建视图窗口\n");
			return -1;
		}

		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("未能创建状态栏\n");
			return -1;      // 未能创建
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

		return 0;
	}

	BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
	{
		if( !CFrameWnd::PreCreateWindow(cs) )
			return FALSE;
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
			| WS_THICKFRAME;

		cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
		cs.lpszClass = AfxRegisterWndClass(0);
		return TRUE;
	}

	// CMainFrame 诊断

#ifdef _DEBUG
	void CMainFrame::AssertValid() const
	{
		CFrameWnd::AssertValid();
	}

	void CMainFrame::Dump(CDumpContext& dc) const
	{
		CFrameWnd::Dump(dc);
	}
#endif //_DEBUG


	// CMainFrame 消息处理程序

	void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
	{
		// 将焦点前移到视图窗口
		m_wndView.SetFocus();
	}

	BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
	{
		// 让视图第一次尝试该命令
		if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;

		// 否则，执行默认处理
		return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}

	//按钮响应事件,进行转换并保存二进制文件
	void CMainFrame::On32771()
	{
		// TODO: 在此添加命令处理程序代码
		CString pathName;
		CString fileName;
		CString FileDirName = _T("D:\sjc");
		CFileDialog fileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("威胁库文本文件(*.txt)|*.txt||"));
		fileDlg.m_ofn.lpstrTitle = _T("");
		fileDlg.m_ofn.lpstrDefExt = _T("txt");
		fileDlg.m_ofn.lpstrInitialDir = FileDirName;

		CFileFind find;
		int t = find.FindFile(LPCTSTR("D:\\DATA"));
		if (t == 0)
		{
			CreateDirectory(LPCTSTR("D:\\DATA"),NULL);
		}
		CString style;
		CString orFileName = _T("D:\\DATA\\JZB.20");
		int k = find.FindFile(LPCTSTR("D:\\DATA"));
		if (k > 0)
		{
			MessageBox(_T("createway"),_T("提示"),MB_OK|MB_ICONWARNING);
		}
		
		int y = orgaufh.Open(orFileName,CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate,0);
		if (y!=0)
		{
			//orgaufh.SeekToEnd();
		}
		if(fileDlg.DoModal()==IDOK)
		{
			pathName = fileDlg.GetPathName();
			fileName = fileDlg.GetFileName();
			struct A Threadlib = {0};
			int i ,length;
			length = fileName.GetLength();
			char *FileName = new char[length];
			for (int i = 0; i < length; i++)
			{
				*(FileName+i) = fileName.GetAt(i);
			}
			*(FileName+length) = NULL;
			FILE *fp;
			errno_t err;
			int d = 0;
			err = fopen_s(&fp,FileName,"r+");
			CString kiss;
			kiss.Format(_T("err值为%d"),err);
			MessageBox(kiss,_T("提示"),MB_OK|MB_ICONWARNING);
			if(0 == err)
			{
				fscanf_s(fp,"%d",&(Threadlib.Num));
				fscanf_s(fp,"%d",&(Threadlib.BJ));
				this->SaveAlarmOrg((char*)&Threadlib.Num,sizeof(int));
				this->SaveAlarmOrg((char*)&Threadlib.BJ,sizeof(int));
				for (int i = 0; i < Threadlib.Num; i++)
				{
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iRf));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iSlope1));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iIntercept1));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iSlope2));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iIntercept2));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iSlope3));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iIntercept3));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iSlope4));
					fscanf_s(fp,"%d",&(Threadlib.tagThreat[i].iIntercept4));
					this->SaveAlarmOrg((char*)&Threadlib.tagThreat[i],36);
					
				}
				orgaufh.Close();
				MessageBox(_T("666"),_T("提示"),MB_OK|MB_ICONWARNING);
			}
		}
	}
	int CMainFrame::SaveAlarmOrg(char *buf,int lenOfByte)
	{
		
		//orgaufh.SeekToEnd();
		orgaufh.Write(buf,lenOfByte);
		orgaufh.Flush();
		return 1;
	}
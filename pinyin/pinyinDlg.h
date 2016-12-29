
// pinyinDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include <string>
#include <iostream>
#include "afxcmn.h"

#include <map>
#include <list>
#include <vector>

#include <algorithm>

using namespace std;

// CpinyinDlg �Ի���
class CpinyinDlg : public CDialog
{
// ����
public:
	CpinyinDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PINYIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnZh();
	CString m_csInput;
	CString m_csOutput;

protected:
	char* ConvertChineseUnicodeToPyt(wchar_t* chrstr);
	std::wstring ws2s(std::string str);
	BOOL InitializePinyinMap();

	CString EncodeChinese(CString InputStr);
	CString DecodeChinese(CString InputStr);
	BOOL	GetSimpleAndFull(CString InputStr, CString &SimpleStr, CString &FullStr);
public:
	CEdit m_edit_Inpot;
	CEdit m_edit_Output;
	CComboBox m_ComboBox;
	CString m_csComboBox;
	afx_msg void OnCbnEditchangeCombo1();
	afx_msg void OnCbnDropdownCombo1();
	CEdit m_SearchEdit;
	CString m_csSearchValue;
	CListCtrl m_listSearchResult;
	afx_msg void OnEnChangeEdit1();

	void RebuildRearchList(const std::vector<std::wstring> &SearchVec);
	CEdit m_AddEdit;
	CString m_csAddValue;
	afx_msg void OnBnClickedButton1();


private:
	std::multimap<CString, CString> PYmap;
	std::multimap<CString, CString> PYHelpermap;
};

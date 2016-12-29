
// pinyinDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pinyin.h"
#include "pinyinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CpinyinDlg 对话框




CpinyinDlg::CpinyinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CpinyinDlg::IDD, pParent)
	, m_csInput(_T(""))
	, m_csOutput(_T(""))
	, m_csComboBox(_T(""))
	, m_csSearchValue(_T(""))
	, m_csAddValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpinyinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN, m_csInput);
	DDX_Text(pDX, IDC_EDIT_OUT, m_csOutput);
	DDX_Control(pDX, IDC_EDIT_IN, m_edit_Inpot);
	DDX_Control(pDX, IDC_EDIT_OUT, m_edit_Output);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_CBString(pDX, IDC_COMBO1, m_csComboBox);
	DDX_Control(pDX, IDC_EDIT1, m_SearchEdit);
	DDX_Text(pDX, IDC_EDIT1, m_csSearchValue);
	DDX_Control(pDX, IDC_LIST1, m_listSearchResult);
	DDX_Control(pDX, IDC_EDIT2, m_AddEdit);
	DDX_Text(pDX, IDC_EDIT2, m_csAddValue);
}

BEGIN_MESSAGE_MAP(CpinyinDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ZH, &CpinyinDlg::OnBnClickedBtnZh)
	ON_CBN_EDITCHANGE(IDC_COMBO1, &CpinyinDlg::OnCbnEditchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CpinyinDlg::OnCbnDropdownCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CpinyinDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CpinyinDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CpinyinDlg 消息处理程序

BOOL CpinyinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_edit_Inpot.ShowWindow(SW_HIDE);
	m_edit_Output.ShowWindow(SW_HIDE);
	m_ComboBox.ShowWindow(SW_HIDE);

	InitializePinyinMap();

	//test
	//std::multimap<CString, CString> map = PYmap;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpinyinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpinyinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpinyinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CpinyinDlg::OnBnClickedBtnZh()
{
	// TODO: 在此添加控件通知处理程序代码
// 	m_edit_Inpot.GetWindowText(m_csInput);
// 	std::string strVal = ConvertChineseUnicodeToPyt(m_csInput.GetBuffer());
// 	m_csInput.ReleaseBuffer();
// 	m_edit_Output.SetWindowText(ws2s(strVal).c_str());

	m_edit_Inpot.GetWindowText(m_csInput);
	CString csEncodestr = EncodeChinese(m_csInput);

	CString csSimplestr, csFullstr;
	if (GetSimpleAndFull(csEncodestr, csSimplestr, csFullstr))
	{
		m_edit_Output.SetWindowText(csFullstr.GetString());
	}
}

char* CpinyinDlg::ConvertChineseUnicodeToPyt(wchar_t* chrstr)
{ 
	const  int pyvalue[] = {-20319,-20317,-20304,-20295,-20292,-20283,-20265,-20257,-20242,-20230,-20051,-20036,-20032,-20026,
		-20002,-19990,-19986,-19982,-19976,-19805,-19784,-19775,-19774,-19763,-19756,-19751,-19746,-19741,-19739,-19728,
		-19725,-19715,-19540,-19531,-19525,-19515,-19500,-19484,-19479,-19467,-19289,-19288,-19281,-19275,-19270,-19263,
		-19261,-19249,-19243,-19242,-19238,-19235,-19227,-19224,-19218,-19212,-19038,-19023,-19018,-19006,-19003,-18996,
		-18977,-18961,-18952,-18783,-18774,-18773,-18763,-18756,-18741,-18735,-18731,-18722,-18710,-18697,-18696,-18526,
		-18518,-18501,-18490,-18478,-18463,-18448,-18447,-18446,-18239,-18237,-18231,-18220,-18211,-18201,-18184,-18183,
		-18181,-18012,-17997,-17988,-17970,-17964,-17961,-17950,-17947,-17931,-17928,-17922,-17759,-17752,-17733,-17730,
		-17721,-17703,-17701,-17697,-17692,-17683,-17676,-17496,-17487,-17482,-17468,-17454,-17433,-17427,-17417,-17202,
		-17185,-16983,-16970,-16942,-16915,-16733,-16708,-16706,-16689,-16664,-16657,-16647,-16474,-16470,-16465,-16459,
		-16452,-16448,-16433,-16429,-16427,-16423,-16419,-16412,-16407,-16403,-16401,-16393,-16220,-16216,-16212,-16205,
		-16202,-16187,-16180,-16171,-16169,-16158,-16155,-15959,-15958,-15944,-15933,-15920,-15915,-15903,-15889,-15878,
		-15707,-15701,-15681,-15667,-15661,-15659,-15652,-15640,-15631,-15625,-15454,-15448,-15436,-15435,-15419,-15416,
		-15408,-15394,-15385,-15377,-15375,-15369,-15363,-15362,-15183,-15180,-15165,-15158,-15153,-15150,-15149,-15144,
		-15143,-15141,-15140,-15139,-15128,-15121,-15119,-15117,-15110,-15109,-14941,-14937,-14933,-14930,-14929,-14928,
		-14926,-14922,-14921,-14914,-14908,-14902,-14894,-14889,-14882,-14873,-14871,-14857,-14678,-14674,-14670,-14668,
		-14663,-14654,-14645,-14630,-14594,-14429,-14407,-14399,-14384,-14379,-14368,-14355,-14353,-14345,-14170,-14159,
		-14151,-14149,-14145,-14140,-14137,-14135,-14125,-14123,-14122,-14112,-14109,-14099,-14097,-14094,-14092,-14090,
		-14087,-14083,-13917,-13914,-13910,-13907,-13906,-13905,-13896,-13894,-13878,-13870,-13859,-13847,-13831,-13658,
		-13611,-13601,-13406,-13404,-13400,-13398,-13395,-13391,-13387,-13383,-13367,-13359,-13356,-13343,-13340,-13329,
		-13326,-13318,-13147,-13138,-13120,-13107,-13096,-13095,-13091,-13076,-13068,-13063,-13060,-12888,-12875,-12871,
		-12860,-12858,-12852,-12849,-12838,-12831,-12829,-12812,-12802,-12607,-12597,-12594,-12585,-12556,-12359,-12346,
		-12320,-12300,-12120,-12099,-12089,-12074,-12067,-12058,-12039,-11867,-11861,-11847,-11831,-11798,-11781,-11604,
		-11589,-11536,-11358,-11340,-11339,-11324,-11303,-11097,-11077,-11067,-11055,-11052,-11045,-11041,-11038,-11024,
		-11020,-11019,-11018,-11014,-10838,-10832,-10815,-10800,-10790,-10780,-10764,-10587,-10544,-10533,-10519,-10331,
		-10329,-10328,-10322,-10315,-10309,-10307,-10296,-10281,-10274,-10270,-10262,-10260,-10256,-10254};
	const char pystr[396][7] = {"a","ai","an","ang","ao","ba","bai","ban","bang","bao","bei","ben","beng","bi","bian","biao",
		"bie","bin","bing","bo","bu","ca","cai","can","cang","cao","ce","ceng","cha","chai","chan","chang","chao","che","chen",
		"cheng","chi","chong","chou","chu","chuai","chuan","chuang","chui","chun","chuo","ci","cong","cou","cu","cuan","cui",
		"cun","cuo","da","dai","dan","dang","dao","de","deng","di","dian","diao","die","ding","diu","dong","dou","du","duan",
		"dui","dun","duo","e","en","er","fa","fan","fang","fei","fen","feng","fo","fou","fu","ga","gai","gan","gang","gao",
		"ge","gei","gen","geng","gong","gou","gu","gua","guai","guan","guang","gui","gun","guo","ha","hai","han","hang",
		"hao","he","hei","hen","heng","hong","hou","hu","hua","huai","huan","huang","hui","hun","huo","ji","jia","jian",
		"jiang","jiao","jie","jin","jing","jiong","jiu","ju","juan","jue","jun","ka","kai","kan","kang","kao","ke","ken",
		"keng","kong","kou","ku","kua","kuai","kuan","kuang","kui","kun","kuo","la","lai","lan","lang","lao","le","lei",
		"leng","li","lia","lian","liang","liao","lie","lin","ling","liu","long","lou","lu","lv","luan","lue","lun","luo",
		"ma","mai","man","mang","mao","me","mei","men","meng","mi","mian","miao","mie","min","ming","miu","mo","mou","mu",
		"na","nai","nan","nang","nao","ne","nei","nen","neng","ni","nian","niang","niao","nie","nin","ning","niu","nong",
		"nu","nv","nuan","nue","nuo","o","ou","pa","pai","pan","pang","pao","pei","pen","peng","pi","pian","piao","pie",
		"pin","ping","po","pu","qi","qia","qian","qiang","qiao","qie","qin","qing","qiong","qiu","qu","quan","que","qun",
		"ran","rang","rao","re","ren","reng","ri","rong","rou","ru","ruan","rui","run","ruo","sa","sai","san","sang",
		"sao","se","sen","seng","sha","shai","shan","shang","shao","she","shen","sheng","shi","shou","shu","shua",
		"shuai","shuan","shuang","shui","shun","shuo","si","song","sou","su","suan","sui","sun","suo","ta","tai",
		"tan","tang","tao","te","teng","ti","tian","tiao","tie","ting","tong","tou","tu","tuan","tui","tun","tuo",
		"wa","wai","wan","wang","wei","wen","weng","wo","wu","xi","xia","xian","xiang","xiao","xie","xin","xing",
		"xiong","xiu","xu","xuan","xue","xun","ya","yan","yang","yao","ye","yi","yin","ying","yo","yong","you",
		"yu","yuan","yue","yun","za","zai","zan","zang","zao","ze","zei","zen","zeng","zha","zhai","zhan","zhang",
		"zhao","zhe","zhen","zheng","zhi","zhong","zhou","zhu","zhua","zhuai","zhuan","zhuang","zhui","zhun","zhuo",
		"zi","zong","zou","zu","zuan","zui","zun","zuo"};

	int chrasc = 0;         

	char* pcReturnString = NULL;

	//unicode转换为ANSI
	int length = WideCharToMultiByte(CP_ACP, 0, chrstr, -1, 0, 0, 0, 0 ); 
	char* nowchar = new char[length+1];
	memset(nowchar,0,length+1);
	WideCharToMultiByte( CP_ACP, 0, chrstr, -1, nowchar,length, 0, 0 );

	//转换ANSI,字符部分不变，汉字转换成相应的拼音
	char *returnstr = new char[6*length +1];
	memset(returnstr,0,6*length +1);

	int offset = 0; 
	for (int j = 0; j < length;) // 循环处理字节数组
	{
		if (nowchar[j] >= 0 && nowchar[j] < 128) // 非汉字处理
		{

			returnstr[offset] = nowchar[j];
			offset++;
			j++;
			continue;
		}

		// 汉字处理
		chrasc = nowchar[j] * 256 + nowchar[j+1]+256;

		if (chrasc > 0 && chrasc < 160)
		{
			returnstr[offset]= nowchar[j];
			offset++;
			j++;
		}
		else
		{
			for (int i = (sizeof(pyvalue)/sizeof(pyvalue[0]) - 1); i >= 0; i--)
			{
				if (pyvalue[i] <= chrasc)
				{
					strcpy(returnstr+offset ,pystr[i]);

					offset +=strlen(pystr[i]);  
					break;
				}
			}
			j +=2;
		}
	}
	if(strlen(returnstr)>0)
	{
		pcReturnString = new char[strlen(returnstr)+1];
		memset(pcReturnString,0,strlen(returnstr)+1);
		strcpy(pcReturnString,returnstr);
	}
	delete []returnstr;
	delete []nowchar;

	return pcReturnString;
}

wstring CpinyinDlg::ws2s(string strSrc)
{
	int len;
	int slength = (int)strSrc.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r; 
}

BOOL CpinyinDlg::InitializePinyinMap()
{
	PYmap.clear();

	CStdioFile sfile;
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定<ctpye.h>中字符处理方式

	if(!sfile.Open(_T("mapfile.txt"), CStdioFile::modeRead))
	{
		return FALSE;
	}

	CString strLine;
	while(sfile.ReadString(strLine))
	{
		strLine.Trim();

		if(!strLine.IsEmpty())
		{
			CString strKey, strVlue;
			TCHAR split = ' ';
			int nBlank = strLine.Find(split);

			if(nBlank > 0)
			{
				strKey = strLine.Left(nBlank);
				strVlue = strLine.Right( strLine.GetLength() - nBlank - 1 );

				nBlank = strVlue.Find(split);
				while(nBlank > 0)
				{
					PYmap.insert(std::make_pair(strKey, strVlue.Left(nBlank)));
					strVlue = strVlue.Right( strVlue.GetLength() - nBlank - 1 );
					nBlank = strVlue.Find(split);
				}
			}
			PYmap.insert(std::make_pair(strKey, strVlue));
		}
	}

	sfile.Close();
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定

	return TRUE;
}

/*
@	汉字的unicode码与拼音的互转
*/
CString CpinyinDlg::EncodeChinese(CString InputStr)
{
	int cur;
	CString tempstr,returnstr;
	for(int i=0;i<InputStr.GetLength();i++)
	{
		cur=InputStr.GetAt(i);
		tempstr.Format(L"%04X",cur);
		returnstr=returnstr+tempstr;
	}
	return returnstr;
}

CString CpinyinDlg::DecodeChinese(CString InputStr)
{
	CString tempstr,returnstr;
	for(int i=0;i<InputStr.GetLength();i+=4)
	{
		CString str = InputStr.Mid(i,4);
		wchar_t *str1 = str.GetBuffer();
		int x = (int)_tcstol(str, &str1, 16);//十六进制 

		tempstr.Format(L"%c",x);
		returnstr=returnstr+tempstr;
	}
	return returnstr;
}
//end

/*
@	获取拼音的全拼跟简拼
*/
BOOL CpinyinDlg::GetSimpleAndFull(CString InputStr, CString &SimpleStr, CString &FullStr)
{
	if (InputStr.IsEmpty())
	{
		return FALSE;
	}

	CString tempSimplestr, tempFullstr, tempstr;
	for (int i = 0; i < InputStr.GetLength(); i += 4)
	{
		CString str = InputStr.Mid(i, 4);
		std::multimap<CString, CString>::iterator iter = PYmap.find(str);

		if (iter != PYmap.end())
		{
			tempstr = iter->second;
		}


		tempFullstr = tempFullstr + tempstr;
		tempSimplestr = tempSimplestr + tempstr.Left(1);
	}


	FullStr = tempFullstr;
	SimpleStr = tempSimplestr;

	return TRUE;
}

void CpinyinDlg::OnCbnEditchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ComboBox.GetWindowText(m_csComboBox);
	for (int i = 0; i <= m_ComboBox.GetCount(); i++)
	{
		m_ComboBox.DeleteString(0);
	}
// 	m_ComboBox.SetWindowText(L"");
// 	m_ComboBox.SetWindowText(m_csComboBox.GetString());
	std::vector<CString> SearchVec;
	SearchVec.clear();

	if (!m_csComboBox.IsEmpty())
	{
		std::multimap<CString, CString>::iterator iter = PYHelpermap.begin();
		for (; iter != PYHelpermap.end(); iter++)
		{
			std::wstring wstrName = iter->first;
			if (wstrName.find(m_csComboBox) != string::npos && wstrName.find_first_of(m_csComboBox) == 0)
			{
				SearchVec.push_back(iter->second);
			}
		}
	}
	else
		SearchVec.clear();

	sort(SearchVec.begin(), SearchVec.end());
	SearchVec.erase(unique(SearchVec.begin(), SearchVec.end()), SearchVec.end());

	std::vector<CString>::iterator iter_vec = SearchVec.begin();
	for (; iter_vec != SearchVec.end(); iter_vec++)
	{
		m_ComboBox.AddString(iter_vec->GetString());
	}
}

void CpinyinDlg::OnCbnDropdownCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CpinyinDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//edit有变化    根据变化去表中查找相应数据，然后添加到查找结果表中
	CString csSearch;
	m_SearchEdit.GetWindowText(csSearch);
	csSearch.Trim();

	if (L"" != csSearch)
	{
		std::vector<CString> vecSearch;
		vecSearch.clear();

		std::multimap<CString, CString>::iterator iter = PYHelpermap.begin();
		for (; iter != PYHelpermap.end(); iter++)
		{
			std::wstring wstrSearchKey = iter->first;
			if (wstrSearchKey.find(csSearch.GetString()) != string::npos && wstrSearchKey.find_first_of(csSearch.GetString()) == 0)
			{
				vecSearch.push_back(iter->second);
			}
		}

		sort(vecSearch.begin(), vecSearch.end());
		vecSearch.erase(unique(vecSearch.begin(), vecSearch.end()), vecSearch.end());


		int nTotal = m_listSearchResult.GetItemCount();
		for(int i = 0;i < nTotal;i++)
		{
			m_listSearchResult.DeleteItem(0);
		}
		std::vector<CString>::iterator it = vecSearch.begin();

		for (int i =0; i < vecSearch.size(); i++)
		{
			m_listSearchResult.InsertItem(i, vecSearch[i].GetString());
		}
	}
	else
	{
		int nTotal = m_listSearchResult.GetItemCount();
		for(int i = 0;i < nTotal;i++)
		{
			m_listSearchResult.DeleteItem(0);
		}
	}
}

void CpinyinDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csAddValue;
	m_AddEdit.GetWindowText(csAddValue);

	if (L"" != csAddValue)
	{
		CString pyValue;
		pyValue = EncodeChinese(csAddValue);
		CString csFullVal,csSimpleVal;
		GetSimpleAndFull(pyValue, csSimpleVal, csFullVal);

		PYHelpermap.insert(make_pair(csSimpleVal, csAddValue));
		PYHelpermap.insert(make_pair(csFullVal, csAddValue));
	}

	m_AddEdit.SetWindowText(L"");
}

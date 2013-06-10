========================================================================
    WIN32 应用程序：Mousee 项目概述
========================================================================

技术：

1.Mouse low level hook 
	
	捕获鼠标移动 滚轮消息消息

2.透明窗口，窗口截图
  

3.鼠标所在位置 HWND 和 Window Class 的获取
	
	o   WindowFromPoint  
		The WindowFromPoint function retrieves a handle to the window occupying a particular point on the screen.
	
	o   ChildWindowFromPoint\ChildWindowFromPointEx
		ChildWindowFromPoint and ChildWindowFromPointEx functions retrieve a handle to the child window occupying a particular point in the parent window's client area. Although ChildWindowFromPointEx can ignore invisible, disabled, and transparent child windows, ChildWindowFromPoint cannot.

	o   RealChildWindowFromPoint

参考（Microsoft MSDN ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.chs/winui/winui/windowsuserinterface/windowing/windows/aboutwindows.htm#position）
	
	
Parent or Owner Window Handle
	
	A window can have a parent window. A window that has a parent is called a [child window]. 
	The parent window provides the coordinate system used for positioning a child window. 
	Having a parent window affects aspects of a window's appearance; for example, a child 
	window is clipped so that no part of the child window can appear outside the borders of 
	its parent window. 
	
Top-level windows

	A window that has no parent, or whose parent is the desktop window, 
	is called a top-level window. An application uses the EnumWindows() function to obtain a 
	handle to each of its top-level windows. EnumWindows passes the handle to each top-level 
	window, in turn, to an application-defined callback function, EnumWindowsProc.

	A window can own, or be owned by, another window. An owned window always appears in front 
	of its owner window, is hidden when its owner window is minimized, and is destroyed when 
	its owner window is destroyed. For more information, see Owned Windows.

IsWindow	

	The IsWindow function determines whether a window handle identifies a valid, 
	existing window. There are special constants that can replace a window handle
	 in certain functions. For example, an application can use HWND_BROADCAST in 
	 the SendMessage and SendMessageTimeout functions, or HWND_DESKTOP in the
	  MapWindowPoints function.
  
3.1 测试鼠标所在为何位置？

	LRESULT curPosition = SendMessage( 
		hParentWnd, 
		WM_NCHITTEST, 
		0, 
		MAKELPARAM(wndPos.x, wndPos.y) 
		);
 
4.当鼠标移出托盘菜单范围并点击菜单没有消失

	在 TrackPopMenu 之前调用 SetForegroundWindow 设置菜单的 Owner 为 Foreground

5.自动运行

	注册表操作
	RegOpenKeyEx 不会尝试创建新的键值

6.字符查找
    ANSI MBCS: strchr
    Unicode  : wcschr
    TCHAR	 : _tcsrchr
    
7.Static control 
	Static control 具有很多种类型：
	o Simple Graphics Static Control
	o Text Static Control
	o Image Static Controls
	o Owner-Drawn Static Control
	
	显示文本使用 Text Static Control 类型，并指定窗口风格为
	SS_LEFTNOWORDWRAP, SS_LEFT, SS_CENTER, SS_RIGHT, and SS_SIMPLE，
	
	注意：
	1) 不要指定SS_WHITEFRAME风格，该风格数据Simple Graphics Static Control的
	   导致显示白框，文本不会显示出来
	2)指定SS_SIMPLE风格导致SetWindowText的时候，Static Control 不会rearranges 文本
	
8.字体颜色、背景透明

    TextOut输出字体背景透明，使用
		SetBkMode(hdc, TRANSPARENT ); 
		
SetBkMode
		The SetBkMode function sets the background mix mode of the specified device context.
		The background mix mode is used with text, hatched brushes, and pen styles that are not solid lines. 

		int SetBkMode(
		  HDC hdc,      // handle to DC
		  int iBkMode   // background mode
		);

hdc
		Handle to the device context. 
iBkMode
		OPAQUE			Background is filled with the current background color before the text, hatched brush, or pen is drawn. 
		TRANSPARENT		Background remains untouched. 

	设置背景混合模式。
	
设置背景颜色

	SetBkColor(hdc, RGB(23,43,34));
	
9. 只允许一个程序实例运行
Your WinMain function can also limit your application to a single instance. 
Create a named mutex using the CreateMutex function. If GetLastError returns ERROR_ALREADY_EXISTS, 
another instance of your application exists (it created the mutex) and you should exit WinMain.

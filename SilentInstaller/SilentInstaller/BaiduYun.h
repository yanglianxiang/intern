#pragma once

#include "Installer.h"

// BaiduYun

class BaiduYun : public Installer, CWnd
{
	DECLARE_DYNAMIC(BaiduYun)

public:
	BaiduYun();
	virtual ~BaiduYun();

// constants
private:
	const string PROCESS_NAME;
	const string APP_NAME;

	const string EXIST_WIN_TITLE;       // 已安装时弹出的窗口写的是APP_NAME，但是实际不是
	const string INSTALL_WIN_TITLE;
	const string LOGIN_WIN_TITLE;

	// MessageBox 上的 "确定" 或 "是" 按钮
	const int OY_BTN_X;                 // 265
	const int OY_BTN_Y;                 // 175

	// MessageBox 上的 "取消" 或 "否" 按钮 
	const int CN_BTN_X;                 // 325
	const int CN_BTN_Y;                 // 175

	// Customize install button，自定义安装按钮
	const int CINSTALL_BTN_X;
	const int CINSTALL_BTN_Y;

	// 安装路径文本框
	const string PATH_CTRL_CLSNAME;

	// Install button，安装按钮
	const int INSTALL_BTN_X;
	const int INSTALL_BTN_Y;

	// Finish button，完成按钮
	const int FINISH_BTN_X;
	const int FINISH_BTN_Y;

	// 貌似只能通过长度来区分这两个控件了
	const int USR_EDIT_LENGTH;          // 163
	const int PSWD_EDIT_LENGTH;         // 183

	// 记住密码CheckBox
	const int REM_PSWD_CB_X;            // 130
	const int REM_PSWD_CB_Y;            // 180

	// Login button, 登陆按钮
	const int LOGIN_BTN_X;
	const int LOGIN_BTN_Y;

	const string CONFIG_WND_CLSNAME;
	const int    CONFIG_WND_WIDTH;      // 设置本地同步文件夹路径的窗口宽度

	// 设置本地同步文件夹路径的控件
	const int SYNC_PATH_EDIT_LENGTH;    // 336

	// Next button, 下一步按钮
	const int NEXT_BTN_X;
	const int NEXT_BTN_Y;

	// 显示悬浮窗口复选框
	const int SHOW_FLOAT_WND_X;         // 370
	const int SHOW_FLOAT_WND_Y;         // 280

	// 配置确定按钮
	const int CONFIG_OK_BTN_X;          // 410
	const int CONFIG_OK_BTN_Y;          // 320

	// 新手引导窗口
	const string WIZARD_NAME;

	// 跳过向导按钮
	const int SKIP_BTN_X;               // 330
	const int SKIP_BTN_Y;               // 320

public:
	virtual bool install(VirtualDesktop *vDesktop, string path);
	
private:
	bool isInstalled();
	void selectMode();
	void changeSettings(string path);
	void complete();            // 完成安装
	void login(string usr, string pswd);
	void config(string path);
	HWND findConfigWnd();
	void configSyncDir(string path);
	void confirmUseExistDir();  // 将已存在目录设为同步目录
	void walkWizard();          // 此处直接跳过向导，也可以完全不用处理
	void finish();              // 结束整个安装及设置等过程

public:
	void kill();
	string retrieveInstallDir();

protected:
	DECLARE_MESSAGE_MAP()
};



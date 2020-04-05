; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLauncherCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Launcher.h"
CDK=Y

ClassCount=6
Class1=CLauncherCtrl
Class2=CLauncherPropPage

ResourceCount=5
LastPage=0
Resource1=IDD_INSTALL_STEP1_DLG
Class3=CInstallProperty
Resource2=IDD_INSTALL_STEP2_DLG
Resource3=IDD_PROPPAGE_LAUNCHER
Class4=CInstallStep1
Class5=CInstallStep2
Class6=CUpdateDlg
Resource4=IDD_ABOUTBOX_LAUNCHER
Resource5=IDD_UPDATE_DLG

[CLS:CLauncherCtrl]
Type=0
HeaderFile=LauncherCtl.h
ImplementationFile=LauncherCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CLauncherCtrl

[CLS:CLauncherPropPage]
Type=0
HeaderFile=LauncherPpg.h
ImplementationFile=LauncherPpg.cpp
Filter=D

[DLG:IDD_ABOUTBOX_LAUNCHER]
Type=1
Class=CUpdateDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_LAUNCHER]
Type=1
Class=CLauncherPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_INSTALL_STEP1_DLG]
Type=1
Class=CInstallStep1
ControlCount=5
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_INSTALL_PATH_EDIT,edit,1342244992
Control4=IDC_STATIC,button,1342177287
Control5=IDC_FIND_BTN,button,1342242816

[DLG:IDD_INSTALL_STEP2_DLG]
Type=1
Class=CInstallStep2
ControlCount=8
Control1=IDC_DOWN_PROGRESS,msctls_progress32,1342177281
Control2=IDC_UNZIP_PROGRESS,msctls_progress32,1342177281
Control3=IDC_STATIC,button,1342177287
Control4=IDC_INSTALL_BTN,button,1342242816
Control5=IDC_DOWN_STATIC,static,1342308352
Control6=IDC_UNZIP_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CInstallProperty]
Type=0
HeaderFile=InstallProperty.h
ImplementationFile=InstallProperty.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CInstallProperty

[CLS:CInstallStep1]
Type=0
HeaderFile=InstallStep1.h
ImplementationFile=InstallStep1.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_FIND_BTN
VirtualFilter=idWC

[CLS:CInstallStep2]
Type=0
HeaderFile=InstallStep2.h
ImplementationFile=InstallStep2.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CInstallStep2
VirtualFilter=idWC

[CLS:CUpdateDlg]
Type=0
HeaderFile=UpdateDlg.h
ImplementationFile=UpdateDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CANCEL

[DLG:IDD_UPDATE_DLG]
Type=1
Class=CUpdateDlg
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_UPDATE_VER_PROGRESS,msctls_progress32,1342177281
Control3=IDC_UPDATE_DOWN_PROGRESS,msctls_progress32,1342177281
Control4=IDC_UPDATE_UNZIP_PROGRESS,msctls_progress32,1342177281
Control5=IDC_UPDATE_DOWN_STATIC,static,1342308352
Control6=IDC_UPDATE_UNZIP_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_UPDATE_VER_STATIC,static,1342308352
Control11=IDC_CANCEL,button,1342242816


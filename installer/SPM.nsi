; Script generated by the HM NIS Edit Script Wizard.

; generate version
!include version.nsi

; Standard installer  options
SetCompressor /FINAL /SOLID lzma
SetDatablockOptimize 	on
CRCCheck on ;CRC check
SilentInstall normal ;normal install
SilentUnInstall normal ;uninstall quietly
XPStyle on ;graphic
BrandingText "http://www.niwa.co.nz"

;includes
!include Modules\EnvVarUpdate.nsh
!include Modules\fileassoc.nsh
!include "WordFunc.nsh"
!insertmacro VersionCompare

; Define multiuser install options
!define MULTIUSER_EXECUTIONLEVEL Highest
!include "MultiUser.nsh"

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "SPM"
!define PRODUCT_PUBLISHER "NIWA"
!define PRODUCT_WEB_SITE "http://www.niwa.co.nz"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\spm.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

; check installer is not already running
Function .onInit
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "SPMinstaller") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 +3
    MessageBox MB_OK|MB_ICONEXCLAMATION "The ${PRODUCT_NAME} installer is already running."
    Abort
  ;Check for admin rights
  UserInfo::GetOriginalAccountType
  Pop $0
  StrCmp $0 "Admin" +3 0
		MessageBox MB_OK "You need to have adminstrator rights to install ${PRODUCT_NAME}. Aborting install."
		abort
  ;Force install for all users
  !insertmacro MULTIUSER_INIT
  ;Check earlier installation
  init.restart:
  ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "UninstallString"
  ReadRegStr $0 HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "DisplayVersion"
  IfFileExists $R0 +1 init.done
    StrCmp $0 ${PRODUCT_VERSION} init.Same
    MessageBox MB_YESNO|MB_ICONQUESTION "Setup has found another version of ${PRODUCT_NAME} (v$0) installed on your system.$\nWould you like to remove it before continuing with the installation of version ${PRODUCT_VERSION}?" \
      IDYES init.uninst
    MessageBox MB_OK "${PRODUCT_NAME} v${PRODUCT_VERSION} setup will now exit"
    Quit
  init.uninst:
    ClearErrors
    ReadRegStr $0 HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "UninstallString"
    IfErrors init.done
      Pop $R1
      StrCmp $0 2 Quit +1
      ExecWait '"$0" _?=$INSTDIR'
      ;'"$INSTDIR\uninstall.exe" _?=$INSTDIR'
      GOTO init.restart
  init.Same:
    MessageBox MB_YESNO|MB_ICONQUESTION "${PRODUCT_NAME} v$0 seems to be already installed on your system.$\nDo you want to uninstall and continue?" \
      IDYES init.uninst
    MessageBox MB_OK "${PRODUCT_NAME} v${PRODUCT_VERSION} setup will now exit"
    Quit
  Quit:
    Quit
  init.done:
FunctionEnd

; MUI 1.67 compatible ------
!include "MUI.nsh"
; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "..//Source//SPM.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "CPLv1.0.txt"
;Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY

; Start menu page
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Spatial Population Model (SPM)"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES

; Finish page
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Readme.txt"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
; MUI end ------

Name "${PRODUCT_NAME} v${PRODUCT_VERSION}"
OutFile "..//Build//Setup_${PRODUCT_NAME}.exe"
InstallDir "$PROGRAMFILES\SPM"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "Install program files" SEC01
SectionIn RO
  ;LogSet On
  ;LogText "${PRODUCT_NAME} v${PRODUCT_VERSION} install log"
  ;Logtext "==============================================\n"
  ;LogText "Install path $INSTDIR"
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "..\\Build\\windows\\spm.exe"
  File "..\\Build\\windows\\spm_unittests.exe"
  File "pthreadGC2_64.dll"
  File "run SPM.lnk"
  File "..\\Source\\SPM-file.ico"
  File "..\\Build\\SPM.pdf"
  File "..\\Source\\CPLv1.0.txt"
  File "Readme.txt"
  File "..\\Source\\SPM.ico"
  SetOutPath "$%SYSTEMROOT%"
  File "..\\Source\\SPM.ico"
SectionEnd

Section "Start menu shortcuts" SEC02
; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Run SPM.lnk" "$INSTDIR\Run SPM.lnk"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\SPM User Manual.lnk" "$INSTDIR\SPM.pdf"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Readme.lnk" "$INSTDIR\Readme.txt"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\License.lnk" "$INSTDIR\CPLv1.0.txt"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section "Associate .spm files" SEC03
  ;associate .spm files witrh notepad++
  !insertmacro APP_ASSOCIATE "spm" "SPM.textfile" "" "$INSTDIR\SPM-file.ico" "Open with notepad++" "notepad++.exe $\"%1$\""
SectionEnd

!define APP_HOME $INSTDIR
Section "Modify path for SPM" SEC04
  ; update path to install directory
  ${EnvVarUpdate} $0 "PATH" "R" "HKLM" "$INSTDIR"  ; Remove path of old rev
  ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR"  ; Append the new one
SectionEnd

Section /o "Copy example files" SEC05
  SetOutPath "$INSTDIR\\Examples"
  File /r "..\\Examples\*"
SectionEnd

Section /o "Copy the R library" SEC06
  SetOutPath "$INSTDIR"
  File "..\\Build\\spm_2.0.1.zip"
SectionEnd

Section /o "Copy the syntax files" SEC08
  SetOutPath "$INSTDIR"
  File "..\\Build\\SPM.syn"
  File "..\\Build\\SPM.xml"
SectionEnd

LangString DESC_SEC01 ${LANG_ENGLISH} "Copy the ${PRODUCT_NAME} v${PRODUCT_VERSION} program files to the installation directory (required)"
LangString DESC_SEC02 ${LANG_ENGLISH} "Add icons to your start menu for easy access"
LangString DESC_SEC03 ${LANG_ENGLISH} "Associate .spm files with notepad++.exe"
LangString DESC_SEC04 ${LANG_ENGLISH} "Add the installation directory of ${PRODUCT_NAME} to your Windows PATH? (recommended)"
LangString DESC_SEC05 ${LANG_ENGLISH} "Copy the example files"
LangString DESC_SEC06 ${LANG_ENGLISH} "Copy the R ${PRODUCT_NAME} library"
LangString DESC_SEC08 ${LANG_ENGLISH} "Copy the syntax files (SPM.syn for TextPad and SPM.xml for Notepad++)"

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} $(DESC_SEC01)
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} $(DESC_SEC02)
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC03} $(DESC_SEC03)
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC04} $(DESC_SEC04)
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC05} $(DESC_SEC05)
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC06} $(DESC_SEC06)
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC08} $(DESC_SEC08)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

Section -AdditionalIcons
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\spm.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Name" "${PRODUCT_NAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\spm.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegDword ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "NoModify" 1
  WriteRegDword ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "NoRepair" 1
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "HelpLink" "http://www.niwa.co.nz"
  ;DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SPM"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  !insertmacro MULTIUSER_UNINIT
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\SPM.ico"
  Delete "$INSTDIR\Readme.txt"
  Delete "$INSTDIR\CPLv1.0.txt"
  Delete "$INSTDIR\SPM.pdf"
  Delete "$INSTDIR\SPM-file.ico"
  Delete "$INSTDIR\spm.exe"
  Delete "$INSTDIR\spm_unittests.exe"
  Delete "$INSTDIR\pthreadGC2_64.dll"
  Delete "$INSTDIR\Run SPM.lnk"
  Delete "$INSTDIR\Install.log"
  Delete "$INSTDIR\SPM.syn"
  Delete "$INSTDIR\SPM.xml"
  Delete "$INSTDIR\spm_1.1.zip"
  RmDir /r "$INSTDIR\examples"
  
  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Readme.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\SPM User Manual.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Run SPM.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\License.lnk"
  
  RMDir "$SMPROGRAMS\$ICONS_GROUP"
  RMDir "$INSTDIR"

  ${un.EnvVarUpdate} $0 "PATH" "R" "HKLM" "$INSTDIR"      ; Remove path of latest rev

  !insertmacro APP_UNASSOCIATE "SPM" "SPM.textfile"
  
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd


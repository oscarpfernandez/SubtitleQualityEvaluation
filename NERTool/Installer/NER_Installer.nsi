;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name and file
  Name "NER Tool Application"
  OutFile "NERTool.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\NERTool"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\NERTool" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "Spanish"
 
;Select the language... 
Function .onInit
	InitPluginsDir
	File /oname=$PLUGINSDIR\splash.bmp "pics\splash_brand.bmp"
	advsplash::show 2000 600 400 0x04025C $PLUGINSDIR\splash
	Pop $0 
    Delete $PLUGINSDIR\splash.bmp

  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

;--------------------------------
;Installer Sections

Section "NER Tool Components" SecNERBase

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  
  ;Store installation folder
  WriteRegStr HKCU "Software\NERTool" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecNERBase ${LANG_ENGLISH} "NER Tool base configuration."
  LangString DESC_SecNERBase ${LANG_SPANISH} "Configuracion base de NER Tool."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecNERBase} $(DESC_SecNERBase)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\NERTool"

SectionEnd
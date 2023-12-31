# Microsoft Developer Studio Project File - Name="vorbishq" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vorbishq - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vorbishq.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vorbishq.mak" CFG="vorbishq - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vorbishq - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vorbishq - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vorbishq - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VORBISHQ_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /GX /Zd /O2 /D "NDEBUG" /D "_USRDLL" /D "VORBISHQ_EXPORTS" /D BYTE_ORDER=1 /D LITTLE_ENDIAN=1 /D BIG_ENDIAN=0 /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40e /d "NDEBUG"
# ADD RSC /l 0x40e /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /map /machine:I386 /out:"../release/vorbishq.plg"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "vorbishq - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VORBISHQ_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /Gm /GX /ZI /Od /D "_DEBUG" /D "_USRDLL" /D "VORBISHQ_EXPORTS" /D BYTE_ORDER=1 /D LITTLE_ENDIAN=1 /D BIG_ENDIAN=0 /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40e /d "_DEBUG"
# ADD RSC /l 0x40e /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../debug/vorbishq.plg" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "vorbishq - Win32 Release"
# Name "vorbishq - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\vorbislq\ogg.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\oggembedded.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\oggpacket.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\stdafx.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\vorbis.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\vorbislq\vorbis.h
# End Source File
# End Group
# Begin Group "tremor"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\vorbislq\tremor\asm_arm.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\backends.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\bitwise.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\block.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\codebook.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\codebook.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\codec_internal.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\config_types.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\floor0.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\floor1.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\framing.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\info.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\ivorbiscodec.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\lsp_lookup.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\mapping0.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\mdct.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\mdct_lookup.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\mdctvorbis.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\misc.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\ogg.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\os.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\os_types.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\registry.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\registry.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\res012.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\sharedbook.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\synthesis.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\window.c
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\window.h
# End Source File
# Begin Source File

SOURCE=..\vorbislq\tremor\window_lookup.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# End Group
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="SkewT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SkewT - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SkewT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SkewT.mak" CFG="SkewT - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SkewT - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SkewT - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SkewT - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "c:/Binaries/Aspen/Lib/Release"
# PROP Intermediate_Dir "c:/Binaries/Aspen/Obj/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../" /I "../../" /I "c:/Projects/Netcdfpp" /I "c:/Projects/BSpline" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SkewT - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "c:/Binaries/Aspen/Lib/Debug"
# PROP Intermediate_Dir "c:/Binaries/Aspen/Obj/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../" /I "../../" /I "c:/Projects/Netcdfpp" /I "c:/Projects/BSpline" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"c:/projects/lib/debug/SkewT.lib"

!ENDIF 

# Begin Target

# Name "SkewT - Win32 Release"
# Name "SkewT - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Adiabats.cpp
# End Source File
# Begin Source File

SOURCE=.\IsoMR.cpp
# End Source File
# Begin Source File

SOURCE=.\IsoPleth.cpp
# End Source File
# Begin Source File

SOURCE=.\IsoPress.cpp
# End Source File
# Begin Source File

SOURCE=.\IsoTherms.cpp
# End Source File
# Begin Source File

SOURCE=.\PAdiabats.cpp
# End Source File
# Begin Source File

SOURCE=.\PresRect.cpp
# End Source File
# Begin Source File

SOURCE=.\Rect.cpp
# End Source File
# Begin Source File

SOURCE=.\SkewT.cpp
# End Source File
# Begin Source File

SOURCE=.\SkewTAdapter.cpp
# End Source File
# Begin Source File

SOURCE=.\SkewTMetFormulas.cpp
# End Source File
# Begin Source File

SOURCE=.\SkewTRect.cpp
# End Source File
# Begin Source File

SOURCE=.\SkewTtrace.cpp
# End Source File
# Begin Source File

SOURCE=.\WindBarb.cpp
# End Source File
# Begin Source File

SOURCE=.\WindBarbs.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Adiabats.h
# End Source File
# Begin Source File

SOURCE=.\IsoMR.h
# End Source File
# Begin Source File

SOURCE=.\IsoPleth.h
# End Source File
# Begin Source File

SOURCE=.\IsoPress.h
# End Source File
# Begin Source File

SOURCE=.\IsoTherms.h
# End Source File
# Begin Source File

SOURCE=.\PAdiabats.h
# End Source File
# Begin Source File

SOURCE=.\PresRect.h
# End Source File
# Begin Source File

SOURCE=.\Rect.h
# End Source File
# Begin Source File

SOURCE=.\SkewT.h
# End Source File
# Begin Source File

SOURCE=.\SkewTAdapter.h
# End Source File
# Begin Source File

SOURCE=.\SkewTdefs.h
# End Source File
# Begin Source File

SOURCE=.\SkewTdoxygen.h
# End Source File
# Begin Source File

SOURCE=.\SkewTMetFormulas.h
# End Source File
# Begin Source File

SOURCE=.\SkewTRect.h
# End Source File
# Begin Source File

SOURCE=.\SkewTtrace.h
# End Source File
# Begin Source File

SOURCE=.\WindBarb.h
# End Source File
# Begin Source File

SOURCE=.\WindBarbs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project

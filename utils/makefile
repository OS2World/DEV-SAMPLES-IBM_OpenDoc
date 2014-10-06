# @(#) 1.19.1.16 os2/src/samples/utils/makefile.mak, odutilspart, od96os2, odos29712d 2/11/97 08:59:30 [ 3/21/97 17:39:47 ]
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odsutils
#
#   CLASSES: none
#
#   ORIGINS: 27
#
#
#   (C) COPYRIGHT International Business Machines Corp. 1995,1996
#   All Rights Reserved
#   Licensed Materials - Property of IBM
#   US Government Users Restricted Rights - Use, duplication or
#   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#
#   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
#   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
#   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
#   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
#   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
#   OR PERFORMANCE OF THIS SOFTWARE.
#
#====END_GENERATED_PROLOG========================================

# If you wish to add to the existing compile and link flags, you can
# do it with these macros

ExtraSOMCompileOptions =

ExtraCompileOptions =

ExtraLinkOptions =


# ===================================================================
# Subdirectories you want nmake to visit
Subdirs = 

# include to define the iodutils macro
!include $(ODSRC)/src/iodduals.mak

# ===================================================================
# Targets

# IdlTargets = List all the idls
# HdrTargets = List all the C++ headers
# MsgTargets = List all the message catalogs
# LibTargets = List all export libraries to be built
# DllTargets = List all shared libraries to be built
#
# The Reg* and File*  macros are used to generate a table of contents
# and an install package


IdlTargets = iodlink.idl iodprint.idl iodscrol.idl

HdrTargets = AltPoint.h \
	AltPoly.h \
	BArray.h \
	ODExcept.h \
	FlipEnd.h \
	FocusLib.h \
	iodprint.hpp \
	iodscrol.hpp \
	IText.h \
	LineOps.h \
	ODDebug.h \
	ODMath.h \
	ODMemory.h \
	ODMvcLnk.h \
	ODUtils.h \
	StorUtil.h \
	StdTypIO.h \
	TempIter.h \
	TempObj.h \
	TempObj.th \
	TempRef.th \
	WinUtils.h

MsgTargets =

RcTargets =  iodutils.rc

LibTargets = $(ODSRC)/lib/$(iodutils).$(LibSuffix)

DllTargets = $(ODSRC)/dll/$(iodutils).dll


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.
 
!include $(ODSRC)/src/Platform.mak
 
 
# ===================================================================
# Rules

samputilObjList = \
	AltPoint.$(Obj) \
	AltPoly.$(Obj) \
	BArray.$(Obj) \
	ODExcept.$(Obj) \
	FlipEnd.$(Obj) \
	FocusLib.$(Obj) \
	iodlink.$(Obj) \
	iodprint.$(Obj) \
	iodscrol.$(Obj) \
	IText.$(Obj) \
	LineOps.$(Obj) \
	ODMathW.$(Obj) \
	ODDebug.$(Obj) \
	ODUtils.$(Obj) \
!IF "$(Platform)"=="os2"
	qprintf.$(Obj) \
!ENDIF
	StorUtil.$(Obj) \
	StdTypIO.$(Obj) \
	TempIter.$(Obj) \
	TempObj.$(Obj) \
	WinUtils.$(Obj)

iodlink.$(Obj) : iodlink.xih

iodprint.$(Obj) : iodprint.xih iodprint.hpp

iodscrol.$(Obj) : iodscrol.xih iodscrol.hpp


samputilLibList = \
!IF "$(Platform)"=="win32"
	{$(LIB)}msgdll.$(LibSuffix) \
	{$(LIB)}COMDLG32.$(LibSuffix) \
!ENDIF
!IF "$(Platform)"=="os2"
	{$(LIB)}oddataX.$(LibSuffix) \
!ENDIF
	{$(LIB)}odcore.$(LibSuffix) \
	{$(LIB)}odimagng.$(LibSuffix) \
	{$(LIB)}odlayout.$(LibSuffix) \
	{$(LIB)}odstorag.$(LibSuffix) \
	{$(LIB)}odui.$(LibSuffix) \
	{$(LIB)}odmsgcat.$(LibSuffix) \
	{$(LIB)}somtk.$(LibSuffix)



$(ODSRC)/dll/$(iodutils).dll :  $(ODSRC)/lib/$(iodutils).$(Exp) \
	$(samputilObjList) \
	$(samputilLibList)
	@$(BuildDllWithRes) "RecFile=IODUtils.res" BuildDllRule


$(ODSRC)/lib/$(iodutils).$(Def) :  $(samputilObjList)
	@$(BuildDef)


$(ODSRC)/lib/$(iodutils).$(LibSuffix) : \
!IFDEF CPPMAIN
	$(ODSRC)/lib/$(iodutils).$(Def) \
!ENDIF
	$(samputilObjList)
	@$(BuildLib)

# end of file

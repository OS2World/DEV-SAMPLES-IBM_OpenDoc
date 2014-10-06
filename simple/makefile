# @(#) 1.7.1.20 os2/src/samples/simple/makefile.mak, odsimplepart, od96os2, odos29712d 1/31/97 15:54:34 [ 3/21/97 17:41:43 ]
#
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odsimplepart
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
#

# If you wish to add to the existing compile and link flags, you can
# do it with these macros

ExtraSOMCompileOptions =

ExtraCompileOptions =

ExtraLinkOptions =


# ===================================================================
# Subdirectories you want nmake to visit
Subdirs = en_US


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


IdlTargets = iodsimpl.idl

RcTargets = iodsimpl.rc

HdrTargets = iodsimpl.h

MsgTargets =

LibTargets = $(ODSRC)/lib/iodsimpl.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodsimpl.dll

RegMain=iodsimpl.dll
RegIDL=iodsimpl.idl
RegClassName=SimplePart
RegKind=SimplePart
FilesDlls=iodsimpl.dll $(iodutils).dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=iodsimpl.$(LibSuffix)
FilesCats=iodsmple.cat
FilesHelps=iodsimpl.hlp
FilesStationery=

# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

simplprtObjList = iodsimpl.$(Obj)

iodsimpl.$(Obj) : iodsimpl.cpp iodsimpl.xih iodsimpl.h

simplprtLibList = \
!IF "$(Platform)"=="win32"
	{$(LIB)}msgdll.$(LibSuffix) \
!ENDIF
	{$(LIB)}somtk.$(LibSuffix) \
	{$(LIB)}$(iodutils).$(LibSuffix) \
	{$(LIB)}odimagng.$(LibSuffix) \
	{$(LIB)}odui.$(LibSuffix) \
	{$(LIB)}odlayout.$(LibSuffix) \
	{$(LIB)}odcore.$(LibSuffix) \
	{$(LIB)}odmsgcat.$(LibSuffix) \
	{$(LIB)}odstorag.$(LibSuffix)


$(ODSRC)/dll/iodsimpl.dll :  $(ODSRC)/lib/iodsimpl.$(Exp) \
	$(simplprtLibList) \
	$(simplprtObjList)
	@$(BuildDllWithRes) "RecFile=iodsimpl.res" BuildDllRule

$(ODSRC)/lib/iodsimpl.$(Def) :  iodsimpl.$(Def)
	@$(BuildCopy)


$(ODSRC)/lib/iodsimpl.$(LibSuffix) : \
!IFDEF CPPMAIN
	$(ODSRC)/lib/iodsimpl.$(Def) \
!ENDIF
	$(simplprtObjList)
	@$(BuildLib)

# end of file

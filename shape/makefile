#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odshapepart
#
#   CLASSES: none
#
#   ORIGINS: 82,27
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
# @(#) 1.16 os2/src/samples/shape/makefile.mak, odshapepart, od96os2, odos29712d 2/13/97 14:25:39 [ 3/21/97 17:44:32 ]
#

# If you wish to add to the existing compile and link flags, you can
# do it with these macros

ExtraSOMCompileOptions =

ExtraCompileOptions =

ExtraLinkOptions =


# ===================================================================
# Subdirectories you want nmake to visit
Subdirs = en_US


# ===================================================================
# Targets

# IdlTargets = List all the idls
# HdrTargets = List all the C++ headers
# MsgTargets = List all the message catalogs
# LibTargets = List all export libraries to be built
# DllTargets = List all shared libraries to be built


IdlTargets = iodshape.idl

RcTargets  = iodshape.rc

HdrTargets = iodshape.h

MsgTargets =

LibTargets = $(ODSRC)/lib/iodshape.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodshape.dll

RegMain=iodshape.dll
RegIDL=iodshape.idl
RegClassName=ShapePart
RegKind=ShapePart
FilesDlls=iodshape.dll iodutils.dll iodsimpl.dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=iodshape.$(LibSuffix)
FilesCats=iodshpe.cat
FilesHelps=iodshape.hlp
FilesStationery=


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

shapeprtObjList = iodshape.$(Obj)

iodshape.$(Obj) : iodshape.cpp iodshape.xih iodshape.h


shapeprtLibList = \
!IF "$(Platform)"=="win32"
        {$(LIB)}COMDLG32.$(LibSuffix)  \
	{$(LIB)}msgdll.$(LibSuffix) \
!ENDIF
   	{$(LIB)}iodsimpl.$(LibSuffix) \
	{$(LIB)}somtk.$(LibSuffix) \
	{$(LIB)}iodutils.$(LibSuffix) \
	{$(LIB)}odimagng.$(LibSuffix) \
	{$(LIB)}odui.$(LibSuffix) \
	{$(LIB)}odlayout.$(LibSuffix) \
	{$(LIB)}odcore.$(LibSuffix) \
	{$(LIB)}odmsgcat.$(LibSuffix) \
	{$(LIB)}odstorag.$(LibSuffix)


$(ODSRC)/dll/iodshape.dll :  $(ODSRC)/lib/iodshape.$(Exp) \
	$(shapeprtLibList) \
	$(shapeprtObjList)
	@$(BuildDllWithRes) "RecFile=iodshape.res" BuildDllRule

$(ODSRC)/lib/iodshape.$(Def) :  iodshape.$(Def)
	@$(BuildCopy)


$(ODSRC)/lib/iodshape.$(LibSuffix) : \
!IFDEF CPPMAIN
	$(ODSRC)/lib/iodshape.$(Def) \
!ENDIF
	$(shapeprtObjList)
	@$(BuildLib)

# end of file

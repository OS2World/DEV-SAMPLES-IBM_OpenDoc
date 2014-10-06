# @(#) 1.26 os2/src/samples/text/makefile.mak, odtextpart, od96os2, odos29712d 1/22/97 11:59:45 [ 3/21/97 17:45:20 ]
#
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odtextpart
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

ExtraCompileOptions    =

ExtraLinkOptions       =

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
#
# The Reg* and File*  macros are used to generate a table of contents
# and an install package


IdlTargets = iodtext.idl

RcTargets = iodtext.rc

HdrTargets =

MsgTargets =

LibTargets = $(ODSRC)/lib/iodtext.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodtext.dll

RegMain=iodtext.dll
RegIDL=iodtext.idl
RegClassName=TextPart
RegKind=TextPart
FilesDlls=iodtext.dll iodbasec.dll iodutils.dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=iodtext.$(LibSuffix)
FilesCats=iodtextm.cat
FilesStationery=

# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

textpartObjList = iodtext.$(Obj) textplat.$(Obj) \
                  paragrph.$(Obj) textmgr.$(Obj) indxcoll.$(Obj)

iodtext.$(Obj) : iodtext.xih iodtext.h iodtext.cpp textmgr.hpp
textplat.$(Obj) : textplat.cpp iodtext.h textplat.h
paragrph.$(Obj) : paragrph.cpp paragrph.hpp textplat.h
textmgr.$(Obj) : textmgr.cpp textmgr.hpp iodtext.idl iodtext.h textplat.h paragrph.hpp indxcoll.hpp
indxcoll.$(Obj) : indxcoll.cpp indxcoll.hpp

textpartLibList = \
        {$(LIB)}iodutils.$(LibSuffix) \
        {$(LIB)}iodbasec.$(LibSuffix) \
        {$(LIB)}odimagng.$(LibSuffix) \
        {$(LIB)}odui.$(LibSuffix) \
        {$(LIB)}odlayout.$(LibSuffix) \
        {$(LIB)}odcore.$(LibSuffix) \
        {$(LIB)}odstorag.$(LibSuffix) \
        {$(LIB)}odmsgcat.$(LibSuffix) \
        {$(LIB)}somtk.$(LibSuffix) \
!IF "$(Platform)"=="os2"
	{$(LIB)}CPPON30.$(LibSuffix)  \
!ENDIF
!IF "$(Platform)"=="win32"
	{$(LIB)}COMDLG32.$(LibSuffix)  \
        {$(LIB)}msgdll.$(LibSuffix)
!ENDIF

$(ODSRC)/dll/iodtext.dll :  $(ODSRC)/lib/iodtext.$(Exp) \
        $(textpartLibList) \
        $(textpartObjList)
   @$(BuildDllWithRes) "RecFile=iodtext.res" BuildDllRule


$(ODSRC)/lib/iodtext.$(Def) :  iodtext.$(Def)
   @$(BuildCopy)


$(ODSRC)/lib/iodtext.$(LibSuffix) : \
!IFDEF CPPMAIN
   $(ODSRC)/lib/iodtext.$(Def) \
!ENDIF
   $(textpartObjList)
   @$(BuildLib)

# end of file

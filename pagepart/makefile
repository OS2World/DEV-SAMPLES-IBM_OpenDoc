#   @(#) 1.4 os2/src/samples/pagepart/makefile.mak, odpagepart, od96os2, odos29712d 1/24/97 12:58:49 [3/21/97 17:49:02]
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odpagepart
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
#Subdirs = en_US de_DE es_ES fr_FR ja_JP pt_BR zh_CN zh_TW


# ===================================================================
# Targets

# IdlTargets = List all the idl other samples will want to see
# HdrTargets = List all the C++ headers other samples will want to see
# LibTargets = List all export libraries to be built
# DllTargets = List all shared libraries to be built


IdlTargets = iodpage.idl \
             iodpgprn.idl

RcTargets =  iodpage.rc

HdrTargets = iodpage.hpp \
             iodpgres.h

LibTargets = $(ODSRC)/lib/iodpage.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodpage.dll

RegMain=iodpage.dll
RegIDL=iodpage.idl
RegClassName=PageLayout
RegKind=PageLayout
FilesDlls=iodpage.dll iodbasec.dll iodutils.dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=iodpage.$(LibSuffix)
#FilesCats=iodpage.cat
FilesCats=
FilesStationery=


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

iodpage.$(Obj) : iodpage.xih iodpage.hpp iodpgRes.h

iodpgPrn.$(Obj) : iodpgprn.xih

iodpageObjList = iodpage.$(Obj) \
                 iodpgprn.$(Obj)

iodpageLibList = \
!IF "$(Platform)"=="win32"
        {$(LIB)}COMDLG32.$(LibSuffix)  \
        {$(LIB)}COMCTL32.$(LibSuffix)  \
        {$(LIB)}msgdll.$(LibSuffix)   \
!ENDIF
        {$(LIB)}somtk.$(LibSuffix)  \
        {$(LIB)}iodutils.$(LibSuffix) \
        {$(LIB)}iodbasec.$(LibSuffix) \
        {$(LIB)}odbento.$(LibSuffix)  \
        {$(LIB)}odbindng.$(LibSuffix) \
        {$(LIB)}odcm.$(LibSuffix)     \
        {$(LIB)}odcore.$(LibSuffix)   \
        {$(LIB)}oddatax.$(LibSuffix)  \
        {$(LIB)}odimagng.$(LibSuffix) \
        {$(LIB)}odlayout.$(LibSuffix) \
        {$(LIB)}odmsgcat.$(LibSuffix) \
        {$(LIB)}odstorag.$(LibSuffix) \
        {$(LIB)}odui.$(LibSuffix)     \
        {$(LIB)}odregsty.$(LibSuffix)


$(ODSRC)/dll/iodpage.dll :  $(ODSRC)/lib/iodpage.$(Exp) \
        $(iodpageLibList) \
        $(iodpageObjList)
	@$(BuildDllWithRes) "RecFile=iodpage.res" BuildDllRule


$(ODSRC)/lib/iodpage.$(Def) :  iodpage.$(Def)
        @$(BuildCopy)


$(ODSRC)/lib/iodpage.$(LibSuffix) : \
!IFDEF CPPMAIN
	$(ODSRC)/lib/iodpage.$(Def) \
!ENDIF
        $(iodpageObjList)
        @$(BuildLib)


# end of file

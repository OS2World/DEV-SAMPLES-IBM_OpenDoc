# @(#) 1.7.1.3 os2/src/samples/linkcntr/makefile.mak, odlinkpart, od96os2, odos29712d 1/22/97 12:01:03 [ 3/21/97 17:44:55 ]
#
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odlinkcntr
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


IdlTargets = iodlinkc.idl

HdrTargets =

LibTargets = $(ODSRC)/lib/iodlinkc.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodlinkc.dll

RegMain=iodlinkc.dll
RegIDL=iodlinkc.idl
RegClassName=LinkContainer
RegKind=LinkContainer
FilesDlls=iodlinkc.dll iodutils.dll iodbasec.dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=iodlinkc.$(LibSuffix)
FilesCats=
FilesStationery=


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

linkcntrObjList = iodlinkc.$(Obj)

iodlinkc.$(Obj) : iodlinkc.xih iodlinkc.cpp

linkcntrLibList = \
!IF "$(Platform)"=="win32"
        {$(LIB)}COMDLG32.$(LibSuffix)  \
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



$(ODSRC)/dll/iodlinkc.dll :  $(ODSRC)/lib/iodlinkc.$(Exp) \
        $(linkcntrLibList) \
        $(linkcntrObjList)
        @$(BuildDll)


$(ODSRC)/lib/iodlinkc.$(Def) :  iodlinkc.$(Def)
        @$(BuildCopy)


$(ODSRC)/lib/iodlinkc.$(LibSuffix) : \
!IFDEF CPPMAIN
	$(ODSRC)/lib/iodlinkc.$(Def) \
!ENDIF
        $(linkcntrObjList)
        @$(BuildLib)


# end of file

#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odsamples
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
# @(#) 1.19 os2/src/samples/dynamicp/makefile.mak, oddynamicpart, od96os2, odos29712d 1/22/97 12:04:29 [3/21/97 17:44:56]

# If you wish to add to the existing compile and link flags, you can
# do it with these macros

ExtraSOMCompileOptions =

ExtraCompileOptions =

ExtraLinkOptions =


# ===================================================================
# Targets

# IdlTargets = List all the idls
# HdrTargets = List all the C++ headers
# LibTargets = List all export libraries to be built
# DllTargets = List all shared libraries to be built
#
# The Reg* and File*  macros are used to generate a table of contents
# and an install package


IdlTargets = ioddynam.idl ioddyext.idl

RcTargets =  ioddynam.rc

HdrTargets =

LibTargets = $(ODSRC)/lib/ioddynam.$(LibSuffix)

DllTargets = $(ODSRC)/dll/ioddynam.dll

RegMain=ioddynam.dll
RegIDL=ioddynam.idl ioddyext.idl
RegClassName=DynamicPart
RegKind=DynamicPart
FilesDlls=ioddynam.dll iodutils.dll iodsimpl.dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=ioddynam.$(LibSuffix)
FilesCats=
FilesTypeLibs=ioddynam.tlb
FilesStationery=

# Add script event handler registration information
CtypelibIDL=ioddynam.idl
CtypelibDir=$(ODSRC)/src/dynamicp
CtypelibCmdLineArgsFile=ioddynam.cin

# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

dynamicpObjList = ioddynam.$(Obj) ioddyext.$(Obj)

ioddynam.$(Obj) : ioddynam.xih ioddynam.cpp
!IF "$(Platform)"=="win32"
myfocus.$(Obj) : myfocus.cpp myfocus.h
!ENDIF

ioddyext.$(Obj) : ioddyext.xih ioddyext.cpp

dynamicpLibList = \
!IF "$(Platform)"=="win32"
        {$(LIB)}COMDLG32.$(LibSuffix)  \
        {$(LIB)}msgdll.$(LibSuffix) \
        myfocus.$(Obj) \
!ENDIF
        {$(LIB)}somtk.$(LibSuffix) \
        {$(LIB)}iodsimpl.$(LibSuffix) \
        {$(LIB)}iodutils.$(LibSuffix) \
        {$(LIB)}odcore.$(LibSuffix) \
        {$(LIB)}odimagng.$(LibSuffix) \
        {$(LIB)}odlayout.$(LibSuffix) \
        {$(LIB)}odui.$(LibSuffix) \
        {$(LIB)}odstorag.$(LibSuffix) \
        {$(LIB)}oddsevnt.$(LibSuffix) \
        {$(LIB)}oddatax.$(LibSuffix) \
        {$(LIB)}oddsscr.$(LibSuffix)

$(ODSRC)/dll/ioddynam.dll :  $(ODSRC)/lib/ioddynam.$(Exp) \
        $(dynamicpLibList) \
        $(dynamicpObjList)
        @$(BuildDllWithRes) "RecFile=ioddynam.res" BuildDllRule
!IF "$(Platform)"=="win32"
   $(COPY) ioddynam.bmp $(@D:/=\)
!ENDIF


$(ODSRC)/lib/ioddynam.$(Def) :  ioddynam.$(Def)
        @$(BuildCopy)


$(ODSRC)/lib/ioddynam.$(LibSuffix) : \
!IFDEF CPPMAIN
$(ODSRC)/lib/ioddynam.$(Def) \
!ENDIF
        $(dynamicpObjList)
        @$(BuildLib)

MakeCPP: $(IdlTargets)
        @setlocal
        @set SMNOTC=
        sc -sxc $(SOPTS) $**
        @endlocal

MakeDEF: $(IdlTargets)
        @setlocal
        @set SMNOTC=
        @set SMINCLUDE=
        sc -sdef $(SOPTS) $**
        @endlocal

# end of file

# @(#) 1.8.2.26 os2/src/samples/basecntr/makefile.mak, odbasepart, od96os2, odos29712d 3/13/97 21:16:02 [ 3/21/97 17:41:21 ]
#
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odbasecntr
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

ExtraSOMCompileOptions = -DEMIT_CONTOBJ

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
# LibTargets = List all export libraries to be built
# DllTargets = List all shared libraries to be built
#
# The Reg* and File*  macros are used to generate a table of contents
# and an install package

IdlTargets = iodbasec.idl\
iodbcitr.idl\
iodbcutl.idl\
iodbcobj.idl\
iodbcset.idl

RcTargets = iodbasec.rc

HdrTargets = bcmain.h 

LibTargets = $(ODSRC)/lib/iodbasec.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodbasec.dll

RegMain=iodbasec.dll
RegIDL=iodbasec.idl
RegClassName=BaseContainer
RegKind=IBM:BaseContainer:PartKind
FilesDlls=iodbasec.dll $(iodutils).dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets) iodbasec.h
FilesLibs=iodbasec.$(LibSuffix)
FilesCats=iodbasec.cat
FilesHelps=iodbasec.hlp
FilesStationery=


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

bcpartObjList = iodbasec.$(Obj) iodbcitr.$(Obj) iodbcutl.$(Obj) bcevent.$(Obj) iodbcobj.$(Obj) iodbcset.$(Obj)

iodbasec.$(Obj) : iodbasec.xih bcxfer.cpp iodbcvwt.cpp

iodbcitr.$(Obj) : iodbcitr.xih

iodbcutl.$(Obj) : iodbcutl.xih

bcevent.$(Obj) : iodbasec.xih

iodbcobj.$(Obj) : iodbcobj.xih

iodbcset.$(Obj) : iodbcset.xih

bcpartLibList = \
!IF "$(Platform)"=="win32"
        {$(LIB)}COMDLG32.$(LibSuffix) \
	{$(LIB)}msgdll.$(LibSuffix) \
        {$(LIB)}comdlg32.lib \
        {$(LIB)}comctl32.lib \
!ENDIF
	{$(LIB)}somtk.$(LibSuffix) \
	{$(LIB)}$(iodutils).$(LibSuffix) \
	{$(LIB)}odbento.$(LibSuffix)  \
	{$(LIB)}odbindng.$(LibSuffix) \
	{$(LIB)}odcm.$(LibSuffix)     \
	{$(LIB)}odcore.$(LibSuffix)   \
	{$(LIB)}oddatax.$(LibSuffix)  \
	{$(LIB)}odimagng.$(LibSuffix) \
	{$(LIB)}odlayout.$(LibSuffix) \
	{$(LIB)}odstorag.$(LibSuffix) \
	{$(LIB)}odui.$(LibSuffix)     \
	{$(LIB)}odregsty.$(LibSuffix) \
	{$(LIB)}odmsgcat.$(LibSuffix) 



$(ODSRC)/dll/iodbasec.dll :  $(ODSRC)/lib/iodbasec.$(Exp) \
	$(bcpartLibList) \
	$(bcpartObjList)
	@$(BuildDllWithRes) "RecFile=iodbasec.res" BuildDllRule


$(ODSRC)/lib/iodbasec.$(Def) :  iodbasec.$(Def)
	@$(BuildCopy)


$(ODSRC)/lib/iodbasec.$(LibSuffix) : \
!IFDEF CPPMAIN
	$(ODSRC)/lib/iodbasec.$(Def) \
!ENDIF
	$(bcpartObjList)
	@$(BuildLib)

# end of file

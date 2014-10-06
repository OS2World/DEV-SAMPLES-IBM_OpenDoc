# @(#) 1.39 os2/src/samples/grafpart/makefile.mak, odgrafpart, od96os2, odos29714c 3/24/97 18:25:34 [4/2/97 17:19:54]
#
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odgrafpart
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

# ************************************************************************
#  File:      makefile(.mak)
#  Contains:  Nmake program maintenance file for 2D-Drawing Container Sample Part
# ************************************************************************


# ===================================================================
# If you wish to add to the existing compile and link flags, you can
# do it with these macros (add only platform independant values).

ExtraSOMCompileOptions = -DGPDebug -DEMIT_GRAFPART

ExtraCompileOptions    = -DGPDebug

ExtraLinkOptions       =


# ===================================================================
# Subdirectories you want nmake to visit

Subdirs = en_US


# ===================================================================
# Targets

# IdlTargets = List all the idls
IdlTargets = \
    iodgraph.idl \
    iodgfigr.idl \
    iodgpoin.idl \
    iodgline.idl \
    iodgtext.idl \
    iodgrect.idl \
    iodbasec.idl

# HdrTargets = List all the C++ headers
HdrTargets = iodgraph.hpp

# MsgTargets = List all the message catalogs
MsgTargets =

# LibTargets = List all export libraries to be built
LibTargets = $(ODSRC)/lib/iodgraph.$(LibSuffix)

# DllTargets = List all shared libraries to be built
DllTargets = $(ODSRC)/dll/iodgraph.dll

# RcTargets = List all resource files to be built
RcTargets = iodgraph.rc

# The Reg* and File*  macros are used to generate a table of contents
# and an install package
RegMain=iodgraph.dll
RegIDL=iodgraph.idl 
RegClassName=GrafPart
RegKind=GraphicsPart
FilesDlls=iodgraph.dll iodbasec.dll iodutils.dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=iodgraph.$(LibSuffix)
FilesCats=iodgraph.cat
FilesStationery=

# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Lists

grafpartObjList = \
    iodgraph.$(Obj) \
    iodgfigr.$(Obj) \
    iodgpoin.$(Obj) \
    iodgline.$(Obj) \
    iodgtext.$(Obj) \
    iodgrect.$(Obj)

grafpartLibList = \
!IF "$(Platform)"=="win32"
    {$(LIB)}Msgdll.$(LibSuffix) \
!ENDIF
    {$(LIB)}somtk.$(LibSuffix) \
    {$(LIB)}odimagng.$(LibSuffix) \
    {$(LIB)}odui.$(LibSuffix) \
    {$(LIB)}odlayout.$(LibSuffix) \
    {$(LIB)}odcore.$(LibSuffix) \
    {$(LIB)}odstorag.$(LibSuffix) \
    {$(LIB)}odmsgcat.$(LibSuffix) \
    {$(LIB)}iodbasec.$(LibSuffix) \
    {$(LIB)}iodutils.$(LibSuffix)

# ===================================================================
# Rules

iodgraph.$(Obj) : \
   iodgraph.cpp \
   graph_cm.cpp \
   iodgraph.xih \
   iodgcomm.cpp \
   iodgraph.hpp

iodgfigr.$(Obj) : \
   iodgfigr.cpp \
   iodgfigr.xih \
   iodgcomm.cpp \
   iodgraph.hpp

iodgpoin.$(Obj) : \
   iodgpoin.cpp \
   iodgfigr.idl \
   iodgpoin.xih \
   iodgcomm.cpp \
   iodgraph.hpp

iodgline.$(Obj) : \
   iodgline.cpp \
   iodgfigr.idl \
   iodgline.xih \
   iodgcomm.cpp \
   iodgraph.hpp

iodgtext.$(Obj) : \
   iodgtext.cpp \
   iodgfigr.idl \
   iodgrect.idl \
   iodgtext.xih \
   iodgcomm.cpp \
   iodgraph.hpp

iodgrect.$(Obj) : \
   iodgrect.cpp \
   iodgline.idl \
   iodgrect.xih \
   iodgcomm.cpp \
   iodgraph.hpp


$(ODSRC)/dll/iodgraph.dll :  \
   $(ODSRC)/lib/iodgraph.$(Exp) \
   $(grafpartLibList) \
   $(grafpartObjList)
       @$(BuildDll)


$(ODSRC)/lib/iodgraph.$(Def) :  \
   iodgraph.$(Def)
       @$(BuildCopy)


$(ODSRC)/lib/iodgraph.$(LibSuffix) : \
   $(ODSRC)/lib/iodgraph.$(Def) \
   $(grafpartObjList)
       @$(BuildLib)


# ===================================================================
# end of file
# ===================================================================

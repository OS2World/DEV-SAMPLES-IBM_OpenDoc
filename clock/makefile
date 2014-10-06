# @(#) 1.17 os2/src/samples/clock/makefile.mak, odclockpart, od96os2, odos29712d 1/22/97 12:04:26 [ 3/21/97 17:41:43 ]
#
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odclockpart
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

ExtraCompileOption =

ExtraLinkOptions =


# ===================================================================
# Targets

# IdlTargets = List all the idl other samples will want to see
# HdrTargets = List all the C++ headers other samples will want to see
# LibTargets = List all export libraries to be built
# DllTargets = List all shared libraries to be built
#
# The Reg* and File*  macros are used to generate a table of contents
# and an install package


IdlTargets = iodclock.idl

HdrTargets =

LibTargets = $(ODSRC)/lib/iodclock.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodclock.dll

RegMain=iodclock.dll
RegIDL=iodclock.idl
RegClassName=Clock
RegKind=Clock
FilesDlls=iodclock.dll iodutils.dll iodshape.dll iodsimpl.dll
FilesIncs=$(IdlTargets) $(IdlTargets:.idl=.xh) $(HdrTargets)
FilesLibs=iodclock.$(LibSuffix)
FilesCats=
FilesStationery=


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

ClockObjList = iodclock.$(Obj)


iodclock.$(Obj) : iodclock.xih iodclock.cpp

ClockLibList = \
        {$(LIB)}iodutils.$(LibSuffix) \
        {$(LIB)}iodshape.$(LibSuffix) \
        {$(LIB)}iodsimpl.$(LibSuffix) \
        {$(LIB)}odimagng.$(LibSuffix) \
        {$(LIB)}odui.$(LibSuffix) \
        {$(LIB)}odlayout.$(LibSuffix) \
        {$(LIB)}odcore.$(LibSuffix) \
        {$(LIB)}odstorag.$(LibSuffix) \
        {$(LIB)}somtk.$(LibSuffix) \
!IF "$(Platform)"=="win32"
        {$(LIB)}msgdll.$(LibSuffix)
!ENDIF



$(ODSRC)/dll/iodclock.dll :  $(ODSRC)/lib/iodclock.$(Exp) \
        $(ClockLibList) \
        $(ClockObjList)
        @$(BuildDll)


$(ODSRC)/lib/iodclock.$(Def) :  iodclock.$(Def)
        @$(BuildCopy)


$(ODSRC)/lib/iodclock.$(LibSuffix) : $(ODSRC)/lib/iodclock.$(Def) \
        $(ClockObjList)
        @$(BuildLib)

# end of file

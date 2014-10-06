# @(#) 1.2 os2/src/samples/shpin/makefile.mak, odplugin, od96os2, odos29712d 2/27/97 16:12:40 [ 3/21/97 17:51:32 ]
#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odplugin
#
#   CLASSES: none
#
#   ORIGINS: 27
#
#
#   (C) COPYRIGHT International Business Machines Corp. 1997
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


IdlTargets = ioddspm.idl

HdrTargets = 

MsgTargets =

RcTargets =

LibTargets = $(ODSRC)/lib/iodshpin.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodshpin.dll


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.
 
!include $(ODSRC)/src/Platform.mak
 
 
# ===================================================================
# Rules

shpinObjList = \
	ioddspm.$(Obj) \
	iodshpin.$(Obj)

ioddspm.$(Obj) : ioddspm.xih ioddspm.h

shpinLibList = \
	$(SOMBASE)/lib/somtk.$(LibSuffix) \
	$(ODBASE)/lib/odcore.$(LibSuffix) \
	$(ODBASE)/lib/odbento.$(LibSuffix) \
	$(ODBASE)/lib/odstorag.$(LibSuffix) \
	$(ODBASE)/lib/odui.$(LibSuffix) \
	$(ODBASE)/lib/odlayout.$(LibSuffix) \
	$(ODSRC)/lib/$(iodutils).$(LibSuffix)

$(ODSRC)/dll/iodshpin.dll :  $(ODSRC)/lib/iodshpin.$(Exp) \
	$(shpinObjList) \
	$(shpinLibList)
	@$(BuildDll)

$(ODSRC)/lib/iodshpin.$(Def) :  $(shpinObjList)
	@$(BuildDef)

$(ODSRC)/lib/iodshpin.$(LibSuffix) : \
!IFDEF CPPMAIN
	$(ODSRC)/lib/iodshpin.$(Def) \
!ENDIF
	$(shpinObjList)
	@$(BuildLib)

# end of file

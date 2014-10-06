# @(#) 1.4 os2/src/samples/runtime/makefile.mak, odruntimepart, od96os2, odos29712d 3/3/97 12:19:14 [ 3/21/97 17:47:48 ]
#
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

# This is an example of creating your own runtime library with
# the VisualAge compiler.  Creating and using your own runtime library
# means your part doesn't require the VisualAge compiler to be installed
# on any machine using your part.
#
# The alternatives, along with the writeup describing this process,
# is in the section titled "Creating Your Own Runtime Library Dlls" in
# the VisualAge C++ Programming Guide.


# If you wish to add to the existing compile and link flags, you can
# do it with these macros

ExtraSOMCompileOptions =

ExtraCompileOptions =

ExtraLinkOptions =


# ===================================================================
# Subdirectories you want nmake to visit
Subdirs = 

 
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


IdlTargets = 

HdrTargets =

MsgTargets =

!IFDEF CPPMAIN
LibTargets = $(ODSRC)/lib/iodrt.$(LibSuffix)

DllTargets = $(ODSRC)/dll/iodrt.dll
!ENDIF


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.
 
!include $(ODSRC)/src/Platform.mak
 
 
# ===================================================================
# Rules


!IF "$(Platform)"=="win32"
rtLibList =  $(CPPMAIN)\lib\cppwm35.lib \
             $(CPPMAIN)\sdk\lib\kernel32.lib
rtLinkFlags = /NOD /NOLogo
!ENDIF

!IF "$(Platform)"=="os2"
rtLibList =  $(CPPMAIN)\lib\cppom30.lib \
             $(CPPMAIN)\lib\os2386.lib \
             $(CPPMAIN)\lib\somtk.lib
rtLinkFlags = /NOD /NOLogo /EXEPACK:2
!ENDIF



$(ODSRC)/dll/iodrt.dll : iodrt.c \
	$(ODSRC)/lib/iodrt.$(Exp) \
	$(rtLibList)
	$(COMPILE) -B"$(rtLinkFlags)" -Fe$@ -Q+ -Ge- -Gm+ $**


# On Windows, iodrt.def is based off $(CPPMAIN)\lib\cppwm35.def for the
#             VisualAge compiler, version 3.5.  If you have a later version
#             of the compiler, you may need to replace iodrt.def.
# On OS/2,    iodrt.def is based off $(CPPMAIN)\lib\cppom30.def for the
#             VisualAge compiler, version 3.0.  If you have a later version
#             of the compiler, you may need to replace iodrt.def.
$(ODSRC)/lib/iodrt.$(Def) :  iodrt.$(Def)
	@$(BuildCopy)


$(ODSRC)/lib/iodrt.$(LibSuffix) : \
	$(ODSRC)/lib/iodrt.$(Def)
!IF "$(Platform)"=="win32"
	ilib /nologo /nobackup /GENI:$@ /DEF:$**
!ENDIF
!IF "$(Platform)"=="os2"
	implib /nologo /NOI $(@:/=\) $**
	ilib /q /convformat /NOBROWSE /noext /nobackup \
		$(@:/=\) + $(CPPMAIN)\lib\CPPOM30O.lib;
!ENDIF



# end of file

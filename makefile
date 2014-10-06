# @(#) 1.7.1.9 os2/src/samples/makefile.mak, odsamples, od96os2, odos29714c 3/25/97 12:07:57 [ 4/2/97 17:20:01 ]
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

# If you wish to add to the existing compile and link flags, you can
# do it with these macros

ExtraSOMCompileOptions =

ExtraCompileOptions =

ExtraLinkOptions =


# ===================================================================
# Subdirectories you want nmake to visit.  Order should NOT matter,
# but to guard against individual makefile problems, we'll visit
# utils first, the subclassable parts (simple, basecntr) second.
Subdirs = utils \
	basecntr \
	simple \
	shape \
	clock \
	text \
	pagepart \
	grafpart \
	linkcntr \
	dynamicp 

# Additional Sample Parts - only source will be shipped.
# 	runtime 

# ===================================================================
# Targets

# DllTargets = List all shared libraries and binarys to be built
!IFNDEF OS2_SHELL
DllTargets = $(ODSRC)/bin/NMakCpkg.exe
!ENDIF


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

$(ODSRC)/bin/NMakCpkg.exe : NMakCpkg.exe
	@$(BuildCopy)

NMakCpkg.exe : NMakCpkg.cpp
	@echo .
	set PATH=$(NmakePATH)%%PATH%%
	set LIB=$(NmakeLIB)%%LIB%%
	$(COMPILE) $(CompileIncludes) $**


# end of file

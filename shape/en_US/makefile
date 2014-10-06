#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odshapepart
#
#   CLASSES: none
#
#   ORIGINS: 82,27
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
# @(#) 1.4 os2/src/samples/shape/en_US/makefile.mak, odshapepart, od96os2, odos29712d 2/12/97 16:13:07 [ 3/21/97 17:48:23 ]
#

# If you wish to add to the existing compile and link flags, you can
# do it with these macros

ExtraSOMCompileOptions =

ExtraCompileOptions =

ExtraLinkOptions =


# ===================================================================
# Subdirectories you want nmake to visit
#Subdirs =


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

RcTargets =

HdrTargets = iodshpe.h

MsgTargets = $(ODSRC)/locale/en_US/iodshpe.cat \
             $(ODSRC)/locale/en_US/iodshape.hlp

LibTargets =

DllTargets =

# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.

!include $(ODSRC)/src/Platform.mak


# ===================================================================
# Rules

$(ODSRC)/locale/en_US/iodshpe.cat : iodshpe.cat
	@$(BuildCopy)

$(ODSRC)/locale/en_US/iodshape.hlp : iodshape.hlp
	@$(BuildCopy)

# end of file

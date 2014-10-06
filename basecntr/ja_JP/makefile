# @(#) 1.2.1.4 os2/src/samples/basecntr/ja_JP/makefile.mak, odbasepart, od96os2, odos29712d 2/13/97 14:13:09 [ 3/21/97 17:41:49 ]
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

ExtraSOMCompileOptions = 

ExtraCompileOptions = 

ExtraLinkOptions =


# ===================================================================
# Subdirectories you want nmake to visit
Subdirs =

 
# ===================================================================
# Targets

# IdlTargets = List all the idls
# RegTargets = List all idls of parts that need to be registered
# HdrTargets = List all the C++ headers
# MsgTargets = List all the message catalogs
# LibTargets = List all export libraries to be built
# DllTargets = List all shared libraries to be built


IdlTargets =

RegTargets =

HdrTargets = 

MsgTargets = $(ODSRC)/locale/ja_JP/iodbasec.cat \
	     $(ODSRC)/locale/ja_JP/iodbasec.hlp

LibTargets =

DllTargets =


# ===================================================================
# Common Inference Rules

# Platform.mak contains all the platform specific code to build the
# sample. Check it to verify which compiler the sample is using.
 
!include $(ODSRC)/src/Platform.mak
 
 
# ===================================================================
# Rules

$(ODSRC)/locale/ja_JP/iodbasec.cat : iodbasec.cat
	@$(BuildCopy)

$(ODSRC)/locale/ja_JP/iodbasec.hlp : iodbasec.hlp
	@$(BuildCopy)


# end of file

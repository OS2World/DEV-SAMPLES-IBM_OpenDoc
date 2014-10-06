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
# @(#) 1.48 os2/src/samples/Platform.mak, odsamples, od96os2, odos29712d 3/10/97 14:11:10 [ 3/21/97 17:39:48 ]
#
#--------------------------------------------------------------------------
# characters that can precede a make line:
#    @  suppresses display of the command
#    -  turns off error checking for the command
#    !  executes the command for each dependent file
#
# make macros:
#    $@   the target file	(d:/src/main.cpp)
#    $*   base name             (d:/src/main)
#    $**  dependent files (sources)
#    $?   sources newer than target
#    $<   single source newer than target
#    $$@  current NMAKE target
#    
# macro modifiers - you can modify all of the make macros above this way
#    $(@D) - directory only 	(d:/src)
#    $(@F) - file only          (main.cpp)
#    $(@B) - base filename only (main)
#    $(@R) - path, no extension (d:/src/main)
#    $(SOMETHING:a=b) - substitutes changes a's in $(SOMETHING) to b's
#
# shell programming:
#    echo.    - echoes a blank line
#    setlocal - allows you to change env variables during execution of a
#               batch file 
#    endlocal - restores the env variables to their original values
#    for %%variable (or %variable) in (some set) do command:
#	Each %%variable (or %variable) is replaced with each string in (some 
#       set) until the command processes all files.  %% is used within a 
#       batch pgm.
#
#    
#--------------------------------------------------------------------------
#
# Note: This is the platform specific header for the OpenDoc nmake files
#       on OS/2 using the VisualAge compiler


# Important Note: The compile and link flags in this nmake file are the
#                 basic core set of flags.  If you want to build optimized
#                 code or debug code you will need to set the compiler
#                 specific environment variables.  Here are our suggestions:
#
#                  Optimized build
#                   set ICC = -O+ -Om-
#                   set ILINK = -NOBROWSE
#
#                  Debug build
#                   set ICC = -Ti+ -DDEBUG
#                   set ILINK = -DEBUG


# Important Note: The nmake logic has the additional capability
#                 of letting you optionally link in your own runtime library.
#                 The default is to dynamically link in the compiler's runtime.
#                 To link in your own runtime, call nmake with the
#                 LocalRuntimeLibrary macro set to your runtime library.
#                 This macro triggers the logic that adjusts the compile and
#                 link flags to use your runtime library.
#		    %ODSRC%\src\runtime gives an example of building a local
#		  runtime library based off the description in "Creating
#		  Your Own Runtime Library DLLs" in the VisualAge C++
#		  Programming Guide. After creating iodrt.dll in
#		  %ODSRC%\src\runtime, you could build the IBM Samples, having
#		  them linked to the local runtime, by issuing the following
#		  nmake command:
#		     nmake "LocalRuntimeLibrary=%ODSRC%\lib\iodrt.lib %ODSRC%\lib\os2\os2386.lib %CPPMAIN%\lib\CPPOOC3.lib"
#


#..............................................................................
#			Macros used to re-set environment variables
#..............................................................................

# There is a known problem with nmake, where it has problems parsing
# the SET statment when you are setting an environment variable to null.
# So we currently can not set an environment variable equal to null in an
# nmake file.

# Whenever the som compiler is used, This becomes the new setting of
# SMINCLUDE.
NmakeSMINCLUDE=.


# Whenever ilink is used to build a dll, These become the new settings of
# PATH, LIB, and BeginLIBPATH.
NmakePATH = $(CPPMAIN)\BIN;$(CPPMAIN)\SMARTS\SCRIPTS;$(PATH)

NmakeLIBPATH=$(ODSRCPATHS:;=\dll;)$(ODPARTPATHS:;=\dll;)$(ODBASEPATHS:;=\dll;)$(SOMBASE)\LIB;$(CPPMAIN)\DLL;$(CPPMAIN)\SAMPLES\TOOLKIT\DLL;

NmakeLIB=$(ODSRCPATHS:;=\lib;)$(ODPARTPATHS:;=\lib;)$(ODBASEPATHS:;=\lib;)$(ODSRC)\LIB\OS2;$(ODCFG)\LIB\OS2;$(SOMBASE)\LIB;$(CPPMAIN)\LIB;$(CPPMAIN)\DLL;$(CPPMAIN)\sdk\lib;


# Whenever we call the resource compiler, This becomes the new setting of
# INCLUDE.
NmakeINCLUDE=.

# Whenever a package is built, this is used as the locale
!IF "$(LOCALE)"=="" || "$(LOCALE)"=="C"
NmakeLOCALE=en_US
!ELSE
NmakeLOCALE=$(LOCALE)
!ENDIF


#..............................................................................
# set the LIB path for building the OpenDoc samples
#..............................................................................
LIB=$(NmakeLIB)
BeginLIBPATH=$(NmakeLIBPATH)

#..............................................................................
#			General use Macros
#..............................................................................

IncludeDir     = $(ODSRC)\INCLUDE

# These are the list of Locales we know are valid
LocaleList = de_DE es_ES en_US fr_FR ja_JP pt_BR zh_CN zh_TW


SOMDefines     = -D_PLATFORM_OS2_

SOMArgs        = -p -c -mchkexcept

# Includes are set with -I flags to allow for multiple, different, compilers
# to be installed on your machine.
SOMIncludes    = -I. -I$(ODSRCPATHS:;=\include -I)$(ODPARTPATHS:;=\include -I)$(ODBASEPATHS:;=\include -I)$(SOMBASE)\INCLUDE

SOMOptions     = $(SOMArgs) $(SOMDefines) $(SOMIncludes)

SOPTS = $(SOMOptions) $(ExtraSOMCompileOptions)


CompileDefines = -D_PLATFORM_OS2_ -DODDebug=0 -D_NATIVE_EXCEPTIONS_

# If nmake was called with a LocalRuntimeLibrary macro set to a local runtime
# library, don't link dynamically to the compiler runtime
! IF "$(LocalRuntimeLibrary)" != ""
CompileArgs    = -C+ -Gd+ -Gm+ -Gs- -Q+ -Ss+ -Su4 -Ge- -Gn+ $(ICC)
! ELSE
CompileArgs    = -C+ -Gd+ -Gm+ -Gs- -Q+ -Ss+ -Su4 -Ge- $(ICC)
! ENDIF

# Includes are set with -I flags to allow for multiple, different, compilers
# to be installed on your machine.
CompileIncludes=.;$(ODSRCPATHS:;=\include;)$(ODPARTPATHS:;=\include;)$(ODBASEPATHS:;=\include;)$(SOMBASE)\INCLUDE;$(IncludeDir)\OS2;$(CPPMAIN)\include;$(CPPMAIN)\include\os2;$(CPPMAIN)\inc

CompileOptions = $(CompileArgs) $(CompileDefines) 

COPTS = $(CompileOptions) $(ExtraCompileOptions)

COMPILE = icc

ResourceCompiler = $(CPPMAIN)\bin\rc.exe


# If nmake was called with a LocalRuntimeLibrary macro set to a local runtime
# library, disregard the default libraries
! IF "$(LocalRuntimeLibrary)" != ""
LinkOptions = /NOE /st:100000 /NOLogo /Se:512 /NOD $(ILINK)
! ELSE
LinkOptions = /NOE /st:100000 /NOLogo /Se:512 $(ILINK)
! ENDIF

LOPTS = $(LinkOptions) $(ExtraLinkOptions)

REMOVE = erase /f

COPY = copy

# We use the Info-ZIP 32-bit compression code when we create packages.
# It's freely available from CompuServe in the IBMPRO forum and by
# anonymous ftp from the Internet site ftp.uu.net:/pub/archiving/zip/OS2.
# If you decide to use it, this build logic will work after you
# set the NmakeZIP2EXE environment variable to the full path location
# of unzipsfx.exe.
#   If you decide to use any other 32-bit compression code, you will have
# adjust the ZIP and ZIP2EXE macros, and the logic that uses them, accordingly.
#
ZIP = zip -j
ZIP2EXE = copy /b $(NMAKEZIP2EXE)+$(RegMain:.dll=.zip) $(RegMain:.dll=.exe)


Platform = os2

MAKE = nmake

# These suffixes are to help promote portable nmake files between platforms.
# When the suffixes change on different platforms, these suffixes are the
# only things that need to change.  All the sample nmake files that use these
# suffix macros, so they are portable between different platforms.
Exp = def
Def = def
Obj = obj
LibSuffix = lib
Locale = locale


#..............................................................................
#			Default Targets
#..............................................................................
DefaultTarget : Idls Hdrs Libs Dlls


# Rule to copy the idls to samples
Idls : CheckEnvironmentVariables Idl
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f Idls $(MAKEFLAGS)
!   ENDIF

Idl  : $(IdlTargets)
!   IF "$(IdlTargets)"!=""
    !$(COPY) $** $(IncludeDir)
!   ENDIF


# Rules to process the headers
Hdrs : CheckEnvironmentVariables Hdr
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f Hdrs $(MAKEFLAGS)
!   ENDIF

Hdr  :: $(MsgTargets)

Hdr  :: $(HdrTargets)
!       IF "$(HdrTargets)"!=""
           @FOR %%f IN ($(HdrTargets)) DO $(COPY) %%f $(IncludeDir)
!       ENDIF

Hdr  :: $(RcTargets)
!       IF "$(RcTargets)"!=""
#
#	    If the version of the resourse compiler that comes with the
#	    VisualAge compiler exist, then use it.  Otherwise, use whatever
#	    resourse compiler exists in the path
#
	    @setlocal
	    set INCLUDE=$(CompileIncludes)
	    @set PATH=$(CPPMAIN)\bin;$(PATH)
	    @IF EXIST $(ResourceCompiler) \
	      FOR %%f IN ($(RcTargets)) DO \
		 $(ResourceCompiler) -r $(CompileDefines) %%f
	    @IF NOT EXIST $(ResourceCompiler) \
	      FOR %%f IN ($(RcTargets)) DO \
		 rc -r $(CompileDefines) $(CompileIncludes) %%f
	    @endlocal
!       ENDIF

Hdr  :: CheckForSMNOTC $(IdlTargets:.idl=.xh)


# Rule to make the libraries
Libs : CheckEnvironmentVariables Lib
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f Libs $(MAKEFLAGS)
!   ENDIF

Lib  : $(LibTargets)


# Rule to make the dlls
Dlls : CheckEnvironmentVariables Dll
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f Dlls $(MAKEFLAGS)
!   ENDIF

Dll  :: $(DllTargets)

Dll  :: $(ODCFG)\od.ir


#..............................................................................
#			Default build rules and macros
#..............................................................................
.SUFFIXES: .cpp .CPP .c .C .idl .IDL .msg .MSG .ipf .IPF

.cpp.obj:
	@echo.
	@setlocal
	set INCLUDE=$(CompileIncludes)
	$(COMPILE) $(COPTS) -Ge- -Fo $@ $< || (( $(REMOVE) $@) && (exit 1))
	@endlocal

.c.obj:
	@echo.
	@setlocal
	set INCLUDE=$(CompileIncludes)
	$(COMPILE) $(COPTS) -Ge- -Fo $@ $< || (( $(REMOVE) $@) && (exit 1))
	@endlocal

.idl.xh:
	@echo.
        @setlocal
	set SMINCLUDE=$(NmakeSMINCLUDE)
	$(SOMBASE)\bin\sc -sxh -d$(IncludeDir) $(SOPTS) $**
!	IF "$(SMINCLUDE)"!=""
        @set SMINCLUDE=$(SMINCLUDE)
!	ENDIF
        @endlocal

.idl.xih:
	@echo.
        @setlocal
        set SMINCLUDE=$(NmakeSMINCLUDE)
	$(SOMBASE)\bin\sc -sxih $(SOPTS) $**
!	IF "$(SMINCLUDE)"!=""
        @set SMINCLUDE=$(SMINCLUDE)
!	ENDIF
        @endlocal

.msg.cat:
	@echo.
        runcat $(**R)

.ipf.hlp:
	@echo.
	ipfc $** $@


# Rule to re-register the idl when it has been modified
#
$(ODCFG)\od.ir : $(RegIDL)
!       IF "$(RegIDL)"!=""
!             IF "$(RegClassName)"!=""
	         @echo.
        	 @setlocal
		 set BeginLIBPATH=$(NmakeLIBPATH)
                 reg1part $(RegClassName) $(RegIDL:.idl=)
       		 @endlocal
!	      ELSE
	         @echo.
	         @echo ERROR: A ClassName has to be identified for the RegIDL.
	         @echo 	Set the RegClassName macro.
	         @echo.
!             ENDIF
!       ENDIF


# Rules to check the environment variables
#
CheckEnvironmentVariables: CheckForCPPMAIN CheckForODSRC CheckForSMNOTC

CheckForCPPMAIN:
!	IFNDEF CPPMAIN
		@echo .........................................
		@echo The OpenDoc nmake files are written to be used with
		@echo the IBM VisualAge compiler.  Since the environment
		@echo variable CPPMAIN is not defined, it appears the
		@echo compiler has not been installed.
		@echo Building the samples can not continue.
		@echo .........................................
		exit 1
!	ENDIF

CheckForODSRC:
!	IFNDEF ODSRC
		@echo .........................................
		@echo ODSRC, one of the OpenDoc environment variables, is
		@echo not defined, it appears OpenDoc has not been 
		@echo correctly installed.
		@echo Building the samples can not continue.
		@echo .........................................
		exit 1
!	ENDIF

CheckForSMNOTC:
!	IFDEF SMNOTC
		@echo .........................................
		@echo SMNOTC, the environment variable that tells
		@echo the SOM compiler not to generate TypeCode information,
		@echo is currently set on your machine.  
		@echo The OpenDoc samples can not build with this
		@echo environment variable set.  
		@echo Please remove this environment variable.
		@echo Building the samples can not continue.
		@echo .........................................
		exit 1
!	ENDIF

CheckForLOCALE:
!	IF "$(LOCALE)"=="" || "$(LOCALE)"=="C"
		@echo .........................................
!		IF "$(LOCALE)"==""
		   @echo  The LOCALE environment variable is currently not set.
!		ELSE
		   @echo  The LOCALE environment variable is currently set to "C".
!		ENDIF
		@echo  Because of this, the locale of the package will default to
		@echo  en_US.  If you wish to use a differnet locale, you must set
		@echo  the LOCALE environment variable to that locale.
		@echo .........................................
        	@echo.
!	ENDIF

CheckForNmakeZIP2EXE:
!	IFNDEF NMAKEZIP2EXE
		@echo .........................................
		@echo NmakeZIP2EXE, the environment variable for
		@echo specifying the 32-bit compression code used
		@echo to make packages, is not defined.  This
		@echo environment variable is necessary to build packages.
		@echo   You will need to install some version of
		@echo 32-bit compression code.  We recommend the
		@echo Info-ZIP 32-bit compression code.  It's freely
		@echo available from CompuServe in the IBMPRO forum
		@echo and by anonymous ftp from the Internet site
		@echo ftp.uu.net:/pub/archiving/zip/OS2.
		@echo   After it is installed, set the NmakeZIP2EXE
		@echo to the full path name of unzipsfx.exe.
		@echo   If you use any other 32-bit compression code,
		@echo you will have to edit Platform.mak accordingly.
		@echo   Building the packages can not continue.
		@echo .........................................
		exit 1
!	ENDIF



# ForceRegistrys and ForceRegistry are rules to force the registration
# of a part.  This rule is *not* part of the default target, so it doesn't
# happen automatically.  You have to run this as a separate build step.
#
ForceRegistrys : CheckEnvironmentVariables ForceRegistry
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f ForceRegistrys $(MAKEFLAGS)
!   ENDIF

ForceRegistry : $(RegIDL)
!       IF "$(RegIDL)"!=""
!             IF "$(RegClassName)"!=""
	         @echo.
        	 @setlocal
		 set BeginLIBPATH=$(NmakeLIBPATH)
                 reg1part $(RegClassName) $(RegIDL:.idl=)
       		 @endlocal
!	      ELSE
	         @echo.
	         @echo ERROR: A ClassName has to be identified for the RegIDL.
	         @echo 	Set the RegClassName macro.
	         @echo.
!             ENDIF
!       ENDIF


# Pkgs, Pkg, $(ODSRC)\pkg\$(NmakeLOCALE)\$(RegMain:.dll=.odz), and
# $(RegMain:.dll=.odt) are rules to make a part to be installed.
# These rules are *not* part of the default target, so it doesn't happen
# automatically.  You have to run this as a separate build step.
#
Pkgs : CheckEnvironmentVariables Pkg
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f Pkgs $(MAKEFLAGS)
!   ENDIF


!IF "$(RegMain)"!=""

Pkg  : CheckForNmakeZIP2EXE CheckForLOCALE $(ODSRC)\pkg\$(NmakeLOCALE)\$(RegMain:.dll=.odz)
#
#     The package for the native local was built as the source to this
#     target.  Now try to build the packages for the other locales.
#
	@--FOR %%g IN ($(LocaleList)) DO \
	    @IF NOT "%%g" == "$(NmakeLOCALE)" \
		@$(MAKE) /nologo "NmakeLOCALE = %%g" BuildPkgForSingleLocale


BuildPkgForSingleLocale :
	@echo.
!       IF "$(FilesCats)"!="" || "$(FilesHelps)"!=""
            @FOR %%f IN ($(FilesCats) $(FilesHelps)) DO \
                @IF NOT EXIST $(ODSRC)\locale\$(NmakeLOCALE)\%%f \
                        ( (echo ERROR:  $(ODSRC)\locale\$(NmakeLOCALE)\%%f does not exist.) && \
			(echo Package can not be built.) && (echo.) && \
			 exit ) 
!       ENDIF
	@$(MAKE) /nologo "NmakeLOCALE = $(NmakeLOCALE)" $(ODSRC)\pkg\$(NmakeLOCALE)\$(RegMain:.dll=.odz)


FilesDefs = $(FilesLibs:.lib=.def)

$(ODSRC)\pkg\$(NmakeLOCALE)\$(RegMain:.dll=.odz) : CleanPkgParts {$(ODSRC)\dll}$(RegMain) $(RegMain:.dll=.odt)
        @echo.
!       IF "$(FilesDlls)"!=""
            @FOR %%f IN ($(FilesDlls)) DO \
                @IF NOT EXIST $(ODSRC)\dll\%%f \
                        ( (echo ERROR:  $(ODSRC)\dll\%%f does not exist.) && \
			(echo Package can not be built.) && (echo.) && \
			 exit 1)
!       ENDIF
!       IF "$(FilesIncs)"!=""
            @FOR %%f IN ($(FilesIncs)) DO \
                @IF NOT EXIST $(ODSRC)\include\%%f \
                        ( (echo ERROR:  $(ODSRC)\include\%%f does not exist.) && \
			(echo Package can not be built.) && (echo.) && \
			 exit 1)
!       ENDIF
!       IF "$(FilesLibs)"!=""
            @FOR %%f IN ($(FilesLibs) $(FilesDefs)) DO \
                @IF NOT EXIST $(ODSRC)\lib\%%f \
                        ( (echo ERROR:  $(ODSRC)\lib\%%f does not exist.) && \
			(echo Package can not be built.) && (echo.) && \
			 exit 1)
!       ENDIF
!       IF "$(FilesCats)"!="" || "$(FilesHelps)"!=""
            @FOR %%f IN ($(FilesCats) $(FilesHelps)) DO \
                @IF NOT EXIST $(ODSRC)\locale\$(NmakeLOCALE)\%%f \
                        ( (echo ERROR:  $(ODSRC)\locale\$(NmakeLOCALE)\%%f does not exist.) && \
			(echo Package can not be built.) && (echo.) && \
			 exit 1)
!       ENDIF
!       IF "$(FilesStationery)"!=""
            @FOR %%f IN ($(FilesStationery)) DO \
                @IF NOT EXIST $(ODSRC)\work\%%f \
                        ( (echo ERROR:  $(ODSRC)\work\%%f does not exist.) && \
			(echo Package can not be built.) && (echo.) && \
			 exit 1)
!       ENDIF
        @echo Building: $@
	echo $(RegMain:.dll=.odt) > parts.lst
        $(ZIP) $(RegMain:.dll=.zip) parts.lst $(RegMain:.dll=.odt)
!       IF "$(FilesDlls)"!=""
            @FOR %%f IN ($(FilesDlls)) DO \
                $(ZIP) $(RegMain:.dll=.zip) $(ODSRC)\dll\%%f
!       ENDIF
!       IF "$(FilesIncs)"!=""
            @FOR %%f IN ($(FilesIncs)) DO \
                $(ZIP) $(RegMain:.dll=.zip) $(ODSRC)\include\%%f
!       ENDIF
!       IF "$(FilesLibs)"!=""
            @FOR %%f IN ($(FilesLibs) $(FilesDefs)) DO \
                $(ZIP) $(RegMain:.dll=.zip) $(ODSRC)\lib\%%f
!       ENDIF
!       IF "$(FilesCats)"!="" || "$(FilesHelps)"!=""
            @FOR %%f IN ($(FilesCats) $(FilesHelps)) DO \
                $(ZIP) $(RegMain:.dll=.zip) $(ODSRC)\locale\$(NmakeLOCALE)\%%f
!       ENDIF
!       IF "$(FilesStationery)"!=""
            @FOR %%f IN ($(FilesStationery)) DO \
                $(ZIP) $(RegMain:.dll=.zip) $(ODSRC)\work\%%f
!       ENDIF
        $(ZIP2EXE)
        $(REMOVE) $(RegMain:.dll=.zip)
	IF EXIST $(ODSRC)\pkg\$(NmakeLOCALE)\$(RegMain:.dll=.odz) $(REMOVE) $(ODSRC)\pkg\$(NmakeLOCALE)\$(RegMain:.dll=.odz)
        $(COPY) $(RegMain:.dll=.exe) $(ODSRC)\pkg\$(NmakeLOCALE)\$(RegMain:.dll=.odz)
        $(REMOVE) $(RegMain:.dll=.exe)


$(RegMain:.dll=.odt) :
        @echo.
        @echo Building: $@
        echo IODPartPlatform=$(Platform) > $@
        echo IODPartLocale=$(NmakeLOCALE) >> $@
        echo IODPartFilesDlls=$(FilesDlls: =,) >> $@
        echo IODPartFilesIncs=$(FilesIncs: =,) >> $@

!	IF "$(FilesLibs)"!=""
		echo IODPartFilesLibs=$(FilesLibs: =,),$(FilesDefs: =,) >> $@
!	ELSE
		echo IODPartFilesLibs= >> $@
!	ENDIF

        echo IODPartFilesCats=$(FilesCats: =,) >> $@
        echo IODPartFilesHelps=$(FilesHelps: =,) >> $@
        echo IODPartFilesStationery=$(FilesStationery: =,) >> $@
        echo IODPartRegMain=$(RegMain) >> $@
        echo IODPartRegIDL=$(RegIDL: =,) >> $@
        echo IODPartRegClassName=$(RegClassName) >> $@
        echo IODPartRegKind=$(RegKind) >> $@

!ELSE
Pkg  :
        @echo No package to build.
!ENDIF



#.............................................................................
#                       Macros with associated rules
#.............................................................................


#
# The BuildCopyRule requires 2 macros be set:
#       Target = $@
#       Sources = $**
#
BuildCopyRule :
        $(COPY) $(Sources) $(Target:/=\)

# The following macro simplifies the recursive call to the BuildCopyRule
BuildCopy = $(MAKE) /nologo /$(MAKEFLAGS) "Sources = $**" "Target = $@" BuildCopyRule


#
# The BuildDefRule requires 3 macros be set:
#       Target = $@
#       BaseNamePartOfTarget = $(@B)
#       Sources = $**
#
BuildDefRule :
        @echo.
        @echo Building: $(Target)
        @echo LIBRARY $(BaseNamePartOfTarget) INITINSTANCE TERMINSTANCE > $(Target)
        @echo DESCRIPTION '$(BaseNamePartOfTarget).dll' >> $(Target)
        @echo DATA MULTIPLE NONSHARED LOADONCALL >> $(Target)
        @echo EXPORTS >> $(Target)
        @FOR %%f IN ($(Sources)) DO cppfilt /B /P /Q /S %%f >> $(Target)
	@echo Leaving BuildDefRule

# The following macro simplifies the recursive call to the BuildDefRule
BuildDef = $(MAKE) /nologo /$(MAKEFLAGS) "Sources = $**" "Target = $@" "BaseNamePartOfTarget = $(@B)" BuildDefRule


#
# The BuildLibRule requires 2 macros be set:
#       Target = $@
#       Sources = $**
#
BuildLibRule :
        @echo.
        @echo Building: $(Target)
	implib /noignorecase /nologo $(Target:/=\) $(Target:.lib=.def)
	ilib /nobrowse /noext /nobackup /nologo /convformat $(Target:/=\);
	@echo Leaving BuildLibRule
	@echo.

# The following macro simplifies the recursive call to the BuildLibRule
BuildLib = $(MAKE) /nologo /$(MAKEFLAGS) "Sources = $**" "Target = $@" BuildLibRule


#
# The BuildDllRule requires 2 macros be set:
#       Target = $@
#       Sources = $**
# In addition, there is 1 optional macro:
#       RecFile = the name of the resource files to be bound to the dll
#
BuildDllRule :
        @echo.
        @echo Building: $(Target)
        @setlocal
        set PATH=$(NmakePATH)
	set LIB=$(NmakeLIB);
	set BeginLIBPATH=$(NmakeLIBPATH)
        @echo ilink $(LOPTS) /DLL /OUT:$(Target)
	@FOR %%f IN ($(Sources:/=\) $(LocalRuntimeLibrary:/=\)) DO @echo 	%%f
        @ilink $(LOPTS) /DLL /OUT:$(Target) @<<
 $(Sources) $(LocalRuntimeLibrary)
<<
!       IF "$(RecFile)"!=""
        	@echo.
		@-IF EXIST $(ResourceCompiler) \
        	   FOR %%f IN ($(RecFile)) DO \
		      $(ResourceCompiler) -p %%f $(Target)
		@-IF NOT EXIST $(ResourceCompiler) \
        	   FOR %%f IN ($(RecFile)) DO \
		      rc -p %%f $(Target)
!       ENDIF
        @set PATH=$(PATH)
	@set LIB=$(LIB)
        @endlocal
	@echo Leaving BuildDllRule

# The following macros simplify the recursive call to the BuildDllRule
BuildDll = $(MAKE) /nologo /$(MAKEFLAGS) "Sources = $**" "Target = $@" "LocalRuntimeLibrary=$(LocalRuntimeLibrary)" BuildDllRule

BuildDllWithRes = $(MAKE) /nologo /$(MAKEFLAGS) "Sources = $**" "Target = $@" "LocalRuntimeLibrary=$(LocalRuntimeLibrary)"




#..............................................................................
#                       clean up rules
#..............................................................................


Cleans : Clean
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f Cleans $(MAKEFLAGS)
!   ENDIF

Clean : CleanHdr CleanIdl CleanLib CleanDll CleanPkg


CleanHdrs : CleanHdr
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f CleanHdrs $(MAKEFLAGS)
!   ENDIF

CleanHdr : CleanMsg
!       IF "$(HdrTargets)"!=""
                @FOR %%f IN ($(HdrTargets)) DO IF EXIST $(IncludeDir)\%%f $(REMOVE) $(IncludeDir)\%%f
!       ENDIF
!       IF "$(IdlTargets)"!=""
                @FOR %%f IN ($(IdlTargets:.idl=.xh)) DO IF EXIST $(IncludeDir)\%%f $(REMOVE) $(IncludeDir)\%%f
!       ENDIF
!       IF "$(RcTargets)"!=""
                @FOR %%f IN ($(RcTargets:.rc=.res)) DO IF EXIST %%f $(REMOVE) %%f
!       ENDIF


CleanMsg : $(MsgTargets)
!       IF "$(MsgTargets)"!=""
                !IF EXIST $(**F) $(REMOVE) $(**F)
                !IF EXIST $(**B).h $(REMOVE) $(**B).h
                @FOR %%f IN ($(MsgTargets:/=\)) DO IF EXIST %%f $(REMOVE) %%f
!       ENDIF


CleanIdls : CleanIdl
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f CleanIdls $(MAKEFLAGS)
!   ENDIF

CleanIdl  : $(IdlTargets)
!       IF "$(IdlTargets)"!=""
                !IF EXIST $(IncludeDir)\$** $(REMOVE) $(IncludeDir)\$**
!       ENDIF


OS2LibTargets = $(LibTargets:/=\)

CleanLibs : CleanLib
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f CleanLibs $(MAKEFLAGS)
!   ENDIF

CleanLib :
!   IF "$(OS2LibTargets)"!=""
        IF EXIST *.obj $(REMOVE) *.obj
        IF EXIST *.xih $(REMOVE) *.xih
        @FOR %%f IN ($(OS2LibTargets)) DO IF EXIST %%f $(REMOVE) %%f
        @FOR %%f IN ($(OS2LibTargets:.lib=.def)) DO IF EXIST %%f $(REMOVE) %%f
!   ENDIF


CleanDlls : CleanDll
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f CleanDlls $(MAKEFLAGS)
!   ENDIF

CleanDll:
!   IF "$(DllTargets)"!=""
        @FOR %%f IN ($(DllTargets:/=\)) DO IF EXIST %%f $(REMOVE) %%f
!   ENDIF


CleanPkgs : CleanPkg
!   IF "$(Subdirs)"!=""
        @-FOR %%f IN ($(Subdirs)) DO \
		@$(ODSRC)\bin\NMakSubd %%f CleanPkgs $(MAKEFLAGS)
!   ENDIF

CleanPkg: CleanPkgParts
!   IF "$(RegMain)"!=""
	@FOR %%f IN ($(LocaleList)) DO \
	    IF EXIST $(ODSRC)\pkg\%%f\$(RegMain:.dll=.odz) $(REMOVE) $(ODSRC)\pkg\%%f\$(RegMain:.dll=.odz)
!   ENDIF

CleanPkgParts:
!   IF "$(RegMain)"!=""
	IF EXIST $(RegMain:.dll=.odt) $(REMOVE) $(RegMain:.dll=.odt)
	IF EXIST $(RegMain:.dll=.ZIP) $(REMOVE) $(RegMain:.dll=.ZIP)
	IF EXIST $(RegMain:.dll=.EXE) $(REMOVE) $(RegMain:.dll=.EXE)
	IF EXIST parts.lst $(REMOVE) parts.lst
!   ENDIF


# end of file

@echo off
rem @(#) 1.1 com/src/samples/shpin/buildme.cmd, odplugin, od96os2, odos29712d 2/27/97 15:12:14 [ 3/21/97 17:51:31 ]
rem
rem This command file is to build the sample shell plugin library

if "%ODSRC%" == "" goto runenv

:build
nmake 2>&1 | tee make.out

if "%OS2_SHELL%" == "" goto setshpinenv
echo
echo The shell plugin library iodshpin.dll is built and is located in
echo $(ODSRC)/dll directory. Please copy this dll into the OpenDoc
echo Shell plugin folder.
goto end

:runenv
call SampEnv
goto build

:setshpinenv
set ODSHELLPLUGINS=%ODSRC%\dll
:end

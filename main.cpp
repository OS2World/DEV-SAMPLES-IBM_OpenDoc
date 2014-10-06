/* @(#)Z 1.5 com/src/docshell/main.cpp, odshell, od96os2, odos29712d 97/03/21 17:41:22 (96/10/29 09:24:41) */
//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odshell
//
//   CLASSES: none
//
//   ORIGINS: 27
//
//
//   (C) COPYRIGHT International Business Machines Corp. 1995,1996
//   All Rights Reserved
//   Licensed Materials - Property of IBM
//   US Government Users Restricted Rights - Use, duplication or
//   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//   	
//   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
//   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
//   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
//   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
//   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
//   OR PERFORMANCE OF THIS SOFTWARE.
//
//====END_GENERATED_PROLOG========================================
//


#include "rlshell.h"


/**************************************************************************
 *
 *  Name       : main()
 *
 *************************************************************************/
int main (int argc, char *argv[])
{
    int returnValue = FALSE;
    // InitODMemory();

    // Create a RealShell and start it
    RealShell *shell = new RealShell;
    if (shell)
        returnValue = shell->go(argc,argv);

    return returnValue;
}




#ifdef _PLATFORM_WIN32_

#include <windows.h>
#include "rlshell.h"

int       WindowDisplayMode;
HANDLE    ApplicationInstance;

extern int  _argc;
extern char **_argv;


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                         LPSTR CmdLine, int CmdShow)
{
    int returnValue = FALSE;
    InitODMemory();

    // For now make hInstance and CmdShow global
    ApplicationInstance = hInstance;
    WindowDisplayMode = CmdShow;

    // Create a RealShell and start it
    RealShell *shell = new RealShell;
    if (shell)
        returnValue = shell->go(_argc, _argv);

    return returnValue;
}

#endif    // _PLATFORM_WIN32_

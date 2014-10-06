README for                                                          [Image]
OpenDoc® Graphics Editor Sample Part

---------------------------------------------------------------------------

Contents

   * Files and their Uses in this Part
        o Files shipped as Source in the Package
        o Files shipped as Binary, or Built
   * Functional Description of the GrafPart Sample
   * Compiling the GrafPart Sample
   * Executing the GrafPart Sample
   * Platform Dependance Issues
   * GrafPart Known Bugs and Limitations

---------------------------------------------------------------------------

Files in this part

Files shipped as Source in the Package

The following files are shipped in the OpenDoc distribution as source, and
are required to rebuild the GrafPart sample (without modification). All of
the following files are platform-independent, except as noted.

src/grafpart/makefile
     makefile for the Graphics editor and its content classes (for use with
     Nmake)
src/grafpart/README.htm
     HTML document containing directions for use of the GrafPart sample
     part (hypertext version of this file)
src/grafpart/README.txt
     Text file containing directions for use of the GrafPart sample part
     (flat text version of this file)
src/grafpart/iodgraph.gif
     Image file of the GrafPart editor icon
src/grafpart/iodgraph.rc
     Resource script file
src/grafpart/iodgradc.ico
     Source icon for "document" use (platform-specific)
src/grafpart/iodgraed.ico
     Source icon for "editor" use (platform-specific)
src/grafpart/iodgrast.ico
     Source icon for "stationery" use (platform-specific)
src/grafpart/iodgraph.hpp
     Global constants and defines
src/grafpart/iodgcomm.cpp
     Global common includes and preprocessor instructions
src/grafpart/iodgraph.def
     Object export definitions (platform-specific)
src/grafpart/iodgraph.idl
     SOM interface definition for the Graphics editor class
src/grafpart/iodgraph.cpp
     C++ implementation for the Graphics editor class
src/grafpart/iodgfigr.idl
     SOM interface definition for a "virtual" class which generically
     describes 2D figures.
src/grafpart/iodgfigr.cpp
     C++ implementation of the 'figure' class
src/grafpart/iodgpoin.idl
     SOM interface definition of a point figure class, which derives from
     the 'figure' class.
src/grafpart/iodgpoin.cpp
     C++ implementation of the point class
src/grafpart/iodgline.idl
     SOM interface definition of a line figure class, which derives from
     the 'figure' class
src/grafpart/iodgline.cpp
     C++ implementation of the line class
src/grafpart/iodgrect.idl
     SOM interface definition of a rectangle figure class, which derives
     from the 'line' class.
src/grafpart/iodgrect.cpp
     C++ implementation of the rect class
src/grafpart/iodgtext.idl
     SOM interface definition of a text figure class, which derives from
     the 'rect' class.
src/grafpart/iodgtext.cpp
     C++ implementation of the text class
src/grafpart/en_US/iodgraph.msg
     NLS message source for the Graphics editor in English for United
     States
src/grafpart/ja_JP/iodgraph.msg
     NLS message source for the Graphics editor in Japanese for Japan

Files shipped as Binary, or Built

The following files are shipped in the OpenDoc distribution as prebuilt
binaries, and will be overlayed (or ignored) when the GrafPart sample is
rebuilt (without modification). These binaries were built with the IBM
VisualAge for C++ product.

src/grafpart/iodgraph.RES
     Binary resource object for the Graphics editor class
src/grafpart/iodgraph.xih
     Private C++ language bindings for the Graphics editor class
src/grafpart/iodgraph.obj
     Binary object for the Graphics editor class
src/grafpart/iodgraph.odt
     Table of contents for the package file (platform-specific)
src/grafpart/iodgfigr.xih
     Private C++ language bindings for the 'figure' virtual class
src/grafpart/iodgfigr.obj
     Binary object for the 'figure' virtual class
src/grafpart/iodgpoin.xih
     Private C++ language bindings for the 'point' figure class
src/grafpart/iodgpoin.obj
     Binary object for the 'point' figure class
src/grafpart/iodgline.xih
     Private C++ language bindings for the 'line' figure class
src/grafpart/iodgline.obj
     Binary object for the 'line' figure class
src/grafpart/iodgrect.xih
     Private C++ language bindings for the 'rectangle' figure class
src/grafpart/iodgrect.obj
     Binary object for the 'rectangle' figure class
src/grafpart/iodgtext.xih
     Private C++ language bindings for the 'text' figure class
src/grafpart/iodgtext.obj
     Binary object for the 'text' figure class
dll/iodgraph.dll
     Dynamic Linked Library for the Graphics editor
include/iodgraph.idl
     Exported copy of the Graphics editor SOM class definition
include/iodgfigr.idl
     Exported copy of the 'figure' virtual SOM class definition
include/iodgpoin.idl
     Exported copy of the 'point' figure SOM class definition
include/iodgline.idl
     Exported copy of the 'line' figure SOM class definition
include/iodgrect.idl
     Exported copy of the 'rectangle' figure SOM class definition
include/iodgtext.idl
     Exported copy of the 'text' figure SOM class definition
include/iodgraph.hpp
     Exported copy of the global constants and defines
include/iodgraph.xh
     Public C++ language bindings for the Graphic editor class
include/iodgfigr.xh
     Public C++ language bindings for the 'figure' virtual class
include/iodgpoin.xh
     Public C++ language bindings for the 'point' figure class
include/iodgline.xh
     Public C++ language bindings for the 'line' figure class
include/iodgrect.xh
     Public C++ language bindings for the 'rectangle' figure class
lib/iodgraph.def
     Exported copy of the object export definitions (platform-specific)
lib/iodgraph.lib
     Linked object archive of all class objects
lib/iodgraph.exp
     Binary export list
src/grafpart/en_US/iodgraph.cat
     Compiled NLS message catalog for the Graphics editor in English for
     United States
pkg/iodgraph.odz
     Install-ready compressed binary-only part install file

Back to the Table of Contents.
---------------------------------------------------------------------------

Function Description

GrafPart is a sample of OpenDoc component software (part), which provides
basic two-dimensional vector graphics capabilities. It is provided to serve
as a model which OpenDoc part developers can use as a basis in designing
more sophisticated graphics-related parts, as well as to provide an
embeddable basic graphic function to the shipped set of GrafPart sample
parts.

Inherited Behaviors

The GrafPart is subclassed from the BaseContainer, which in turn, is
subclassed from ODPart, and thus inherits all part behaviors, such as

   * drag/drop support,
   * persistence,
   * properties,
   * clipboard operations,
   * base menubar,
   * drafts, and
   * printing.

Due to GrafPart's inheritance from BaseContainer, it provides a set of
container part behaviors, such as

   * embedding,
   * selection,
   * activation,
   * non-rectangular frames, and
   * content part
        o Z-order maintenance, and
        o background color manipulation.

Inherited Content types

GrafPart will display in its Embed menu all the part kinds currently
registered in the system, and allow the user to embed them as in the
BaseContainer

Intrinsic Behaviors

The intrinsic content is selectable and can be manipulated once selected
via keyboard/mouse input or clipboard functions. Specific manipulations
vary by figure type.

Intrinsic Content types

In addition to being able to imbed other OpenDoc part kinds, GrafPart may
also embed intrinsic content types and manipulate them as peers of full
OpenDoc part kinds. Intrinsic contents are instances of a set of classes
called "figures", which implement basic two-dimensional vector graphic
primitives, and include:

   * Point
   * Line
   * Rectangle
   * Text*

With provisions for the user to implement these additional types:

   * Circle
   * Ellipse
   * Polyline
   * Polygon
   * Freehand
   * Image

* - "Text" is not fully supported first-class implementation at this time,
that is, the class may be instantiated programmatically (ie., though the
scripting interface), but is not supported by GrafPart GUI, and thus cannot
created interactively.

Back to the Table of Contents.
---------------------------------------------------------------------------

Compiling the GrafPart Sample

The GrafPart binaries are shipped as compiled with IBM's VisualAge for C++
compilers on Windows and OS/2 platforms, with the nmake macro 'ODDebug'
turned on. The GrafPart source code also uses a local CPP symbol,
'GPDebug', to control various debugging functions. Specifically, if
GrafPart is compiled with the GPDebug CPP symbol defined, the following
will occur:

Trace messages are activated
     Each method of the GrafPart sample source code contains a message that
     is printed upon invocation, and another upon exit. In addition, many
     methods output various additional messages indicating status and
     parameter content. The output of these messages may be viewed by
     starting a receiver application, such as the MsgDisp.exe utility (on
     Windows platforms), or the PMPrintf.exe utility (on OS/2 platforms).
     With the appropriate message receiver application running, the
     performance of the GrafPart will be impacted, more severely with
     greater volume of embedded content. However, normal OpenDoc part
     performance can be regained simply by closing the receiver
     application. With the GPDebug CPP symbol not defined, no messages will
     be sent, regardless of the presence of a receiver application.
NLS catalog function is asserted
     If NLS catalog function fails, then default string values are used. If
     the GrafPart was compiled with the GPDebug CPP symbol defined, then
     those default string values will be in ALL UPPERCASE TEXT, to allow
     the developer to distinguish the default strings from strings obtained
     from an NLS catalog in the same language ("en_US"). The strings
     specifically affect by this feature are the menu items which GrafPart
     defines, which are:
   * the intrinsic content types in the "Embed" menu, and
   * the "Refresh screen" item in the "Options" menu.
     With the GPDebug CPP symbol not defined, The default strings will
     appear in mixed case, indistinguishable from the catalog strings for
     the locale, en_US. In most cases, failure of NLS catalog function is a
     result of bad or missing definition of the LOCALE and NLSPATH
     environment variables.

If you wish to recompile the GrafPart sample with these functions enabled,
you must first clear the system of any of the existing GrafPart binaries.
From the %ODBASE%/samples/src/grafpart directory, issue the following:

Nmake clean

The GPDebug CPP symbol may be defined in two ways:
* By uncommenting the line (remove the leading "#") in the makefile which
currently reads:

#ExtraCompileOptions    = -DGPDebug

* By invoking Nmake with an explicit command-line macro definition:

Nmake "ExtraCompileOptions    = -DGPDebug"

Back to the Table of Contents.
---------------------------------------------------------------------------

Executing the GrafPart Sample

The GrafPart editor may be started in any of the manners an OpenDoc part
may usually be run.

Adds to two of BaseContainer's main menubar items, Embed and Options. In
its Embed menu, GrafPart shows all the currently registered OpenDoc part
kinds, and then below a menu separator line all of the currently
implemented intrinsic content types.

Unlike embedding OpenDoc part kinds, GrafPart intrinsic content types are
embedded with a drag operation, as follows:

  1. Select "Embed" from the main menu.
  2. Select the desired intrinsic type in the pull-down menu, from amongst
     the items listed below the menu separator line.
  3. Press mouse button 1 in the GrafPart content area at the first point
     of the figure.
  4. Keeping MB1 depressed, drag the mouse to the second point in the
     desired figure. A representation of the figure will appear
     interactively, "rubberbanding" as you drag the mouse.
  5. Release MB1 at the second point.

For the "Point" type, you may use the above described method, or simply
place the cursor where the point is desired and click MB1.

As an aid to performance tuning and a demonstration vehicle, the method of
updating the screen during the "rubberbanding" process is user-selectable
at run-time. In the environment from which DocShell will be started, set an
environment variable 'GP_REFRESH' to a value between '1' and '3', with the
following meanings:

GP_REFRESH=1
     The whole current frame will be invalidated with each pixel of mouse
     movement. This is the most time- and resource-intensive method, but is
     smoothest performing method on systems with the speed to handle it.
     This is the default if the GP_REFRESH environment variable is not set.
GP_REFRESH=2
     Only the shape of the current figure in the current facet will be
     invalidated with each pixel of mouse movement. This is less resource-
     and computation-intensive, but is still a synchronous process.
GP_REFRESH=3
     The shape of the current figure in the current facet will be updated
     with each pixel of mouse movement. This is the least resource- and
     computation-intensive, as it is an asynchronous process, but may
     produce 'jumpy' feedback performance on slower systems.

In the Options main menubar, GrafPart implements a "Refresh Screen" menu
item, which, when selected, will immediately perform a invalidation on all
frames belonging to that GrafPart instance, synchronizing them and causing
them to redraw their contents. This useful if more than one frame exists,
or if the content area has become polluted due to a drag operation.

Back to the Table of Contents.
---------------------------------------------------------------------------

Platform Dependance Issues

GrafPart is written to utilize National Language Support for catalogs. Its
proper operation for the display of its implemented menu items is dependant
on settings of the LANG and NLSPATH environment variables.

Back to the Table of Contents.
---------------------------------------------------------------------------

GrafPart Known Bugs and Limitations

   * Due to NLS dependance, GrafPart requires an NLS-compliant compiler.
     Currently it has only been tested with IBM's VisualAge for C++
     compilers on Windows and OS/2 platforms.
   * No keypress handling.
   * Limited available implemented intrinsic content types.
   * No editing of intrinsic content types, besides move and resize.
   * Intrinsic content types have no user-definable or editable attributes.
   * Some possible user scenarios may be confusing, such as attempting to
     embed within the selection threshold of an intrinsic content item.
   * Unnecessary screen refreshes under certain conditions.

Back to the Table of Contents.
---------------------------------------------------------------------------
©. 1996 IBM Corporation. All rights reserved.

Last updated: 2/7/97 17:42:32 

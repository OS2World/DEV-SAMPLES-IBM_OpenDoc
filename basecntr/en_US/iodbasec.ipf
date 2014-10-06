:USERDOC.
:DOCPROF TOC='123456'.
:TITLE.Container Part Online Helps
:H1 id='A100' res=100.Container Part General Help
:I1 ID='WQX2'.Container Part general help
:P.
The Container Part sample component demonstrates the OpenDoc functionality
for containing parts. You can use the Container to embed other parts. When
the parts are embedded, they can be selected, cut, copied, pasted, deleted,
moved, and resized.
:P.Your part can subclass from the Container Part to provide an OpenDoc
application
that can contain other OpenDoc components.  The Container also provides the
ability for subclassing parts to intermix their intrinsic content items with
the embedded frames of the Container.
:H1 id='A200' res=200.Move To Front
:I1 ID='WQX3'.moving selected content to the front of the Z-order
:P.
Use the :HP2.Move to front:EHP2. menu item to move the selected
content to the front of the Z-order.  If multiple content items are selected,
the relative order of the items will be preserved as they are moved to the
front of the Z-order.
:P.To use :HP2.Move to front:EHP2.&colon.
:OL.
:LI.Use Ctrl&plus.mouse button 1 to select the items whose Z-order will be
changed.
:LI.Select :HP2.Move to front:EHP2. from the :HP2.Edit:EHP2. menu.
:EOL. 
:H1 id='A201' res=201.Move To Back
:I1 ID='WQX4'.moving selected content to the back of the Z-order
:P.
Use the :HP2.Move to back:EHP2. menu item to move the selected
content to the back of the Z-order.  If multiple content items are selected,
the relative order of the items will be preserved as they are moved to the
back of the Z-order.
:P.To use :HP2.Move to back:EHP2.&colon.
:OL.
:LI.Use Ctrl&plus.mouse button 1 to select the items whose Z-order will be
changed.
:LI.Select :HP2.Move to back:EHP2. from the :HP2.Edit:EHP2. menu.
:EOL. 
:H1 id='A202' res=202.Move
:I1 ID='WQX5'.moving selected content within the document
:P.
Use the :HP2.Move:EHP2. menu item to reposition content items
within the document. This menu item supports single selection only.
:P.To use :HP2.Move:EHP2.&colon. 
:OL.
:LI.Use Ctrl&plus.mouse button 1 to select the item to be moved.
:LI.Select :HP2.Move:EHP2. from the :HP2.Edit:EHP2.
menu.
:LI.Click on the new origin of the content item. This origin is the upper-left
corner of the item's bounding box.
:EOL. 
:P.You can also move content items by dragging the selection border using
mouse button 1. To move single or multiple content items using the
mouse&colon. 
:OL.
:LI.Use Ctrl&plus.mouse button 1 to select each item to be moved.
:LI.Press and hold the mouse button over any part of the selection border
that does not contain a resize handle.
:LI.Drag the border to the new position of the content items.
:LI.Release the mouse button to reposition the items.
:EOL. 
:NT.
Moving content items will not change their Z-order. Moving
an object by clicking within the selection border is equivalent to dragging
the object.
:ENT. 
:H1 id='A203' res=203.Resize
:I1 ID='WQX6'.resizing a content item
:P.
:P.Use the :HP2.Resize:EHP2. menu item to resize a content item.
This menu item supports single selection only and is a short cut to dragging
the upper right resize handle with the mouse.
:P.To resize an item&colon. 
:OL.
:LI.Use Ctrl&plus.mouse button 1 to select the item to be resized.
:LI.Select :HP2.Resize:EHP2. from the :HP2.Edit:EHP2.
menu.
:LI.Click on the new extent of the content. The upper-left corner of the
item's
bounding box remains fixed. The location in which you click becomes the
diagonally
opposite corner of the new bounding box.
:EOL. 
:P.You can also resize a content item by dragging the resize handles on its
selection border. To resize a content item using its handles&colon. 
:OL.
:LI.Use Ctrl&plus.mouse button 1 to select the item to be resized.
:LI.Press and hold the mouse button while pointing to one of the eight resize
handles on the selection border.  There is one resize handle on each corner
and one on each side of the selection border.
:LI.Drag the resize handle to modify the size of the content item.
:LI.Release the mouse button to resize the item.
:EOL. 
:H1 id='A204' res=204.Embed
:I1 ID='WQX7'.embedding another OpenDoc part
:P.
Use the :HP2.Embed:EHP2. menu to embed an OpenDoc part in a
document.
:P.To embed a part&colon. 
:OL.
:LI.Select :HP2.Embed:EHP2. from the menu bar.
:LI.Select the part to embed from the list of registered part kinds.
:LI.Click on the origin at which to embed the new part. This origin is the
upper-left corner of the item's bounding box.
:EOL. 
:NT.
An OpenDoc part can also be embedded by dragging a copy of
the part's stationery from the Stationery folder.
:ENT. 
:H1 id='A205' res=205.Change Background
:I1 ID='WQX8'.changing the background color
:P.
Use the :HP2.Change Background:EHP2. menu item to change the
background color of the Container part.
:P.To change the background&colon. 
:OL.
:LI.Select :HP2.Change Background:EHP2. from the :HP2.Options:EHP2. menu. A
platform-specific color dialog is displayed
:LI.Select the new background color using the platform-specific color dialog.
:LI.Select the :HP2.OK:EHP2. push button.
:EOL. 
:H1 id='A206' res=206.Options
:I1 ID='WQX9'.Options menu
:P.
The :HP2.Options:EHP2. menu (provided by the Container
part) provides a list of additional functions not found in any of the other
menus. Subclassing parts can add their own menu items to this menu.
:EUSERDOC. 

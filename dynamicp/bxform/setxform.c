/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: oddynamicpart
 *
 *   CLASSES: none
 *
 *   ORIGINS: 82,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *   	
 *   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 *   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 *   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 *   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 *   OR PERFORMANCE OF THIS SOFTWARE.
 */
/*====END_GENERATED_PROLOG========================================
 */
/* @(#) 1.5 com/src/samples/dynamicp/bxform/setxform.c, oddynamicpart, od96os2, odos29712d 2/7/97 18:32:13 [3/21/97 17:44:51]
*******************************************************************
** Name: void SetInternalXform
**
** Description:  Modified the internal transform to affect rotation
**               and shearing within the part
**
** Parameters:   frame - the frame which should be transformed
**
*******************************************************************
*/
try {
   ODFrameFacetIterator* facets = frame->CreateFacetIterator(ev);
   ODFacet* facet = facets->First(ev);
   delete facets;

   // These are used in the matrix calculations...
   ODFloat cos_O = 1.0;
   ODFloat sin_O = 0.0;
   ODFloat Kh = 0;      // horizontal shear factor
   ODFloat Kv = 0;      // vertical shear factor

   somSelf->CalcRotationFactors(ev, &sin_O, &cos_O, &Kh, &Kv);

   // Set up the internal transform with rotations and shearing.
   try {

      ODRect frameRect;
      ODShape *frameShape = frame->AcquireFrameShape(ev, kODNULL);
      frameShape->GetBoundingBox(ev, &frameRect);
      frameShape->Release(ev);
      ODPoint center;
      center.x = (frameRect.right  - frameRect.left)  / 2;
      center.y = abs(frameRect.top - frameRect.bottom)/ 2;

      ODCanvas* canvas = facet->GetCanvas(ev);

      /* rotate facet about the origin of the frame */

      //                         //
      // Set up rotation matrix  //
      //                         //

      // Create a new Transform and obtain a transform matrix from it.
      ODTransform *newTransform = frame->CreateTransform(ev);
      ODTransform *rotateXform  = frame->CreateTransform(ev);
      ODTransform *shearXform   = frame->CreateTransform(ev);
      ODMatrix matrix;

      // first, translate the center of the new transform matrix to the origin of the frame
      ODPoint centerShift;
      centerShift.x = ODIntToFixed(-drawXdimension/2);// -center.x;
      centerShift.y = ODIntToFixed(-drawYdimension/2);// -center.y;

      // calculate the matrix to rotate _xRotAngle degrees about the origin
      rotateXform->GetMatrix(ev, &matrix);
      matrix.m[0][0] = ODFloatToFixed( cos_O);
      matrix.m[0][1] = ODFloatToFixed(-sin_O);
      matrix.m[1][0] = ODFloatToFixed(sin_O);
      matrix.m[1][1] = ODFloatToFixed(cos_O);
      // Element (2,2) of the ODTransform matrix is an ODFract value.
      // ODFract represents a 2-bit integer (including sign) with a 30-bit fractional part.
      // Do not change this value from the initial "identity" value.
      // matrix.m[2][2] = ODFixedToFract(ODIntToFixed(1));
      rotateXform->SetMatrix(ev, &matrix);
      if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}

      // calculate the matrix to shear _hShearAngle horizontally and _vShearAngle vertically
      shearXform->GetMatrix(ev, &matrix);
      matrix.m[0][1] = ODFloatToFixed(Kv);
      if ((_hShearAngle > degrees_90) &&
          (_hShearAngle < degrees_270)) {
         matrix.m[1][1] *= -1;
      } /* endif */
      matrix.m[1][0] = ODFloatToFixed(Kh);
      if ((_vShearAngle > degrees_90) &&
          (_vShearAngle < degrees_270) ) {
         matrix.m[0][0] *= -1;
      } /* endif */
      shearXform->SetMatrix(ev, &matrix);
      if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}

      // Now use the matrix to make the new Transform transformation equivalent
      // to matrix.
      newTransform->MoveBy(ev, &centerShift);
      if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
      newTransform->PostCompose(ev, shearXform);
      if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
      newTransform->PostCompose(ev, rotateXform);
      if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
      rotateXform->Release(ev);
      shearXform->Release(ev);

     /////////////////////////////////////////////////////////////
     // Now scale the figure so it will fit in the existing frame
     try {
       // make array of four points from frameRect
       ODPoint  corner[4] = { {0,               drawYdimension},
                              {0,               0},
                              {drawXdimension,  drawYdimension},
                              {drawXdimension,  0}};
       // transform this array
       newTransform->TransformPoint(ev, &corner[0]);
       if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
       newTransform->TransformPoint(ev, &corner[1]);
       if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
       newTransform->TransformPoint(ev, &corner[2]);
       if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
       newTransform->TransformPoint(ev, &corner[3]);
       if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
       // calculate scale to keep
       ODCoordinate maxWidth =
             max(corner[0].x, max(corner[1].x, max(corner[2].x, corner[3].x)))  //  largest X
           - min(corner[0].x, min(corner[1].x, min(corner[2].x, corner[3].x))); // -smallest X
       ODCoordinate maxHeight=
             max(corner[0].y, max(corner[1].y, max(corner[2].y, corner[3].y)))  //  largest Y
           - min(corner[0].y, min(corner[1].y, min(corner[2].y, corner[3].y))); // -smallest Y
       ODFloat scale = (ODFloat)(frameRect.right-frameRect.left)/ max(maxWidth, maxHeight);
       // create a transformation to scale matrix by this amount
       ODPoint scaleFactor;
       scaleFactor.x = (frameRect.right - frameRect.left)/max(maxWidth, maxHeight);
       scaleFactor.y = abs(frameRect.top - frameRect.bottom)/max(maxWidth, maxHeight);
       newTransform->ScaleBy(ev, &scaleFactor);
       if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
       //Now translate the center of the figure back to the center of the frame
       centerShift.x = center.x;
       centerShift.y = center.y;
       newTransform->MoveBy(ev, &centerShift);
       if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
       // Make sure the diagonals (scale factors) are not zero.
       // OpenDoc does not like zeros in these fields!
       newTransform->GetMatrix(ev, &matrix);
       const ODFixed SmallestScale = 0x00000100;
       if (abs(matrix.m[0][0]) < SmallestScale) {
          matrix.m[0][0] = SmallestScale * ((matrix.m[0][0]>0)?1:-1);
       }
       if (abs(matrix.m[1][1]) < SmallestScale) {
          matrix.m[1][1] = SmallestScale * ((matrix.m[1][1]>0)?1:-1);
       }
#ifdef _PLATFORM_WIN32_
     if ( (long)GetVersion() < 0 ) {
       // Win '95 doesn't support rotation, so don't
       // include rotation components in matrix.
       matrix.m[0][1] = 0;
       matrix.m[1][0] = 0;
     } /* endif */
#endif
       newTransform->SetMatrix(ev, &matrix);
     } catch (...) {
       reportAnyException(ev);
       return;
     } /* end try */
     /////////////////////////////////////////////////////////////

      ODTransform* oldTransform = frame->AcquireInternalTransform(ev, canvas);

      // If the new transform is different from the old, use it to change
      // the internal transform of the frame.
      if (!newTransform->IsSameAs(ev,oldTransform)) {
         frame->ChangeInternalTransform(ev, newTransform, canvas);
         if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
         // set shape to correspond to new transform
         somSelf->CalcNewShape(ev, frame);
         frame->Invalidate(ev, kODNULL, canvas);
      }
      newTransform->Release(ev);
      oldTransform->Release(ev);

   } catch (IException &exc) {
      reportIException(exc);
   } /* end try */
} catch (...) {
   reportAnyException(ev);
} /* end try */


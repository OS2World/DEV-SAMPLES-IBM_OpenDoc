/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: oddynamicpart
 *
 *   CLASSES:   DynamicPartRotateFn
 *		DynamicPartScrollFn
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
/*  @(#) 1.2 com/src/samples/dynamicp/bdynamic/timerfns.h, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:41 (96/11/01 08:48:59)
*******************************************************************
** Name: class DynamicPartRotateFn
**
** Description:  subclass of ITimerFn which is called when
**               the rotateTimer ITimer object fires.
**
*******************************************************************
*/

class DynamicPartRotateFn : public ITimerFn {
  typedef ITimerFn
    Inherited;
  public:
  /*------------------------------- Constructors -------------------------------*/
  DynamicPartRotateFn ( DynamicPart &object )
    : fObject( object )
    {
    }

  /*---------------------------- Timer Expiration ------------------------------*/
  virtual void
    timerExpired ( unsigned long timerId )
    {
    Environment *ev = somGetGlobalEnvironment();
    fObject.RotateContent(ev, fObject._get_xAngleDelta(ev) );
    }

  private:
  /*----------------------------- Hidden Members -------------------------------*/
    DynamicPartRotateFn ( const DynamicPartRotateFn& timerFunction );
  DynamicPartRotateFn
   &operator=       ( const DynamicPartRotateFn& timerFunction );

  /*--------------------------------- Private ----------------------------------*/
  DynamicPart &fObject;
}; // DynamicPartRotateFn

/*
*******************************************************************
** Name: class DynamicPartScrollFn
**
** Description:  subclass of ITimerFn which is called when
**               the scrollTimer ITimer object fires.
**
*******************************************************************
*/
class DynamicPartScrollFn : public ITimerFn {
  typedef ITimerFn
    Inherited;
  public:
  /*------------------------------- Constructors -------------------------------*/
  DynamicPartScrollFn ( DynamicPart &object )
    : fObject( object )
    {
    }

  /*---------------------------- Timer Expiration ------------------------------*/
  virtual void
    timerExpired ( unsigned long timerId )
    {
    Environment *ev = somGetGlobalEnvironment();
    fObject.ScrollTicker(ev);
    }

  private:
  /*----------------------------- Hidden Members -------------------------------*/
    DynamicPartScrollFn ( const DynamicPartScrollFn& timerFunction );
  DynamicPartScrollFn
   &operator=       ( const DynamicPartScrollFn& timerFunction );

  /*--------------------------------- Private ----------------------------------*/
  DynamicPart &fObject;
}; // DynamicPartScrollFn
/////////////////////////////////////////////////////////////////////////////////

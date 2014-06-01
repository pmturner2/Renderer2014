/** GameTimer.h -- Header File for Game Timer Class
 *  Peter Turner - Spring 2012
 */

#pragma once
#include "stdafx.h"


/** class GameTimer - tracks time
 */
class GameTimer
{
public:
   GameTimer(void);
   ~GameTimer(void);

   // Returns difference between frames
   float GetDt(void) const;

   // Total Time 
   float GetGameTime(void) const;

   // Display string HH:MM AM/PM
   bool BuildWorldTimeString(float angle, WCHAR *buffer);

   // Oncer per frame
   void Tick(void);

   void Reset(void);
   void Stop(void);
   void Start(void);
   
private:
   double secPerCount;
   double dt;

   __int64 baseTime;
   __int64 pausedTime;
   __int64 stopTime;
   __int64 prevTime;
   __int64 currentTime;

   bool stopped;
};


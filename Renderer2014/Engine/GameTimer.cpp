/** GameTimer.cpp -- Code File for Game Timer Class
 *  Peter Turner - Spring 2012
 */

#include "GameTimer.h"


GameTimer::GameTimer(void):secPerCount(0), dt(-1), baseTime(0), pausedTime(0),
   prevTime(0), currentTime(0), stopped(false) {
   __int64 countsPerSec; // Frequency of the Counter
   QueryPerformanceFrequency((LARGE_INTEGER *) &countsPerSec);
   this->secPerCount = 1.0/(double)countsPerSec; // store the period 1/freq   
}


GameTimer::~GameTimer(void) { }


void GameTimer::Tick(void) {
   if (stopped) {
      dt = 0.0;
      return;
   }

   __int64 now;
   QueryPerformanceCounter((LARGE_INTEGER *) &now);
   this->currentTime = now;

   this->dt = (this->currentTime - this->prevTime) * secPerCount;
   this->prevTime = this->currentTime;

   if (this->dt < 0.0) {
      this->dt = 0.0;
   }
}


void GameTimer::Reset(void) {
   __int64 now;
   QueryPerformanceCounter((LARGE_INTEGER *) &now);
   this->baseTime = now;
   this->prevTime = now;
   this->stopTime = 0;
   this->stopped = false;
}


float GameTimer::GetDt(void) const {
   return dt;
}


void GameTimer::Stop(void) {
   if (!(this->stopped)) {
      __int64 now;
      QueryPerformanceCounter((LARGE_INTEGER *) &now);
      this->stopTime = now;
      this->stopped = true;
   }
}

void GameTimer::Start(void) {
   __int64 start;
   QueryPerformanceCounter((LARGE_INTEGER *) &start);

   if (this->stopped) {
      this->pausedTime += (start - this->stopTime);
      this->prevTime = start;
      this->stopTime = 0;
      this->stopped = false;
   }
}


float GameTimer::GetGameTime() const { // returns time in seconds
   if (0) {//this->stopped) {
      return (float) ((this->stopTime - this->baseTime) * this->secPerCount);
   } else {
      return (float) ((this->currentTime - this->pausedTime) - this->baseTime) * this->secPerCount;
   }
}


bool GameTimer::BuildWorldTimeString(float angle, WCHAR *buffer) {
   if (buffer == NULL || angle < 0 || angle > 2 * 3.14f) {
      return false;
   }
   WCHAR *c = buffer;

   // Clear Buffer
   while ((*c) != 0) {
      *c = 0;
      c++;
   }
   WCHAR amPm[3] = { L'A', L'M', 0 };

   const int secondsInDayOver2 = 43200;
   const int secondsInHour = 3600;
   const int secondsInMinute = 60;

   float worldTime = angle * secondsInDayOver2 / 3.1415f;

   if (worldTime < secondsInDayOver2) { // PM
      amPm[0] = L'P';    
   }   

   float hourF = worldTime / secondsInHour;
   float remainder = (int) worldTime % secondsInHour;
   float minuteF =  remainder/secondsInMinute;
   
   int hour = (int) hourF;
   int minute = (int) minuteF;    

   if (hour < 1) {
      hour = 12;
   } else if (hour > 12) { // So we don't have 13:00pm
      hour -= 12;
   }
   
   if (_stprintf(buffer, L"%02d:%02d %s", hour, minute, amPm) <= 0) {
      return false;
   }
   return true;
}
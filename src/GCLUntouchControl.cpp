/**
 * 
 * GCLUntouchControl.cpp - TUntouchControl class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLUntouchControl.h>

/**
 * Конструктор
 */
TUntouchControl::TUntouchControl() {
  //шрифт
  this->setFont(arial_bold_rus);
  this->AlignCaption = DT_LEFT;
  this->FontColor = CL_FONTCOLOR;
  //цвета
  this->Color = CL_NONE;
  this->BorderColor = CL_NONE;
}

/**
 * Заглушка нажатия 
 */
void TUntouchControl::press() {
#ifndef RELEASE  
  Serial.println("TUntouchControl press");
#endif
}

/**
 * Заглушка отпускания
 */
void TUntouchControl::click() {
#ifndef RELEASE  
  Serial.println("TUntouchControl click");
#endif
}

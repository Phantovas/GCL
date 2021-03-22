/**
 * 
 * GCLLabel.cpp - TLabel class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLLabel.h>

/**
 * Конструктор
 */
TLabel::TLabel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //задаем значеняи
  this->Color = CL_NONE;
  //шрифт
  this->setFont(arial_bold_rus);
  this->AlignCaption = DT_LEFT;
  this->FontColor = CL_FONTCOLOR;
  //события
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
}

/**
 * Рисуем метку
 */
void TLabel::paint() {
#ifndef RELEASE  
  Serial.println("paint label");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw label");
#endif
    //заливаем блок
    this->fillClientRect(this->Color);
    if (this->Caption) {
      this->textOut(this->getCaption(), this->getFontColor(), this->getClientRect(), this->AlignCaption);
    }  
  }
}

/**
 * 
 * GCLButton.cpp - TButton class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLButton.h>

/**
 * Конструктор
 */
TButton::TButton(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //события
  this->onClick = NULL;
  this->onPress = NULL;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
}

/**
 * Рисуем панель
 */
void TButton::paint() {
#ifndef RELEASE  
  Serial.println("paint button");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw button");
#endif
    //заливаем блок
    this->fillClientRect(this->Color);
    //рисуем бордюр
    if (this->isEnable() && this->getActive()) {
      this->drawBorder(this->ActiveBorderColor);
    } else {
      this->drawBorder(this->BorderColor);
    }
    if (this->Caption) {
      if (this->isEnable())
        this->textOut(this->getCaption(), this->getFontColor(), this->getClientRect(), this->AlignCaption);
      else
        this->textOut(this->getCaption(), CL_DISABLEFONTCOLOR, this->getClientRect(), this->AlignCaption);
    }  
  }
}
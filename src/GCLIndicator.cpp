/**
 * 
 * GCLIndicator.cpp - TIndicator class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLIndicator.h>

/**
 * Конструктор
 */
TIndicator::TIndicator(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //задаем значеняи
  this->_bitmapWidth = 22;
  this->_bitmapHeight = 22;
  this->Color = CL_NONE;
  //события
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
  //состояние
  this->Checked = false;
}

/**
 * Рисуем метку
 */
void TIndicator::paint() {
#ifndef RELEASE  
  Serial.println("paint indicator");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw indicator");
#endif
    //заливаем блок
    this->fillClientRect(this->Color);  
    if (this->Checked) {
      this->drawBitmap(this->_bitmapWidth, this->_bitmapHeight, icon_check);
    } else {
      this->drawBitmap(this->_bitmapWidth, this->_bitmapHeight, icon_uncheck);
    }
  }
}

/**
 * Установка включенного состояния
 */
void TIndicator::check() {
  if (!this->Checked) {
    this->Checked = true;
    this->paint();
  }
}

/**
 * Функция выключенного состояния
 */
void TIndicator::uncheck() {
  if (this->Checked) {
    this->Checked = false;
    this->paint();
  }
}

/**
 * Функция установки нужного состояни
 * @param AValue
 */
void TIndicator::setChecked(bool AValue) {
  if (this->Checked != AValue) {
    if (AValue) 
      this->check();
    else
      this->uncheck();
  }
}
/**
 * 
 * GCLTouchControl.cpp - TTouchControl class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLTouchControl.h>

/**
 * Конструктор 
 */  
TTouchControl::TTouchControl() {
  //шрифт
  this->setFont(arial_bold_rus);
  this->AlignCaption = DT_CENTER;
  this->FontColor = CL_FONTCOLOR;
  //задаем значеняи
  this->Color = CL_BTNCOLOR;
  this->Border = 1;
  this->BorderColor = CL_BORDERCOLOR;
  this->ActiveBorderColor = CL_ACTIVEBORDERCOLOR;
  this->_Enabled = true;      //чаще будут активные, чем неактивные
}  
  
/**
 * Функция установки цвета активного бордюра
 * @param AValue
 */
void TTouchControl::setActiveBorderColor(word AValue) {
  if (this->Active && (this->ActiveBorderColor != AValue)) {
    this->ActiveBorderColor = AValue;
    this->drawBorder(this->ActiveBorderColor);
  }
}

/**
 * Возврат цвета активного бордюра
 */
word TTouchControl::getActiveBorderColor() {
  return this->ActiveBorderColor;
}  

/**
 * Функция обработки нажатия
 */
void TTouchControl::press() {
  if (this->isEnable()) {
#ifndef RELEASE 
    Serial.println("ActiveControl press ");
#endif
    if (!this->Active)
      this->drawBorder(this->ActiveBorderColor);
    if (this->onPress)
      this->onPress();  
  }
}

/**
 * Функция обработки отпускания
 */
void TTouchControl::click() {
  if (this->isEnable()) {
#ifndef RELEASE    
    Serial.println("ActiveControl click");
#endif
    if (!this->Active)
      this->drawBorder(this->BorderColor);
    if (this->onClick)
      this->onClick();  
  }
}

/**
 * Функция получения состояния кнопки
 * @return 
 */
bool TTouchControl::isEnable() {
  return this->_Enabled;
}

/**
 * Функция активирования кнопки
 */
void TTouchControl::Enable() {
  if (!this->_Enabled) { 
    this->_Enabled = true;
    this->painting();
  }
}

/**
 * Функция деактивации кнопки
 */
void TTouchControl::Disable() {
  if (this->_Enabled) {
    this->_Enabled = false;
    this->painting();
  }
}

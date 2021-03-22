/**
 * 
 * GCLSlider.cpp - TSlider class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLSlider.h>

/**
 * Конструктор слайдера
 */
TSlider::TSlider(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //установки
  this->_Checked = false;
  this->AlignCaption = DT_CENTER;
  this->BorderColor = CL_BLACK;
  //события
  this->onClick = NULL;
  this->onPress = NULL;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
  this->setFont(SmallFont);
}  

/**
 * Рисуем слайдер
 */
void TSlider::paint() {
  TRect sliderRect, fillRect;
  word printColor, oldColor;
  uint8_t mPixel = 3; 
#ifndef RELEASE  
  Serial.println("paint slider");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw slider");
#endif
    //области
    sliderRect = this->getClientRect();
    fillRect = this->getClientRect();;
    //цвета
    oldColor = this->Color;
    if (this->isEnable())
      printColor = this->FontColor;
    else
      printColor = CL_DISABLEFONTCOLOR;
    //заливаем фоном родителя или черным
    if (this->Parent != NULL)
      this->fillRect(this->Parent->Color, fillRect);      
    else
      this->fillRect(this->BorderColor, fillRect);      
    //уменьшаем регион по высоте
    fillRect.Top = fillRect.Top + mPixel;
    fillRect.Bottom = fillRect.Bottom - mPixel;
    if (this->isChecked()) {
      //считаем размер скользящего блока
      sliderRect.Left = sliderRect.Left + 2*this->getClientWidth()/3;   //сдвигаем на 2/3
      //рисуем
      this->fillRect(CL_LIME, fillRect);      
      this->fillRect(this->Color, sliderRect);
      //считаем размер региона для вывода надписи посередине
      fillRect.Right =  fillRect.Left + 2*this->getClientWidth()/3;
      this->Color = CL_LIME;
      this->textOut("ON", printColor, fillRect, this->AlignCaption);  //ON - BJK (ВКЛ)
    } else {
      //считаем размер скользящего блока
      sliderRect.Right =  sliderRect.Left + this->getClientWidth()/3; //всего 1/3 от длины слайдера
      //рисуем
      this->fillRect(CL_RED, fillRect); 
      this->fillRect(this->Color, sliderRect);
      //считаем размер региона для вывода надписи посередине
      fillRect.Left = fillRect.Left + this->getClientWidth()/3;
      this->Color = CL_RED;
      this->textOut("OFF", printColor, fillRect, this->AlignCaption);  //OFF - B[JK (ВЫКЛ)
    }
    this->Color = oldColor;
    //рисуем бордюр
    if (this->isEnable() && this->getActive()) {
      //this->drawBorderRect(this->ActiveBorderColor, sliderRect);
    } else {
      //this->drawBorderRect(this->BorderColor, sliderRect);
    }
  }
}

/**
 * Функция изменения на включено
 */
void TSlider::Check() {
  if (!this->_Checked) {
    this->_Checked = true;
    this->painting();
  }
}

/**
 * Функция изменения состояния на отключено
 */
void TSlider::Uncheck() {
  if (this->_Checked) {
    this->_Checked = false;
    this->painting();
  }
}


/**
 * Установка цвета движущегося блока
 * @param AValue
 */
void TSlider::setSliderColor(word AValue) {
  if (this->SliderColor != AValue) {
    this->SliderColor = AValue;
    this->painting();
  }
}

/**
 * Переопределенный метод реакции на отпускание
 */
void TSlider::click() {
  if (this->isEnable()) {
    //изменяем состояние и вызываем клик парента
    if (this->isChecked()) 
      this->Uncheck();
    else
      this->Check();
  }
  TTouchControl::click();
}
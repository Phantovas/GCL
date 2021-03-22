/**
 * 
 * GCLTrackBar.cpp - TTrackBar class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLTrackBar.h>

/**
 * Конструктор с библиотекой UTFT
 */
TTrackBar::TTrackBar(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  this->BorderColor = CL_BORDERCOLOR;
  this->Border = 1;
  this->_CursorColor = CL_PROGRESSCOLOR;
  //перовоначальные значения
  this->_Min = 0;
  this->_Max = 100;
  this->Step = 1;
  this->Value = 0;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
  //установка размеров указателя
  this->_TypeBar = TB_CURSOR;
  this->setCursorRect();
}

/**
 * Функция установки минимального значения 
 * @param AValue
 */
void TTrackBar::setMin(int AValue) {
  if (this->_Min != AValue) {
    this->_Min = AValue;
    this->setCursorRect();
    this->paint();
  }
}

/**
 * Функция установки максимального значения 
 * @param AValue
 */
void TTrackBar::setMax(int AValue) {
  if (this->_Max != AValue) {
    this->_Max = AValue;
    this->setCursorRect();
    this->paint();
  }
}


/**
 * Функция установки текущего значения 
 * @param AValue
 */
void TTrackBar::setValue(int AValue) {
  AValue = constrain(AValue, this->_Min, this->_Max);
  if (this->Value != AValue) {
    this->Value = AValue;
    this->setCursorRect();
    this->paint();
  }
}

/**
  * Функция увеличения значения
 */
void TTrackBar::inc() {
  this->setValue(this->Value + this->Step);
}

/**
 * Функция уменьшения значения
 */
void TTrackBar::dec() {
  this->setValue(this->Value - this->Step);
}

/**
 * Функция расчета размеров курсора
 */
void TTrackBar::setCursorRect() {
  float _Pos;
  this->_CursorRect.Top = 0;
  this->_CursorRect.Bottom = this->getClientHeight();
  //пересчитываем размер указателя
  switch (this->_TypeBar) {
    case TB_CURSOR: {
      //если шире, чем пол высоты
      if (this->getClientWidth() > this->getClientHeight()/2) {
        /*
         * (this->getClientWidth()  - this->getClientHeight()/2)/(this->_Max - this->_Min) количество пикселей на одно значение - сдвиг на ширину курсора this->getClientHeight()/2
         * (this->Value - this->_Min) сдвиг относительно нулевого угла (пример -50..50, 0 - это сдвиг на 50 значений)
         */
        _Pos = (float)(this->getClientWidth() - this->getClientHeight()/2)/(this->_Max - this->_Min)*(this->Value - this->_Min);
        this->_CursorRect.Left = (int)_Pos;
        this->_CursorRect.Right = this->_CursorRect.Left + this->getClientHeight()/2;
        
      } else {
        //иначе
        this->_CursorRect.Left = 0;
        this->_CursorRect.Right = this->getClientWidth();
      }
      break;
    }
    case TB_PROGRESS: {
      /*
       * this->getClientWidth()/(this->_Max - this->_Min) количество пикселей на одно значение 
       * (this->Value - this->_Min) сдвиг относительно нулевого угла (пример -50..50, 0 - это сдвиг на 50 значений)
       */
      this->_CursorRect.Left = 0;
      _Pos = (float)this->getClientWidth()/(this->_Max - this->_Min)*(this->Value - this->_Min);
      this->_CursorRect.Right = (int)_Pos;
      break;
    }
  }
}

/**
 * Функция отрисовки компонента
 */
void TTrackBar::paint() {
  if (this->getVisible() && this->getParentVisible()) {
    this->fillClientRect(this->Color);
    //рисуем бордюр
    this->drawBorder(this->BorderColor);
    this->fillRect(this->_CursorColor, this->_CursorRect);
  }
}

/**
 * Функция установки цвета курсора
 * @param AValue
 */
void TTrackBar::setCursorColor(word AValue) {
  if (this->_CursorColor != AValue) {
    this->_CursorColor = AValue;
    this->paint();
  }
}

/**
 * Функци яустановки типа полоски
 * @param AValue
 */
void TTrackBar::setTypeBar(TTypeBar AValue) {
  if (this->_TypeBar != AValue) {
    this->_TypeBar = AValue;
    this->setCursorRect();
    this->paint();
  }
} 
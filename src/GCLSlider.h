/**
 * 
 * GCLSlider.h - TSlider class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLSLIDER_H
#define GCLSLIDER_H

#include <GCLTouchControl.h>

/**
 * @class
 * Класс слайдера
 */
class TSlider: public TTouchControl {
private: 
  void paint();
  bool _Checked;
  word SliderColor;
  TRect _cursorRect;
public: 
  TSlider(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
  bool isChecked() const { return this->_Checked; };
  void Check();
  void Uncheck();
  //цвета
  void setSliderColor(word AValue);
  word getSliderColor() const { return this->SliderColor; };
  //переопределяем клик
  void click();
};

#endif //GCLSLIDER_H
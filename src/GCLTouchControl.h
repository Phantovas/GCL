/**
 * 
 * GCLTouchControl.h - TTouchControl class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLTOUCHCONTROL_H
#define GCLTOUCHCONTROL_H

#include <GCLControl.h>

/**
 * @class
 * Класс компонентов реагирующих на касания
 */
class TTouchControl: public TControl {
private:
  bool _Enabled;
public:
  word ActiveBorderColor;
  TNotifyEvent onClick;
  TNotifyEvent onPress;
  TTouchControl();
  //виртуальный метод рисования
  void setActiveBorderColor(word AValue);
  word getActiveBorderColor();
  bool getActive() const { return this->Active; };
  void press();
  void click();
  //доступность контрола
  bool isEnable();
  void Enable();
  void Disable();
};

#endif //GCLTOUCHCONTROL_H
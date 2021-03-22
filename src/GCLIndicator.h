/**
 * 
 * GCLIndicator.h - TIndicator class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLINDICATOR_H
#define GCLINDICATOR_H

#include <GCLUntouchControl.h>

/**
 * @class
 * Класс блока состояния
 */
class TIndicator: public TUntouchControl {
private: 
  uint8_t _bitmapWidth, _bitmapHeight;
  void paint();
public: 
  TIndicator(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
  bool Checked;
  void check();
  void uncheck();
  void setChecked(bool AValue);
};

#endif //GCLINDICATOR_H
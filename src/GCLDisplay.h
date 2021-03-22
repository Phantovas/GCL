/**
 * 
 * GCLDisplay.h - TDisplay class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLDISPLAY_H
#define GCLDISPLAY_H

#include <GCLUntouchControl.h>

/**
 * @class
 * Класс экрана
 */
class TDisplay: public TUntouchControl {
private:
  //переопределяем назначение родителя, прячем от использования
  void setParent(TControl *AValue);
  void clear();
public: 
  TDisplay(UTFT *ptrUTFT);
  void init();
};

#endif //GCLDISPLAY_H
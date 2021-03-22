/**
 * 
 * GCLTrackBar.h - TTrackBar class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLTRACKBAR_H
#define GCLTRACKBAR_H

#include <GCLUntouchControl.h>

/**
 * @class
 * Класс трэкбара
 */
class TTrackBar: public TUntouchControl {
private:
  TRect _CursorRect;
  word _CursorColor;
  int _Min;
  int _Max;
  TTypeBar _TypeBar;
  void paint();
  void setCursorRect();
public: 
  int Value;
  int Step;
  TTrackBar(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
  void setMin(int AValue);
  int getMin() { return this->_Min; };
  void setMax(int AValue); 
  int getMax() { return this->_Max; };
  void setValue(int AValue);
  void setStep(int AValue) { this->Step = AValue; };
  void inc();
  void dec();
  void setCursorColor(word AValue);
  word getCursorColor() { return this->_CursorColor; };
  void setTypeBar(TTypeBar AValue);
};


#endif //GCLTRACKBAR_H
/**
 * 
 * GCLLabel.h - TLabel class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLLABEL_H
#define GCLLABEL_H

#include <GCLUntouchControl.h>

/**
 * @class
 * Класс текстовой метки
 */
class TLabel: public TUntouchControl {
private: 
  void paint();
public: 
  TLabel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
};

#endif //GCLLABEL_H
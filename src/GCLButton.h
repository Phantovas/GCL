/**
 * 
 * GCLButton.h - TButton class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLBUTTON_H
#define GCLBUTTON_H

#include <GCLTouchControl.h>

/**
 * @class
 * Класс кнопки
 */
class TButton: public TTouchControl {
private: 
  void paint();
public: 
  TButton(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
};


#endif //GCLBUTTON_H
/**
 * 
 * GCLUntouchControl.h - TUntouchControl class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLUNTOUCHCONTROL_H
#define GCLUNTOUCHCONTROL_H

#include <GCLControl.h>

/**
 * @class
 * Класс компонентов не реагирующих на касание
 */
class TUntouchControl: public TControl {
private:  
  void press();
  void click();
public:
  TUntouchControl();
};

#endif //GCLUNTOUCHCONTROL_H
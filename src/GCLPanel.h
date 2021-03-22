/**
 * 
 * GCLPanel.h - TPanel class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLPANEL_H
#define GCLPANEL_H

#include <GCLUntouchControl.h>

/**
 * @class
 * Класс панели
 */
class TPanel: public TUntouchControl {
public: 
  TPanel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
};

#endif //GCLPANEL_H
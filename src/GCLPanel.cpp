/**
 * 
 * GCLPanel.cpp - TPanel class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLPanel.h>

/**
 * Конструктор
 */
TPanel::TPanel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  this->BorderColor = CL_BORDERCOLOR;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
}

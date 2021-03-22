/**
 * 
 * GCLDisplay.cpp - TDisplay class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLDisplay.h>

/**
 * Конструктор
 */
TDisplay::TDisplay(UTFT *ptrUTFT) {
  //пока пустой, возможно здесь что-то напишем
  this->pUtft = ptrUTFT;
}
/**
 * Запуск на построение с экраном UTFT
 */
void TDisplay::init() {
  //получаем параметры экрана
  this->setBoundsRect(0, 0, this->pUtft->getDisplayXSize(), this->pUtft->getDisplayYSize());
  this->show();
}

/**
 * Очистка экрана
 */
void TDisplay::clear() {
  if (this->pUtft != NULL)
    this->pUtft->clrScr();
}

/**
 * 
 * GCLComponent.h - TComponent class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLCOMPONENT_H
#define GCLCOMPONENT_H

#include <GCLObject.h>

/**
 * @class
 * Класс работы с подчиненными компонентами
 */
class TComponent: protected TObject {
private:
  listItem *_Components, *_lastItem;
  uint8_t _ComponentCount;
  bool _Visible;
protected:
  void repaintChild();
  //рисуем компонент с дочками
  void painting();                                  
public:
  TComponent();
  bool addComponent(TComponent *AValue);
  bool removeComponent(TComponent *AValue);
  uint8_t getComponentCount();
  listItem* getComponents();
  //виртуальные методы
  //очистка и рисование
  virtual void clear();
  virtual void paint();
  //касание, нужно и для контролов имеющих облать, т.е, для всех наследников TComponent
  virtual TControl* activate(TPoint*);
  virtual TControl* deactivate();
  //стираем и перерисовываем компоннет
  void repaint();                                   
  //видимость
  void show();
  void hide();
  bool getVisible() { return this->_Visible; }; 
  void setVisible(bool AValue);
  bool pointInRect(TPoint *Apoint, TRect ARect);
};

#endif //GCLCOMPONENT_H
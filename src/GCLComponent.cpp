/**
 * 
 * GCLComponent.cpp - TComponent class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLComponent.h>

/**
 * Конструктор класса
 */
TComponent::TComponent() {
  this->_Components = NULL;
  this->_ComponentCount = 0;
  this->_Visible = false;
}

/**
 * Функция добавления нового компонента
 * @param AValue
 * @return bool 
 */
bool TComponent::addComponent(TComponent* AValue) {
  listItem *newItem; 
  //создаем новый элемент списка
  newItem = new listItem;
  newItem->pComponent = AValue;
  newItem->next = NULL;
  if (this->_Components == NULL) {
    //указываем начало списка и конец новому элементу
    this->_Components = this->_lastItem = newItem;
    this->_ComponentCount++;
  } else {
    //указываем последнему элементу ссылку на новый, а новый делаем последним
    this->_lastItem->next = newItem;
    this->_lastItem = newItem;
    this->_ComponentCount++;
  }
  //TODO -u Tcomponent.cpp: сделать обработку исключений, а пока всегда возвращаем истину
  return true;
}

/**
 * Функция удаления компонента из списка
 * @param AValue
 * @return bool
 */
bool TComponent::removeComponent(TComponent* AValue) {
  listItem *nowItem, *prevItem = NULL;
  //если список пуст, то удалить ничего не получится, иначе запоминаем начало списка
  if (this->_Components == NULL) {
    return 0;
  } else {
    nowItem = this->_Components;
  }
  //перебираем
  while (nowItem) {
    //нашли элемент
    if (nowItem->pComponent == AValue) {
      //если он первый, то надо сменить указатель на начало списка и освоболить память
      if (prevItem == NULL) {
        this->_Components = nowItem->next;
      } else
      //последний в списке, предыдущему обнуляем указатель на следующий и рубим память
      if (nowItem->next == NULL) {
        prevItem->next = NULL;
      } else {
      //если он в середине списка, предыдущему надо присвоить указатель на следующий, а текущий срубить
        prevItem->next = nowItem->next;
      }  
      //убиваем текущий элемент, т.к. он найден
      delete nowItem;
      this->_ComponentCount--;
      return true;
    } else {
      //переход к следующему и запоминание текущего
      prevItem = nowItem;  
      nowItem = nowItem->next; 
    }
  }
}

/**
 * Функция получения числа подчиненных компонентов
 * @return uint8_t
 */
uint8_t TComponent::getComponentCount() {
  return _ComponentCount;
}

/**
 * Функция получения указателя на список дочерних компонентов
 * @return listItem*
 */
listItem* TComponent::getComponents() {
  return this->_Components;
}

/**
 * Перерисовка подчиненных космпонентов
 */
void TComponent::repaintChild() {
  listItem *nowItem = NULL;
  //перерисовать всех дочек, если есть
  nowItem = this->getComponents();
  while (nowItem) {
    //ВАЖНО!!! Достаточно просто нарисовать детей, а не перерисовывать их, предок и так уже очищен
    nowItem->pComponent->painting();
    nowItem = nowItem->next;
  }
}

/**
 * Рисуем компонент с дочками
 */
void TComponent::painting() {
  //проверяем что компонент видим
  if (this->getVisible()) {
    this->paint();
    this->repaintChild();
  }
}

/**
 * Перерисовка компонента
 */
void TComponent::repaint() {
  if (this->getVisible()) {
    this->clear();
    //this->painting();
  }
}

/**
 * Функция установки видимости компонента
 */
void TComponent::show() {
#ifndef RELEASE 
  Serial.println("show");
#endif  
  if (!this->_Visible) {
    this->_Visible = true;
    this->painting(); //TODO  перерисовать парента вместо рисования объекта
  }
}

/**
 * Функция скрытия компонента
 */
void TComponent::hide() {
#ifndef RELEASE 
  Serial.println("hide");
#endif
  if (this->_Visible) {
    this->_Visible = false;
    this->clear();
  }
}

/**
 * Функция установки флага видимости объекта
 * @param AValue
 */
void TComponent::setVisible(bool AValue) {
  if (AValue)
    this->show();
  else 
    this->hide();
}

/**
 * Функция опеределения принадлежности точки области
 * @param ALeft
 * @param ATop
 * @param AWidth
 * @param AHeight
 */
bool TComponent::pointInRect(TPoint *APoint, TRect ARect) {
  bool result;
#ifndef RELEASE
  Serial.print("point in rect ");
#endif
  result = ((APoint->X >= ARect.Left) && 
          (APoint->X <= ARect.Right) &&
          (APoint->Y >= ARect.Top) && 
          (APoint->Y <= ARect.Bottom));
#ifndef RELEASE
  Serial.println((int)result);
#endif
  return result;
}




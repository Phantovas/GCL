/*
  Graph.cpp - Source library for build graphics to UTFT.
  Created by Vasiliy A. Ponomarjov, November 26, 2013.
  Email: vas@vingrad.ru
*/

#include "GCL.h"

#define RELEASE

//<editor-fold defaultstate="collapsed" desc="TObject">
/**
 * Конструктор класса
 */
TObject::TObject() {
  //пока пустой, но крайне необходим, а то файл пустым получается :))
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TComponent">
/**
 * Конструктор 
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
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TControl">
/**
 * Конструктор 
 */
TControl::TControl() {
  //родитель пустой
  this->Parent = NULL;
  //первоначальные значения
  this->Border = 0;
  this->Left = 0;
  this->Top = 0;
  this->_ClientOrigin.X = 0;
  this->_ClientOrigin.Y = 0;
}

/**
 * Функция установки размеров блока компонента
 * @param ALeft
 * @param ATop
 * @param AWidth
 * @param AHeight
 */ 
void TControl::setBoundsRect(unsigned int ALeft, unsigned int ATop, unsigned int AWidth, unsigned int AHeight) {
  if ((this->Left != ALeft) || (this->Top != ATop) || (this->Width != AWidth) || (this->Height != AHeight)) {
    this->Left = ALeft;
    this->Top = ATop;
    this->Width = AWidth;
    this->Height = AHeight;
    this->setClientOrigin();
  }
}

/**
 * Функция установки координат клиентской области
 */
void TControl::setClientOrigin() {
  if (this->Parent != NULL) {
    this->_ClientOrigin.X = this->Parent->_ClientOrigin.X + this->Left + this->Border;
    this->_ClientOrigin.Y = this->Parent->_ClientOrigin.Y + this->Top + this->Border; 
  } else {
    this->_ClientOrigin.X = this->Left + this->Border;
    this->_ClientOrigin.Y = this->Top + this->Border;
  }
}

/**
 * Заглушка для виртуального метода (пока еще не знаю, почему Arfuino1.5.8 его требует)
 */
void TControl::press() {
  return;
};

/**
 * Заглушка для виртуального метода (пока еще не знаю, почему Arfuino1.5.8 его требует)
 */
void TControl::click() {
  return;
};

/**
 * Очищаем компонент
 */
void TControl::clear() {
  if (this->Parent != NULL) {
    this->Parent->painting(); //рисуем дочек парента, вместо перерисовки
  }  
}

/**
 * Функция рисования коспонента
 */
void TControl::paint() {
  if (this->getVisible() && this->getParentVisible()) {
    //заливаем блок
    this->fillClientRect(this->Color);
    //рисуем бордюр
    this->drawBorder(this->BorderColor);
  }  
}

/**
 * Функция заливки обалсти
 * @param AColor
 * @param ARect 
 */
void TControl::fillRect(word AColor, TRect ARect) {
  //запоминаем текущий цвет
  word nowColor;
  //если регион имеет не нулевой размер, то тогда рисуем
  if ((ARect.Right - ARect.Left > 0) && (ARect.Bottom - ARect.Top > 0)) {
    nowColor = this->pUtft->getColor();
    this->pUtft->setColor(AColor);
    this->pUtft->fillRect(this->getClientOrigin().X + ARect.Left, 
                        this->getClientOrigin().Y + ARect.Top, 
                        this->getClientOrigin().X + ARect.Right - 1, 
                        this->getClientOrigin().Y + ARect.Bottom - 1);  
    this->paintDelay();
    //восстанавливаем цвет
    this->pUtft->setColor(nowColor);
  }
}  

/**
 * Функция заливки обалсти
 * @param AColor
 * @param ARect 
 */
void TControl::fillRoundRect(word AColor, TRect ARect) {
  //запоминаем текущий цвет
  word nowColor;
  //если регион имеет не нулевой размер, то тогда рисуем
  if ((ARect.Right - ARect.Left > 0) && (ARect.Bottom - ARect.Top > 0)) {
    nowColor = this->pUtft->getColor();
    this->pUtft->setColor(AColor);
    this->pUtft->fillRoundRect(this->getClientOrigin().X + ARect.Left, 
                        this->getClientOrigin().Y + ARect.Top, 
                        this->getClientOrigin().X + ARect.Right - 1, 
                        this->getClientOrigin().Y + ARect.Bottom - 1);  
    this->paintDelay();
    //восстанавливаем цвет
    this->pUtft->setColor(nowColor);
  }
}

/**
 * Функция заливки всей области объекта
 * @param AColor
 */
void TControl::fillClientRect(word AColor) {
  this->fillRect(AColor, this->getClientRect());
}

/**
 * Функция отрисовки бордюра
 * @param AColor
 */
void TControl::drawBorder(word AColor) {
  //запоминаем текущий цвет
  word nowColor;
  //если размер компонента не нулевой
  if ((this->Width >0) && (this->Height > 0)) {
    nowColor = this->pUtft->getColor();
    this->pUtft->setColor(AColor);
    for (int i = 0; i < this->Border; i++) {
      this->pUtft->drawRect(this->getBoundsRect().Left + i, this->getBoundsRect().Top + i, this->getBoundsRect().Right - i - 1, this->getBoundsRect().Bottom - i - 1);
      this->paintDelay();
    }   
    //восстанавливаем цвет
    this->pUtft->setColor(nowColor);
  }
}

/**
 * Переопределенная функция отрисовки бордюра для заданной области
 * @param AColor
 * @param ARect
 */
void TControl::drawBorderRect(word AColor, TRect ARect) {
  //запоминаем текущий цвет
  word nowColor;
  //если размер компонента не нулевой
  if ((this->Width >0) && (this->Height > 0)) {
    nowColor = this->pUtft->getColor();
    this->pUtft->setColor(AColor);
    for (int i = 0; i < this->Border; i++) {
      this->pUtft->drawRect(ARect.Left + i, ARect.Top + i, ARect.Right - i - 1, ARect.Bottom - i - 1);
      this->paintDelay();
    }   
    //восстанавливаем цвет
    this->pUtft->setColor(nowColor);
  }
}

/**
 * Фунция рисования картинки
 * @param x
 * @param y
 * @param sx
 * @param sy
 * @param data
 * @param scale
 */
void TControl::drawBitmap(int ABitmapWidth, int ABitmapHeight, bitmapdatatype AData, int AScale=1) {
  TPoint Coord; TRect _aRect; 
  //если размер компонента не нулевой
  if ((this->Width >0) && (this->Height > 0)) {
    _aRect = this->getClientRect();
    Coord.X = this->getClientOrigin().X + ((_aRect.Left + _aRect.Right) - ABitmapWidth)/2;
    Coord.Y = this->getClientOrigin().Y + ((_aRect.Top + _aRect.Bottom) - ABitmapHeight)/2;
    this->pUtft->drawBitmap(Coord.X, Coord.Y, ABitmapWidth, ABitmapHeight, AData, AScale);
  }
}

/**
 * Функция рисования текстовой строки из заданной координаты
 * @param AStart
 * @param AStr
 */
void TControl::textOut(const char *AStr, word AColor, TRect ARect, uint8_t AType = DT_LEFT) {
  word oldColor, oldBackColor;
  TPoint Coord; uint8_t *oldFont;
  oldColor = this->pUtft->getColor();
  oldBackColor = this->pUtft->getBackColor();
  oldFont = this->pUtft->getFont();
  //устанвливаем новые
  this->pUtft->setColor(AColor);
  this->pUtft->setBackColor(this->Color);
  this->pUtft->setFont(this->getFont());
  switch (AType) {
    case DT_CENTER: {
      Coord.X = this->getClientOrigin().X + ((ARect.Left + ARect.Right) - this->pUtft->getFontXsize()*strlen(AStr))/2;
      Coord.Y = this->getClientOrigin().Y + ((ARect.Top + ARect.Bottom) - this->pUtft->getFontYsize())/2;
      break;
    }
    case DT_RIGHT: {
      Coord.X = this->getClientOrigin().X + (ARect.Left + ARect.Right) - this->pUtft->getFontXsize()*strlen(AStr);
      Coord.Y = this->getClientOrigin().Y + ((ARect.Top + ARect.Bottom) - this->pUtft->getFontYsize())/2;
      break;
    }
    default: {
      Coord.X = this->getClientOrigin().X;
      Coord.Y = this->getClientOrigin().Y + ((ARect.Top + ARect.Bottom) - this->pUtft->getFontYsize())/2;
    }
  }
#ifndef RELEASE 
  Serial.println("TextOut");
  Serial.println(Coord.X);
  Serial.println(Coord.Y);
#endif
  this->pUtft->print(AStr, Coord.X, Coord.Y);
  //восстанавливаем
  this->pUtft->setColor(oldColor);
  this->pUtft->setBackColor(oldBackColor);
  this->pUtft->setFont(oldFont);
}

/**
 * Функция установки родителя
 * @param AValue
 */
void TControl::setParent(TControl *AValue) { 
  if (this->Parent != AValue) {
    //стереть у старого родителя дочку и перерисовываем
    if (this->Parent != NULL) {
      this->Parent->removeComponent(this);
      if (this->Parent->getVisible())
        this->Parent->repaint();
    }
    this->Parent = AValue;
    if (this->Parent != NULL) {
      //назначаем нового родителя
      this->Parent->addComponent(this);
      this->pUtft = this->Parent->pUtft; 
    } 
    this->setClientOrigin();
    //рисуем только если видимый и видимый родитель
    if (this->getVisible() && this->getParentVisible())
      this->paint();
  }
}

/**
 * Функция получения видимости родителей
 * @return 
 */
bool TControl::getParentVisible() {
  TControl *nowParent = NULL;
  bool result = true;
  nowParent = this->Parent;
  while (nowParent) {
    result = result && nowParent->getVisible();
    nowParent = nowParent->Parent;
  }
  return result;
}

/**
 * Функция вовзрата абсолютных координат рамки
 * @return 
 */
TRect TControl::getBoundsRect() {
  TRect result;
  if (this->Parent != NULL) {
    result.Left = this->Parent->_ClientOrigin.X + this->Left;
    result.Top = this->Parent->_ClientOrigin.Y + this->Top;
    result.Right = result.Left + this->Width;
    result.Bottom = result.Top + this->Height;
  } else {
    result.Left = this->Left;
    result.Top = this->Top;
    result.Right = this->Left + this->Width;
    result.Bottom = this->Top + this->Height;
  }
  return result;
}

/**
 * Функция установки клиентской области компонента
 */
TRect TControl::getClientRect() {
  TRect result;
  result.Left = 0;
  result.Top = 0;
  result.Right = this->Width - this->Border*2;
  result.Bottom = this->Height - this->Border*2;
  return result;
}

/**
 * Получение координат компонента
 * @return 
 */
TPoint TControl::getClientOrigin() {
  TPoint result;
  result.X = this->_ClientOrigin.X;
  result.Y = this->_ClientOrigin.Y;
  return result;
}

/**
 * Функция установки левой координаты
 * @param AValue
 */
void TControl::setLeft(unsigned int AValue) {
  this->setBoundsRect(AValue, this->Top, this->Width, this->Height);
  if ((this->Parent != NULL) && this->getVisible())
    this->repaint();
}

/**
 * Функция установки верхней координаты
 * @param AValue
 */
void TControl::setTop(unsigned int AValue) {
  this->setBoundsRect(this->Left, AValue, this->Width, this->Height);
  if ((this->Parent != NULL) && this->getVisible())
    this->repaint();
}

/**
 * Функция получения ширины клиентской области
 * @return unsigned int
 */
unsigned int TControl::getClientWidth() {
  return this->getClientRect().Right;
}

/**
 * Функция получения высоты клиентской области
 * @return unsigned int
 */
unsigned int TControl::getClientHeight() {
 return this->getClientRect().Bottom;
}

/**
 * Функция изменения ширины компонента
 * @param AValue
 */
void TControl::setWidth(unsigned int AValue) {
  this->setBoundsRect(this->Left, this->Top, AValue, this->Height);
  if ((this->Parent != NULL) && this->getVisible())
    this->repaint();
}

/**
 * Функция изменения высоты компонента
 * @param AValue
 */
void TControl::setHeight(unsigned int AValue) {
  this->setBoundsRect(this->Left, this->Top, this->Width, AValue);
  if ((this->Parent != NULL) && this->getVisible())
    this->repaint();
}

/**
 * Функция установки ширины бордюра компонента
 * @param ABorder
 */
void TControl::setBorder(unsigned int ABorder) {
  this->Border = ABorder;
  this->setClientOrigin();
  this->paint();
}

/**
 * Функция установки цвета компонента
 * @param AValue
 */
void TControl::setColor(word AValue) {
  this->Color = AValue;
  this->paint();
}

/**
 * Функция установки цвета бордюра
 * @param AValue
 */
void TControl::setBorderColor(word AValue) {
  this->BorderColor = AValue;
  this->paint();
}

/**
 * Функция передачи нажатия потомкам
 * @param APoint
 * @return 
 */
TControl* TControl::activate(TPoint *APoint) {
  listItem *nowItem = NULL;
  TControl *treat = NULL;
#ifndef RELEASE
  Serial.println("Control activate");
#endif
  if (this->pointInRect(APoint, this->getBoundsRect())) {
    nowItem = this->getComponents();
    while (nowItem) {
      //если нашли внутри потомка с нужными координатами, 
      //то пусть они там сами разбираются что делать, а мы выходим из цикла
      if (nowItem->pComponent->getVisible()) {
        treat = nowItem->pComponent->activate(APoint);
        if (treat)
          break;
      }
      nowItem = nowItem->next;
    }
    if (!treat) {
      this->press();
      //нашли чуток притормозим
      delay(ACTIVATE_DELAY);
      this->Active = true;
      treat = this;
    }
  } 
  //возвращаем результат работы функции  
  return treat;
}

/**
 * Функция деактивации контрола
 * @return 
 */
TControl* TControl::deactivate() {
  listItem *nowItem = NULL;
  TControl *treat = NULL;
#ifndef RELEASE
  Serial.println("Control deactivate");
#endif
  nowItem = this->getComponents();
  //если этот компонент активен, то выполняем клик и вываливаемся в основной цикл
  //и возвращаем результат true
  if (this->Active) {
    this->Active = false;
    delay(ACTIVATE_DELAY);
    this->click();
    treat = this;
  } else {
    while (nowItem) {
      //если нашли внутри активного потомка
      //то пусть они там сами разбираются что делать, а мы выходим из цикла
      if (nowItem->pComponent->getVisible()) { 
        treat = nowItem->pComponent->deactivate();
        if (treat)
          break;
      }
      nowItem = nowItem->next;
    }
  }
  //возвращаем результат работы функции  
  return treat;
}

/**
 * Функция деактивации контрола по ссылке
 * @return 
 */
TControl* TControl::deactivate(TControl* AControl) {
  //если нашли и очистели, то возвращаем NULL, иначе обратно контрол
  if (AControl) {
#ifndef RELEASE    
    Serial.println("Control active deactivate");
#endif
    AControl->Active = false;
    delay(ACTIVATE_DELAY);
    AControl->click();
    return NULL;
  } else {
    return AControl;
  }
}

/**
 * Функция установки заголовка
 * @param AValue
 */
void TControl::setCaption(const char *AValue) {
  this->Caption = AValue;
  this->painting();
}

/**
 * Функция установки положения текста заголовка
 * @param AValue
 */
void TControl::setAlignCaption(uint8_t AValue) {
  if (this->AlignCaption != AValue) {
    this->AlignCaption = AValue;
    this->painting();
  }
}

/**
 * Функция установки цвета шрифта
 * @param AValue
 */
void TControl::setFontColor(word AValue) {
  if (this->FontColor != AValue) {
    this->FontColor = AValue;
    this->painting();
  }
}

/**
 * Функция установки шрифта
 * @param _font
 */
void TControl::setFont(uint8_t* AValue) {
  if (this->_font != AValue) {
    this->_font = AValue;
    this->painting();
  }
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TPassiveControl">
/**
 * Конструктор
 */
TPassiveControl::TPassiveControl() {
  //шрифт
  this->setFont(arial_bold_rus);
  this->AlignCaption = DT_LEFT;
  this->FontColor = CL_FONTCOLOR;
  //цвета
  this->Color = CL_NONE;
  this->BorderColor = CL_NONE;
}

/**
 * Заглушка нажатия 
 */
void TPassiveControl::press() {
#ifndef RELEASE  
  Serial.println("TPassiveControl press");
#endif
}

/**
 * Заглушка отпускания
 */
void TPassiveControl::click() {
#ifndef RELEASE  
  Serial.println("TPassiveControl click");
#endif
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TDisplay">
/**
 * Конструктор основной
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
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TPanel">
/**
 * Конструктор с библиотекой UTFT
 */
TPanel::TPanel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  this->BorderColor = CL_BORDERCOLOR;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TLabel">
/**
 * Конструктор с библиотекой UTFT
 */
TLabel::TLabel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //задаем значеняи
  this->Color = CL_NONE;
  //шрифт
  this->setFont(arial_bold_rus);
  this->AlignCaption = DT_LEFT;
  this->FontColor = CL_FONTCOLOR;
  //события
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
}

/**
 * Рисуем метку
 */
void TLabel::paint() {
#ifndef RELEASE  
  Serial.println("paint label");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw label");
#endif
    //заливаем блок
    this->fillClientRect(this->Color);
    if (this->Caption) {
      this->textOut(this->getCaption(), this->getFontColor(), this->getClientRect(), this->AlignCaption);
    }  
  }
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TIndicator">
/**
 * Конструктор с библиотекой UTFT
 */
TIndicator::TIndicator(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //задаем значеняи
  this->_bitmapWidth = 22;
  this->_bitmapHeight = 22;
  this->Color = CL_NONE;
  //события
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
  //состояние
  this->Checked = false;
}

/**
 * Рисуем метку
 */
void TIndicator::paint() {
#ifndef RELEASE  
  Serial.println("paint indicator");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw indicator");
#endif
    //заливаем блок
    this->fillClientRect(this->Color);  
    if (this->Checked) {
      this->drawBitmap(this->_bitmapWidth, this->_bitmapHeight, icon_check);
    } else {
      this->drawBitmap(this->_bitmapWidth, this->_bitmapHeight, icon_uncheck);
    }
  }
}

/**
 * Установка включенного состояния
 */
void TIndicator::check() {
  if (!this->Checked) {
    this->Checked = true;
    this->paint();
  }
}

/**
 * Функция выключенного состояния
 */
void TIndicator::uncheck() {
  if (this->Checked) {
    this->Checked = false;
    this->paint();
  }
}

/**
 * Функция установки нужного состояни
 * @param AValue
 */
void TIndicator::setChecked(bool AValue) {
  if (this->Checked != AValue) {
    if (AValue) 
      this->check();
    else
      this->uncheck();
  }
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TTrackBar">
/**
 * Конструктор с библиотекой UTFT
 */
TTrackBar::TTrackBar(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  this->BorderColor = CL_BORDERCOLOR;
  this->Border = 1;
  this->_CursorColor = CL_PROGRESSCOLOR;
  //перовоначальные значения
  this->_Min = 0;
  this->_Max = 100;
  this->Step = 1;
  this->Value = 0;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
  //установка размеров указателя
  this->_TypeBar = TB_CURSOR;
  this->setCursorRect();
}

/**
 * Функция установки минимального значения 
 * @param AValue
 */
void TTrackBar::setMin(int AValue) {
  if (this->_Min != AValue) {
    this->_Min = AValue;
    this->setCursorRect();
    this->paint();
  }
}

/**
 * Функция установки максимального значения 
 * @param AValue
 */
void TTrackBar::setMax(int AValue) {
  if (this->_Max != AValue) {
    this->_Max = AValue;
    this->setCursorRect();
    this->paint();
  }
}


/**
 * Функция установки текущего значения 
 * @param AValue
 */
void TTrackBar::setValue(int AValue) {
  AValue = constrain(AValue, this->_Min, this->_Max);
  if (this->Value != AValue) {
    this->Value = AValue;
    this->setCursorRect();
    this->paint();
  }
}

/**
  * Функция увеличения значения
 */
void TTrackBar::inc() {
  this->setValue(this->Value + this->Step);
}

/**
 * Функция уменьшения значения
 */
void TTrackBar::dec() {
  this->setValue(this->Value - this->Step);
}

/**
 * Функция расчета размеров курсора
 */
void TTrackBar::setCursorRect() {
  float _Pos;
  this->_CursorRect.Top = 0;
  this->_CursorRect.Bottom = this->getClientHeight();
  //пересчитываем размер указателя
  switch (this->_TypeBar) {
    case TB_CURSOR: {
      //если шире, чем пол высоты
      if (this->getClientWidth() > this->getClientHeight()/2) {
        /*
         * (this->getClientWidth()  - this->getClientHeight()/2)/(this->_Max - this->_Min) количество пикселей на одно значение - сдвиг на ширину курсора this->getClientHeight()/2
         * (this->Value - this->_Min) сдвиг относительно нулевого угла (пример -50..50, 0 - это сдвиг на 50 значений)
         */
        _Pos = (float)(this->getClientWidth() - this->getClientHeight()/2)/(this->_Max - this->_Min)*(this->Value - this->_Min);
        this->_CursorRect.Left = (int)_Pos;
        this->_CursorRect.Right = this->_CursorRect.Left + this->getClientHeight()/2;
        
      } else {
        //иначе
        this->_CursorRect.Left = 0;
        this->_CursorRect.Right = this->getClientWidth();
      }
      break;
    }
    case TB_PROGRESS: {
      /*
       * this->getClientWidth()/(this->_Max - this->_Min) количество пикселей на одно значение 
       * (this->Value - this->_Min) сдвиг относительно нулевого угла (пример -50..50, 0 - это сдвиг на 50 значений)
       */
      this->_CursorRect.Left = 0;
      _Pos = (float)this->getClientWidth()/(this->_Max - this->_Min)*(this->Value - this->_Min);
      this->_CursorRect.Right = (int)_Pos;
      break;
    }
  }
}

/**
 * Функция отрисовки компонента
 */
void TTrackBar::paint() {
  if (this->getVisible() && this->getParentVisible()) {
    this->fillClientRect(this->Color);
    //рисуем бордюр
    this->drawBorder(this->BorderColor);
    this->fillRect(this->_CursorColor, this->_CursorRect);
  }
}

/**
 * Функция установки цвета курсора
 * @param AValue
 */
void TTrackBar::setCursorColor(word AValue) {
  if (this->_CursorColor != AValue) {
    this->_CursorColor = AValue;
    this->paint();
  }
}

/**
 * Функци яустановки типа полоски
 * @param AValue
 */
void TTrackBar::setTypeBar(TTypeBar AValue) {
  if (this->_TypeBar != AValue) {
    this->_TypeBar = AValue;
    this->setCursorRect();
    this->paint();
  }
} 

//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TActiveControl">
/**
 * Конструктор 
 */  
TActiveControl::TActiveControl() {
  //шрифт
  this->setFont(arial_bold_rus);
  this->AlignCaption = DT_CENTER;
  this->FontColor = CL_FONTCOLOR;
  //задаем значеняи
  this->Color = CL_BTNCOLOR;
  this->Border = 1;
  this->BorderColor = CL_BORDERCOLOR;
  this->ActiveBorderColor = CL_ACTIVEBORDERCOLOR;
  this->_Enabled = true;      //чаще будут активные, чем неактивные
}  
  
/**
 * Функция установки цвета активного бордюра
 * @param AValue
 */
void TActiveControl::setActiveBorderColor(word AValue) {
  if (this->Active && (this->ActiveBorderColor != AValue)) {
    this->ActiveBorderColor = AValue;
    this->drawBorder(this->ActiveBorderColor);
  }
}

/**
 * Возврат цвета активного бордюра
 */
word TActiveControl::getActiveBorderColor() {
  return this->ActiveBorderColor;
}  

/**
 * Функция обработки нажатия
 */
void TActiveControl::press() {
  if (this->isEnable()) {
#ifndef RELEASE 
    Serial.println("ActiveControl press ");
#endif
    if (!this->Active)
      this->drawBorder(this->ActiveBorderColor);
    if (this->onPress)
      this->onPress();  
  }
}

/**
 * Функция обработки отпускания
 */
void TActiveControl::click() {
  if (this->isEnable()) {
#ifndef RELEASE    
    Serial.println("ActiveControl click");
#endif
    if (!this->Active)
      this->drawBorder(this->BorderColor);
    if (this->onClick)
      this->onClick();  
  }
}

/**
 * Функция получения состояния кнопки
 * @return 
 */
bool TActiveControl::isEnable() {
  return this->_Enabled;
}

/**
 * Функция активирования кнопки
 */
void TActiveControl::Enable() {
  if (!this->_Enabled) { 
    this->_Enabled = true;
    this->painting();
  }
}

/**
 * Функция деактивации кнопки
 */
void TActiveControl::Disable() {
  if (this->_Enabled) {
    this->_Enabled = false;
    this->painting();
  }
}



//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TButton">
/**
 * Конструктор с библиотекой UTFT
 */
TButton::TButton(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //события
  this->onClick = NULL;
  this->onPress = NULL;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
}

/**
 * Рисуем панель
 */
void TButton::paint() {
#ifndef RELEASE  
  Serial.println("paint button");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw button");
#endif
    //заливаем блок
    this->fillClientRect(this->Color);
    //рисуем бордюр
    if (this->isEnable() && this->getActive()) {
      this->drawBorder(this->ActiveBorderColor);
    } else {
      this->drawBorder(this->BorderColor);
    }
    if (this->Caption) {
      if (this->isEnable())
        this->textOut(this->getCaption(), this->getFontColor(), this->getClientRect(), this->AlignCaption);
      else
        this->textOut(this->getCaption(), CL_DISABLEFONTCOLOR, this->getClientRect(), this->AlignCaption);
    }  
  }
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="TSlider">
/**
 * Конструктор слайдера
 */
TSlider::TSlider(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight) {
  //установки
  this->_Checked = false;
  this->AlignCaption = DT_CENTER;
  this->BorderColor = CL_BLACK;
  //события
  this->onClick = NULL;
  this->onPress = NULL;
  this->setBoundsRect(ALeft, ATop, AWidth, AHeight);
  this->setParent(ptrParent);
  this->setFont(SmallFont);
}  

/**
 * Рисуем слайдер
 */
void TSlider::paint() {
  TRect sliderRect, fillRect;
  word printColor, oldColor;
  uint8_t mPixel = 3; 
#ifndef RELEASE  
  Serial.println("paint slider");
#endif
  if (this->getVisible() && this->getParentVisible()) {
#ifndef RELEASE    
    Serial.println("draw slider");
#endif
    //области
    sliderRect = this->getClientRect();
    fillRect = this->getClientRect();;
    //цвета
    oldColor = this->Color;
    if (this->isEnable())
      printColor = this->FontColor;
    else
      printColor = CL_DISABLEFONTCOLOR;
    //заливаем фоном родителя или черным
    if (this->Parent != NULL)
      this->fillRect(this->Parent->Color, fillRect);      
    else
      this->fillRect(this->BorderColor, fillRect);      
    //уменьшаем регион по высоте
    fillRect.Top = fillRect.Top + mPixel;
    fillRect.Bottom = fillRect.Bottom - mPixel;
    if (this->isChecked()) {
      //считаем размер скользящего блока
      sliderRect.Left = sliderRect.Left + 2*this->getClientWidth()/3;   //сдвигаем на 2/3
      //рисуем
      this->fillRect(CL_LIME, fillRect);      
      this->fillRect(this->Color, sliderRect);
      //считаем размер региона для вывода надписи посередине
      fillRect.Right =  fillRect.Left + 2*this->getClientWidth()/3;
      this->Color = CL_LIME;
      this->textOut("ON", printColor, fillRect, this->AlignCaption);  //ON - BJK (ВКЛ)
    } else {
      //считаем размер скользящего блока
      sliderRect.Right =  sliderRect.Left + this->getClientWidth()/3; //всего 1/3 от длины слайдера
      //рисуем
      this->fillRect(CL_RED, fillRect); 
      this->fillRect(this->Color, sliderRect);
      //считаем размер региона для вывода надписи посередине
      fillRect.Left = fillRect.Left + this->getClientWidth()/3;
      this->Color = CL_RED;
      this->textOut("OFF", printColor, fillRect, this->AlignCaption);  //OFF - B[JK (ВЫКЛ)
    }
    this->Color = oldColor;
    //рисуем бордюр
    if (this->isEnable() && this->getActive()) {
      //this->drawBorderRect(this->ActiveBorderColor, sliderRect);
    } else {
      //this->drawBorderRect(this->BorderColor, sliderRect);
    }
  }
}

/**
 * Функция изменения на включено
 */
void TSlider::Check() {
  if (!this->_Checked) {
    this->_Checked = true;
    this->painting();
  }
}

/**
 * Функция изменения состояния на отключено
 */
void TSlider::Uncheck() {
  if (this->_Checked) {
    this->_Checked = false;
    this->painting();
  }
}


/**
 * Установка цвета движущегося блока
 * @param AValue
 */
void TSlider::setSliderColor(word AValue) {
  if (this->SliderColor != AValue) {
    this->SliderColor = AValue;
    this->painting();
  }
}

/**
 * Переопределенный метод реакции на отпускание
 */
void TSlider::click() {
  if (this->isEnable()) {
    //изменяем состояние и вызываем клик парента
    if (this->isChecked()) 
      this->Uncheck();
    else
      this->Check();
  }
  TActiveControl::click();
}
//</editor-fold>


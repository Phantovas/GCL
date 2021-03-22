/**
 * 
 * GCLControl.cpp - TControl class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#include <GCLControl.h>

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
void TControl::drawBitmap(int ABitmapWidth, int ABitmapHeight, bitmapdatatype AData, int AScale = 1) {
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




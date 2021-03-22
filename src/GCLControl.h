/**
 * 
 * GCLControl.h - TControl class for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

#ifndef GCLCONTROL_H
#define GCLCONTROL_H

#include <UTFT.h>

#include <GCLComponent.h>

/**
 * @class
 * Класс визуальных компонентов
 */
class TControl: public TComponent {
private:
  TPoint _ClientOrigin;                                        //координата абсолютная от левого угла экрана (0,0)
  uint8_t *_font;
protected:
  TControl *Parent;  
  bool Active;
  void setBoundsRect(unsigned int ALeft, unsigned int ATop, unsigned int AWidth, unsigned int AHeight);
  void setClientOrigin();
  void setParent(TControl *AValue);
  void textOut(const char *AStr, word AColor, TRect ARect, uint8_t AType);
public:
  UTFT *pUtft;
  unsigned int Border;                                          //толщина бордюра  
  int Left, Top;                                               //лево, право относительно родителя
  unsigned int Width, Height;                                   //ширина высота
  word FontColor, Color, BorderColor;
  const char *Caption;
  uint8_t AlignCaption;
  //виртуальные события
  virtual void press();
  virtual void click();
  TControl();
  //отрисовка
  void paintDelay() { delay(PAINT_DELAY); };
  void clear();
  void paint();
  void fillRect(word AColor, TRect ARect);
  void fillRoundRect(word AColor, TRect ARect);
  void fillClientRect(word AColor);
  void drawBorder(word AColor);
  void drawBorderRect(word AColor, TRect ARect);
  void drawBitmap(int ABitmapWidth, int ABitmapHeight, bitmapdatatype AData, int AScale = 1);
  //родитель
  TControl* getParent() { return this->Parent; };
  bool getParentVisible();
  //размеры
  TRect getBoundsRect();
  TRect getClientRect();                                         //возвращает размер клиентской области - бордюр
  TPoint getClientOrigin();                                     //возвращает координаты левого угла абсолютные
  void setLeft(unsigned int AValue);
  int getLeft() { return this->Left; };
  void setTop(unsigned int AValue);
  int getTop() { return this->Top; };
  unsigned int getClientWidth();
  unsigned int getClientHeight();
  void setWidth(unsigned int AValue);
  void setHeight(unsigned int AValue);
  void setBorder(unsigned int AValue);
  //цвета
  void setColor(word AColor);
  void setBorderColor(word ABorderColor);
  //касание
  TControl* activate(TPoint *APoint);
  TControl* deactivate();
  TControl* deactivate(TControl *AControl);
  //заголовок
  void setCaption(const char *AValue);
  const char* getCaption() { return this->Caption; };
  void setAlignCaption(uint8_t AValue);
  uint8_t getAlignCaption() { return this->AlignCaption; };
  //фонт заголовка
  word getFontColor() { return this->FontColor; };
  void setFontColor(word AValue);
  uint8_t* getFont() { return this->_font; };
  void setFont(uint8_t* AValue);
};

#endif //GCLCONTROL_H
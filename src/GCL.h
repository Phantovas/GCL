/*
  Graph.h - Library for build graphics to UTFT.
  Created by Vasiliy A. Ponomarjov, November 26, 2013.
  Email: vas@vingrad.ru
*/

#ifndef GCL_h
#define GCL_h

//************************************************
//Constants
//************************************************
#define PAINT_DELAY 0        //задержка при прорисовке
#define ACTIVATE_DELAY 100   //задержка на активацию
  
//************************************************
// COLORS
//************************************************
#define CL_BLACK              VGA_BLACK		
#define CL_WHITE              VGA_WHITE		
#define CL_RED                VGA_RED			
#define CL_GREEN              VGA_GREEN		
#define CL_BLUE               VGA_BLUE		
#define CL_SILVER             VGA_SILVER	
#define CL_GRAY               VGA_GRAY		
#define CL_MAROON             VGA_MAROON	
#define CL_YELLOW             VGA_YELLOW	
#define CL_OLIVE              VGA_OLIVE		
#define CL_LIME               VGA_LIME		
#define CL_AQUA               VGA_AQUA		
#define CL_TEAL               VGA_TEAL		
#define CL_NAVY               VGA_NAVY		
#define CL_FUCHSIA            VGA_FUCHSIA	
#define CL_PURPLE             VGA_PURPLE	
#define CL_TRANSPARENT        VGA_TRANSPARENT
//************************************************
#define CL_NONE                 CL_BLACK
#define CL_BTNCOLOR             CL_BLUE
#define CL_BORDERCOLOR          CL_GREEN//CL_NAVY
#define CL_ACTIVEBORDERCOLOR    CL_YELLOW
#define CL_FONTCOLOR            CL_WHITE
#define CL_DISABLEFONTCOLOR     CL_BLACK
#define CL_PROGRESSCOLOR        CL_BLUE

//************************************************
// PLACEMENT
//************************************************
#define DT_LEFT                 0x00
#define DT_CENTER               0x01
#define DT_RIGHT                0x10

#include "Arduino.h"

#include <UTFT.h>

//************************************************
// Declare which fonts we will be using
//************************************************
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
//extern uint8_t Inconsola[];
extern uint8_t hallfetica_rus[];
extern uint8_t arial_bold_rus[];
extern uint8_t GlcSymbol[];
extern uint8_t DotMatrix_M_rus[];
extern uint16_t icon_check[];
extern uint16_t icon_uncheck[];

//************************************************
//Forward reference
//************************************************
class TObject;
class TComponent;
class TControl;

//************************************************
//Structurs
//************************************************
typedef struct TPoint {
  unsigned int X, Y;
};

typedef struct TRect {
  unsigned int Left, Top, Right, Bottom;
};

typedef struct listItem {
  TComponent *pComponent;
  listItem *next;
};

typedef enum TTypeBar { TB_CURSOR, TB_PROGRESS };

typedef void (*TNotifyEvent)();


/**
 * Главный класс компонентов
 */
class TObject {
public:
  TObject();
};

/**
 * Класс работы с подчиненными компонентами
 */
class TComponent: protected TObject {
private:
  listItem *_Components, *_lastItem;
  uint8_t _ComponentCount;
  bool _Visible;
protected:
  void repaintChild();
  void painting();                                  //рисуем компонент с дочками
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

/**
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
  void drawBitmap(int ABitmapWidth, int ABitmapHeight, bitmapdatatype AData, int AScale);
  //родитель
  TControl* getParent() { return this->Parent; };
  bool getParentVisible();
  //размеры
  TRect getBoundsRect();
  TRect getClientRect();                                         //возвращает размер клиентской области - бордюр
  TPoint getClientOrigin();    
  //возвращает координаты левого угла абсолютныей
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

/**
 * Класс пассивных компонентов
 */
class TPassiveControl: public TControl {
private:  
  void press();
  void click();
public:
  TPassiveControl();
};

/**
 * Класс экрана
 */
class TDisplay: public TPassiveControl {
private:
  //переопределяем назначение родителя, прячем от использования
  void setParent(TControl *AValue);
  void clear();
public: 
  TDisplay(UTFT *ptrUTFT);
  void init();
};

/**
 * Класс панели
 */
class TPanel: public TPassiveControl {
public: 
  TPanel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
};

/**
 * Класс лейбла
 */
class TLabel: public TPassiveControl {
private: 
  void paint();
public: 
  TLabel(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
};

/**
 * Класс блока состояния
 */
class TIndicator: public TPassiveControl {
private: 
  uint8_t _bitmapWidth, _bitmapHeight;
  void paint();
public: 
  TIndicator(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
  bool Checked;
  void check();
  void uncheck();
  void setChecked(bool AValue);
};

/**
 * Класс трэкбара
 */
class TTrackBar: public TPassiveControl {
private:
  TRect _CursorRect;
  word _CursorColor;
  int _Min;
  int _Max;
  TTypeBar _TypeBar;
  void paint();
  void setCursorRect();
public: 
  int Value;
  int Step;
  TTrackBar(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
  void setMin(int AValue);
  int getMin() { return this->_Min; };
  void setMax(int AValue); 
  int getMax() { return this->_Max; };
  void setValue(int AValue);
  void setStep(int AValue) { this->Step = AValue; };
  void inc();
  void dec();
  void setCursorColor(word AValue);
  word getCursorColor() { return this->_CursorColor; };
  void setTypeBar(TTypeBar AValue);
};



/**
 * Класс для активных компонентов
 */
class TActiveControl: public TControl {
private:
  bool _Enabled;
public:
  word ActiveBorderColor;
  TNotifyEvent onClick;
  TNotifyEvent onPress;
  TActiveControl();
  //виртуальный метод рисования
  void setActiveBorderColor(word AValue);
  word getActiveBorderColor();
  bool getActive() const { return this->Active; };
  void press();
  void click();
  //доступность контрола
  bool isEnable();
  void Enable();
  void Disable();
};

/**
 * Класс кнопки
 */
class TButton: public TActiveControl {
private: 
  void paint();
public: 
  TButton(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
};

/**
 * Класс слайдера
 */
class TSlider: public TActiveControl {
private: 
  void paint();
  bool _Checked;
  word SliderColor;
  TRect _cursorRect;
public: 
  TSlider(TControl *ptrParent, int ALeft, int ATop, int AWidth, int AHeight);
  bool isChecked() const { return this->_Checked; };
  void Check();
  void Uncheck();
  //цвета
  void setSliderColor(word AValue);
  word getSliderColor() const { return this->SliderColor; };
  //переопределяем клик
  void click();
};

#endif //GCL_h

#include <UTouch.h>
#include <GCL.h>

UTFT    GLCD(ITDB32S, 38, 39, 40, 41);   // Remember to change the model parameter to suit your display module!
UTouch  Touch(6, 5, 4, 3, 2);

TDisplay Display(&GLCD);
TPanel MainPanel(&Display, 0, 0, 320, 240);
TButton Button(&MainPanel, 100, 200, 120, 40);
TPanel LabelPanel(&MainPanel, 0, 0, 320, 200);
TLabel Label(&LabelPanel, 0, 50, 320, 40);

void ButtonClick() {
  LabelPanel.setVisible(not LabelPanel.getVisible());
  if (LabelPanel.getVisible() == false) {
    Button.setCaption("SHOW");
  } else {
    Button.setCaption("HIDE");
  }
  
}


void setup() {
  Serial.begin(9600);
  //объект библиотеки UTFT
	GLCD.InitLCD();
	GLCD.setFont(arial_bold_rus);
	GLCD.clrScr();
	//объект библиотеки UTouch (URTouch)
	Touch.InitTouch();
	Touch.setPrecision(PREC_HI);
	//инициализируем дисплей
	Display.init();
	//метка состояния
	Label.setAlignCaption(DT_CENTER);
  Label.setFont(BigFont);
  Label.setCaption("THIS IS LABEL");
	Label.show();
	//кнопка ПУСК
  Button.setFont(BigFont);
  Button.setCaption("HIDE");
	Button.onClick = ButtonClick;
	Button.show();
  //Показываем панель с компонентами
  MainPanel.show();
  LabelPanel.show();
}

void loop() {
  TPoint TouchPoint;
  
  static TControl * FocusControl = NULL;

  Serial.println(Touch.dataAvailable());

  if (Touch.dataAvailable() == true) {
    Touch.read();
    TouchPoint.X = Touch.getX();
    TouchPoint.Y = Touch.getY();
    Serial.println(TouchPoint.X);
    Serial.println(TouchPoint.Y);
    if (TouchPoint.X > 0) {
      FocusControl = Display.activate(&TouchPoint);
    }
  } else {
    FocusControl = Display.deactivate(FocusControl);
  }		
}
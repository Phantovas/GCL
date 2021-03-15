# GLC

���������� ���������� ��������� ��� Arduino UTFT � URTouch.
������ v0.1a

## TODO

1. ������� ���� keywords.txt. �� ������ ������ �� ��������.
2. T�omponent.cpp: ������� ��������� ����������.
  
## �����������
	
���������� ������� ��� �������� ���������������� ����������� � �������������� TFT ������� � ��������� �������. 
��� ������ � TFT �������� ������������ ���������� UTFT(http://www.rinkydinkelectronics.com/library.php?id=51), � ���������� �������� ���������� URTouch (http://www.rinkydinkelectronics.com/library.php?id=92).

## �������� ������� 

#### �������� ������:
* TObject - ��������� �����, �� ����� � ���� ������� ����������, �������� ����� ������� ��� ���� �����������.
* TComponent - ����� �������������� ������� ���������� ���������� �����������, �� ����� �������� �� ����������� ����������� ���������� �����������.
* TControl - �������� ����� ����������� �����������, ��������� ����� ������ ����������� �����, ���������, ����� ������, �������.
* TPassiveControl - ����� ��������� TControl, ����������� ��������� ��������� �����������, ������� �� ��������� �� �������� ������������, � ������ ������� ����������.
* TActiveControl - ����� ��������� TControl, ����������� ��������� �������� �����������, ������� ��������� �� �������� ������������.

#### ���������� TPassiveControl:
* TDisplay - ����� �������, ������������ ��� �������� � ����� ��������� �� ������ ���������� UTFT ��� ������ � ���������������� ������� ���������� �� �����. 
	> � ������ ������������� ���������� ������� � ����� ��, ��� ������� ������ ���������� ��������� ��������� ������ ������ TDisplay.
* TPanel - ������, ���������� � ���� ��������� �����������, ��������� ������ ������ ��� �������� ������ ��������.
* TLabel - ��������� ��� ������ �������� ����������.
* TIndicator - ��������� ��� ����������� ��������� <i>On/Off</i>. ������������ � ���� �������� � �������� ��� ���. ������, ���������� ������, ����������� � PROGMEM ��.
* TTrackBar - ��������, ������������ ������������� �������� ���������� � ��������� ���������.

#### ���������� TActiveControl:
* TButton - ������, ��������� �� ������������� � ����������. ��� ������������� ���������� ����� press() ��� ���������� ����� click().
* TSlider - �������������, ��������� ��������, � ������� �� TIndicator, ��������� <i>On/Off</i>

## ��� ������������ (How to use)

##### 1. ���������� ����������

		UTFT    GLCD(ITDB32S, 38,39,40,41);   // Remember to change the model parameter to suit your display module!
		UTouch  Touch(6,5,4,3,2);
		TDisplay Display(&GLCD);
		TPanel MainPanel(&Display, 0, 0, 320, 240);
		TPanel StatusPanel(&MainPanel, 0, 0, 320, 40);
		TLabel LStatus(&StatusPanel, 0, 0, 205, 40);
		TButton BtnStart(&StatusPanel, 210, 0, 110, 40);

##### 2. ������������� ����������

		//������ ���������� UTFT
		GLCD.InitLCD();
		GLCD.setFont(arial_bold_rus);
		GLCD.clrScr();
		//������ ���������� UTouch (URTouch)
		Touch.InitTouch();
		Touch.setPrecision(PREC_HI);
		//�������������� ������� � ��������� ������ �� ������ LCD
		Display.init();
		MainPanel.setWidth(Display.getClientWidth());
		MainPanel.setHeight(Display.getClientHeight());
		//������� ������� ��� �����������
		StatusPanel.setWidth(MainPanel.getClientWidth());
		//����� ���������
		LStatus.setHeight(LStatus.Height-StatusPanel.Border*2);
		LStatus.setAlignCaption(DT_CENTER);
		LStatus.show();
		//������ ����
		BtnStart.setWidth(StatusPanel.getClientWidth()-LStatus.Width - 5);
		BtnStart.setHeight(LStatus.Height);
		BtnStart.onClick = BtnStartClick;
		BtnStart.show();
	
##### 3. ��������� �������
		void loop() {
			TPoint TouchPoint;
			static TControl * FocusControl = NULL;
			
			if (Touch.dataAvailable() == true) {
				Touch.read();
				TouchPoint.X = Touch.getX();
				TouchPoint.Y = Touch.getY();
				if (TouchPoint.X > 0) {
					FocusControl = Display.activate(&TouchPoint);
				}
			} else {
				FocusControl = Display.deactivate(FocusControl);
			}		
		}
	
����� ������ ����������� ������������� �� ������ ��������� ���������� ��������� ������� � ������������ ���������. ���������� ������� �� ����������� ���������� ����������� �����������, � ��, � ���� �������, ��������� ���������������� ��������.
	
	
	
	
	
	

	





  
  
  


# GLC

Библиотека визуальных компонент для Arduino UTFT и URTouch.
Версия v0.1a

## TODO

1. Сделать файл keywords.txt. На данный момент он неверный.
2. TСomponent.cpp: сделать обработку исключений.
  
## Возможности
	
Библиотека создана для быстрого прототипирования интерфейсов с использованием TFT экранов с сенсорный панелью. 
Для работы с TFT экранами используется библиотека UTFT(http://www.rinkydinkelectronics.com/library.php?id=51), с сенсорными панелями библиотека URTouch (http://www.rinkydinkelectronics.com/library.php?id=92).

## Иерархия классов 

#### Основные классы:
* TObject - основоной класс, не несет в себе никакой реализации, является общим предком для всех наследников.
* TComponent - класс обрабатывающий цепочки подчинения визуальных компонентов, он также отвечает за перерисовку вложенности визуальных компонентов.
* TControl - основной класс визауальных компонентов, реализует общие методы вычисляющие рамки, положение, вывод текста, заливку.
* TPassiveControl - класс наследник TControl, реализующий интерфейс пассивных компонентов, которые не реагируют на действия пользователя, а только выводят информацию.
* TActiveControl - класс наследник TControl, реализующий интерфейс активных компонентов, которые реагируют на действия пользователя.

#### Наследники TPassiveControl:
* TDisplay - класс дисплея, используется для передачи в класс указателя на объект библиотеки UTFT для работы с непосредственным выводом информации на экран. 
	> В случае использования нескольких экранов с одним МК, для каждого экрана необходимо создавать отдельный объект класса TDisplay.
* TPanel - панель, содержащая в себе несколько компонентов, позволяет быстро скрыть или показать группу объектов.
* TLabel - компонент для вывода тестовой информации.
* TIndicator - компонент для отображения состояния <i>On/Off</i>. Отображается в виде квадрата с галочкой или без. Ресурс, содержащий иконки, сохраняется в PROGMEM МК.
* TTrackBar - ползунок, отображающий установленное значение переменной в выбранном диапазоне.

#### Наследники TActiveControl:
* TButton - кнопка, реагирует на прикосновение и отпускание. При прикосновении вызывается метод press() при отпускании метод click().
* TSlider - переключатель, позволяет изменять, в отличии от TIndicator, состояния <i>On/Off</i>

## Как использовать (How to use)

##### 1. Объявление переменных

		UTFT    GLCD(ITDB32S, 38,39,40,41);   // Remember to change the model parameter to suit your display module!
		UTouch  Touch(6,5,4,3,2);
		TDisplay Display(&GLCD);
		TPanel MainPanel(&Display, 0, 0, 320, 240);
		TPanel StatusPanel(&MainPanel, 0, 0, 320, 40);
		TLabel LStatus(&StatusPanel, 0, 0, 205, 40);
		TButton BtnStart(&StatusPanel, 210, 0, 110, 40);

##### 2. Инициализация переменных

		//объект библиотеки UTFT
		GLCD.InitLCD();
		GLCD.setFont(arial_bold_rus);
		GLCD.clrScr();
		//объект библиотеки UTouch (URTouch)
		Touch.InitTouch();
		Touch.setPrecision(PREC_HI);
		//инициализируем дисплей с передачей ссылки на объект LCD
		Display.init();
		MainPanel.setWidth(Display.getClientWidth());
		MainPanel.setHeight(Display.getClientHeight());
		//готовим размеры для компонентов
		StatusPanel.setWidth(MainPanel.getClientWidth());
		//метка состояния
		LStatus.setHeight(LStatus.Height-StatusPanel.Border*2);
		LStatus.setAlignCaption(DT_CENTER);
		LStatus.show();
		//кнопка ПУСК
		BtnStart.setWidth(StatusPanel.getClientWidth()-LStatus.Width - 5);
		BtnStart.setHeight(LStatus.Height);
		BtnStart.onClick = BtnStartClick;
		BtnStart.show();
	
##### 3. Обработка касания
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
	
После данных манипуляций освобождаемся от рутины обработки совпадения координат касания с координатами контролов. Координаты касания по ниспадающей передаются подчиненным компонентам, а те, в свою очередь, реагируют соответствующими методами.
	
	
	
	
	
	

	





  
  
  


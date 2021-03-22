/**
 * 
 * GCLTypes.h - types for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

/**
 * @var
 * Шрифты, которые используем 
 */
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
//extern uint8_t Inconsola[];
extern uint8_t hallfetica_rus[];
extern uint8_t arial_bold_rus[];
extern uint8_t GlcSymbol[];
extern uint8_t DotMatrix_M_rus[];
extern uint16_t icon_check[];
extern uint16_t icon_uncheck[];

/**
 * @var
 * Структурный тип описания координат точки (X,Y)
 */
typedef struct TPoint {
  unsigned int X, Y;
};

/**
 * @var
 * Структурный тип описания прямоугольной области
 * по 4 углам
 */
typedef struct TRect {
  unsigned int Left, Top, Right, Bottom;
};

/**
 * @var
 * Предварительная декларация классов для списка
  */
class TComponent;
class TControl;

/**
 * @var
 * Односвязный список, для хранения порядка создания объектов
 */
typedef struct listItem {
  TComponent *pComponent;
  listItem *next;
};

/**
 * @var
 * Тип трэкбара. Ползунок или прогресс.
 */
typedef enum TTypeBar {TB_CURSOR, TB_PROGRESS};

/**
 * @var
 * Указатель на функцию события
 */
typedef void (*TNotifyEvent)();

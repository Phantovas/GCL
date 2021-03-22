/**
 * 
 * GCLConsts.h - constans for library GCL.
 * Created by Vasiliy A. Ponomaryov, March 22, 2021.
 * Email: vas@vingrad.ru
 * 
*/

/**
 * @define 
 * Флаг релизной сборки, для отключения сообщений в Serial
 */
#define RELEASE

/**
 * @define 
 * Задержка при прорисовке 
 */
#define PAINT_DELAY 0        

/**
 * @define 
 * Задержка на активацию
 */
#define ACTIVATE_DELAY 100 

/**
 * @define 
 * Цвета
 */
#define CL_BLACK                VGA_BLACK		
#define CL_WHITE                VGA_WHITE		
#define CL_RED                  VGA_RED			
#define CL_GREEN                VGA_GREEN		
#define CL_BLUE                 VGA_BLUE		
#define CL_SILVER               VGA_SILVER	
#define CL_GRAY                 VGA_GRAY		
#define CL_MAROON               VGA_MAROON	
#define CL_YELLOW               VGA_YELLOW	
#define CL_OLIVE                VGA_OLIVE		
#define CL_LIME                 VGA_LIME		
#define CL_AQUA                 VGA_AQUA		
#define CL_TEAL                 VGA_TEAL		
#define CL_NAVY                 VGA_NAVY		
#define CL_FUCHSIA              VGA_FUCHSIA	
#define CL_PURPLE               VGA_PURPLE	
#define CL_TRANSPARENT          VGA_TRANSPARENT

/**
 * @define 
 * Системные цвета для элементов управления.
 * Измениния отразятся на дефолтной отрисовке контролов.
 */
#define CL_NONE                 CL_BLACK
#define CL_BTNCOLOR             CL_BLUE
#define CL_BORDERCOLOR          CL_GREEN //CL_NAVY
#define CL_ACTIVEBORDERCOLOR    CL_YELLOW
#define CL_FONTCOLOR            CL_WHITE
#define CL_DISABLEFONTCOLOR     CL_BLACK
#define CL_PROGRESSCOLOR        CL_BLUE

/**
 * @define 
 * Положения элементов
 */
#define DT_LEFT                 0x00
#define DT_CENTER               0x01
#define DT_RIGHT                0x10

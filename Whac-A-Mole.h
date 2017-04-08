/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUIT                       2       /* control type: command, callback function: Quit */
#define  PANEL_HOLE_9                     3       /* control type: pictRing, callback function: Hole_9 */
#define  PANEL_HOLE_8                     4       /* control type: pictRing, callback function: Hole_8 */
#define  PANEL_HOLE_7                     5       /* control type: pictRing, callback function: Hole_7 */
#define  PANEL_HOLE_6                     6       /* control type: pictRing, callback function: Hole_6 */
#define  PANEL_HOLE_5                     7       /* control type: pictRing, callback function: Hole_5 */
#define  PANEL_HOLE_4                     8       /* control type: pictRing, callback function: Hole_4 */
#define  PANEL_HOLE_3                     9       /* control type: pictRing, callback function: Hole_3 */
#define  PANEL_HOLE_2                     10      /* control type: pictRing, callback function: Hole_2 */
#define  PANEL_HOLE_1                     11      /* control type: pictRing, callback function: Hole_1 */
#define  PANEL_START                      12      /* control type: command, callback function: Start */
#define  PANEL_SCORE                      13      /* control type: numeric, callback function: (none) */
#define  PANEL_TIMER                      14      /* control type: timer, callback function: ProcessLoop */
#define  PANEL_STARTMESSAGE               15      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Hole_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hole_9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ProcessLoop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif

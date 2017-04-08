/* Include .h */
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <windows.h>
#include "Whac-A-Mole.h"

/* Start State */
#define TRUE 1
#define FALSE 0

/* Picture States */
#define EMPTY 0
#define POPOUT 1
#define HIT 2
#define ERROR 4

/* Declare Global Variable */
static int panelHandle;
static int start=FALSE;
static int score=0;
static int hole_1[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_2[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_3[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_4[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_5[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_6[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_7[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_8[2]={EMPTY , 0}; /* { Picture States , time } */
static int hole_9[2]={EMPTY , 0}; /* { Picture States , time } */
static int mouse_click_time[2]={FALSE , 0}; /* { Mouse Click States , time } */
static int ra_1=0; /* Appear Probability */
static int ra_2=0; /* Appear Probability */
static int ra_3=0; /* Appear Probability */
static int ra_4=0; /* Appear Probability */
static int ra_5=0; /* Appear Probability */
static int ra_6=0; /* Appear Probability */
static int ra_7=0; /* Appear Probability */
static int ra_8=0; /* Appear Probability */
static int ra_9=0; /* Appear Probability */

/* Main */
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Whac-A-Mole.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

/* Start ? */
int CVICALLBACK Start (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			start=TRUE;
			SetCtrlAttribute (panelHandle, PANEL_HOLE_1, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_2, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_3, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_4, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_5, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_6, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_7, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_8, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_HOLE_9, ATTR_DIMMED, 0);
			
			srand(time(NULL));
			ra_1=(rand()%10)+2; /* Random from 2 to 11 */
			ra_2=(rand()%10)+2; /* Random from 2 to 11 */
			ra_3=(rand()%10)+2; /* Random from 2 to 11 */
			ra_4=(rand()%10)+2; /* Random from 2 to 11 */
			ra_5=(rand()%10)+2; /* Random from 2 to 11 */
			ra_6=(rand()%10)+2; /* Random from 2 to 11 */
			ra_7=(rand()%10)+2; /* Random from 2 to 11 */
			ra_8=(rand()%10)+2; /* Random from 2 to 11 */
			ra_9=(rand()%10)+2; /* Random from 2 to 11 */
		break;
	}
	return 0;
}

/* Timer */
int CVICALLBACK ProcessLoop (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{   
		case EVENT_TIMER_TICK:
		{
			if (mouse_click_time[0]==FALSE)
			{
				HCURSOR hCurs1 = LoadCursorFromFile("Mouse1.ani"); /* Load Mouse Cursor */
				SetCursor (hCurs1); /* Change Mouse Cursor */
				DestroyCursor(hCurs1); /* Release Mouse Cursor Memory */
			}

			if (mouse_click_time[0]==TRUE)
			{
				if (mouse_click_time[1]<170)
				{
					mouse_click_time[1]++;
					HCURSOR hCurs2 = LoadCursorFromFile("Mouse2.ani"); /* Load Mouse Cursor */
					SetCursor (hCurs2); /* Change Mouse Cursor */
					DestroyCursor(hCurs2); /* Release Mouse Cursor Memory */
				}
				
				if (mouse_click_time[1]>=170)
				{
					mouse_click_time[1]=0;
					mouse_click_time[0]=FALSE;
				}	
			}
			
			if (start==TRUE) /* Start */
			{
				SetCtrlAttribute (panelHandle, PANEL_START, ATTR_DIMMED, 1); /* Start Dimmed */
				SetCtrlAttribute (panelHandle, PANEL_STARTMESSAGE, ATTR_VISIBLE, 1); /* Startmessage Visible */
				
				static int startmessagetime=0;
				static int shift=0;
				static int startmessage_visible=TRUE;
				
				if (startmessage_visible==TRUE)
					startmessagetime++;
				
				if (startmessagetime>=3) /* StartMessage Speed */
				{	
					startmessagetime=0;
					shift++;
					SetCtrlAttribute (panelHandle, PANEL_STARTMESSAGE, ATTR_LEFT, 400-shift);
				}
				
				if (shift>=800)
				{	
					SetCtrlAttribute (panelHandle, PANEL_STARTMESSAGE, ATTR_VISIBLE, 0); /* Startmessage Hide */
					startmessage_visible=0;
				}
				
				static double random_1=0;
				static int random_1_number=0; /* Declare Random Appear Probability */
				static double random_2=0;
				static int random_2_number=0; /* Declare Random Appear Probability */
				static double random_3=0;
				static int random_3_number=0; /* Declare Random Appear Probability */
				static double random_4=0;
				static int random_4_number=0; /* Declare Random Appear Probability */
				static double random_5=0;
				static int random_5_number=0; /* Declare Random Appear Probability */
				static double random_6=0;
				static int random_6_number=0; /* Declare Random Appear Probability */
				static double random_7=0;
				static int random_7_number=0; /* Declare Random Appear Probability */
				static double random_8=0;
				static int random_8_number=0; /* Declare Random Appear Probability */
				static double random_9=0;
				static int random_9_number=0; /* Declare Random Appear Probability */
			
					/* hole_1 */
				if (hole_1[0]==EMPTY)
				{
					random_1=ra_1*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_1>=(ra_1-1)) /* Appear Probability */
						random_1_number++;
				
					if (random_1_number>1000)
					{	
						hole_1[0]=POPOUT;
						random_1_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_1[0]==POPOUT)
				{
					hole_1[1]++;
			
					if ( hole_1[1]>0 && hole_1[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 2);
					if ( hole_1[1]>100 && hole_1[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 3);
					if ( hole_1[1]>200 && hole_1[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 4);
					if ( hole_1[1]>300 && hole_1[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 5);
					if ( hole_1[1]>400 && hole_1[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 6);
					if ( hole_1[1]>500 && hole_1[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 7);
					if ( hole_1[1]>600 && hole_1[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 8);
					if ( hole_1[1]>700 && hole_1[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 9);
					if ( hole_1[1]>800 && hole_1[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 10);
					if ( hole_1[1]>900 && hole_1[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 11);
					if ( hole_1[1]>1000 && hole_1[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 11);
					if ( hole_1[1]>1100 && hole_1[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 10);
					if ( hole_1[1]>1200 && hole_1[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 9);
					if ( hole_1[1]>1300 && hole_1[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 8);
					if ( hole_1[1]>1400 && hole_1[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 7);
					if ( hole_1[1]>1500 && hole_1[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 6);
					if ( hole_1[1]>1600 && hole_1[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 5);
					if ( hole_1[1]>1700 && hole_1[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 4);
					if ( hole_1[1]>1800 && hole_1[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 3);
					if ( hole_1[1]>1900 && hole_1[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 2);
					if ( hole_1[1]>2000 )
					{	
						hole_1[1]=0; /* Reset time */
						hole_1[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_1[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_1, 12); /* Update Picture Good HIT State */
				
					if (hole_1[1]<1000) /* Keep for 1 seconds */
						hole_1[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_1[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 1); /* Update Picture EMPTY State */
						hole_1[1]=0; /* Reset time */
					}
				}
			
				if (hole_1[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_1, 13); /* Update Picture Error HIT State */
				
					if (hole_1[1]<1000) /* Keep for 1 seconds */
						hole_1[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_1[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_1, 1); /* Update Picture EMPTY State */
						hole_1[1]=0; /* Reset time */
					}
				}
				
					/* hole_2 */
				if (hole_2[0]==EMPTY)
				{
					random_2=ra_2*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_2>=(ra_2-1)) /* Appear Probability */
						random_2_number++;
				
					if (random_2_number>1000)
					{	
						hole_2[0]=POPOUT;
						random_2_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_2[0]==POPOUT)
				{
					hole_2[1]++;
			
					if ( hole_2[1]>0 && hole_2[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 2);
					if ( hole_2[1]>100 && hole_2[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 3);
					if ( hole_2[1]>200 && hole_2[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 4);
					if ( hole_2[1]>300 && hole_2[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 5);
					if ( hole_2[1]>400 && hole_2[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 6);
					if ( hole_2[1]>500 && hole_2[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 7);
					if ( hole_2[1]>600 && hole_2[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 8);
					if ( hole_2[1]>700 && hole_2[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 9);
					if ( hole_2[1]>800 && hole_2[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 10);
					if ( hole_2[1]>900 && hole_2[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 11);
					if ( hole_2[1]>1000 && hole_2[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 11);
					if ( hole_2[1]>1100 && hole_2[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 10);
					if ( hole_2[1]>1200 && hole_2[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 9);
					if ( hole_2[1]>1300 && hole_2[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 8);
					if ( hole_2[1]>1400 && hole_2[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 7);
					if ( hole_2[1]>1500 && hole_2[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 6);
					if ( hole_2[1]>1600 && hole_2[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 5);
					if ( hole_2[1]>1700 && hole_2[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 4);
					if ( hole_2[1]>1800 && hole_2[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 3);
					if ( hole_2[1]>1900 && hole_2[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 2);
					if ( hole_2[1]>2000 )
					{	
						hole_2[1]=0; /* Reset time */
						hole_2[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_2[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_2, 12); /* Update Picture Good HIT State */
				
					if (hole_2[1]<1000) /* Keep for 1 seconds */
						hole_2[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_2[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 1); /* Update Picture EMPTY State */
						hole_2[1]=0; /* Reset time */
					}
				}
			
				if (hole_2[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_2, 13); /* Update Picture Error HIT State */
				
					if (hole_2[1]<1000) /* Keep for 1 seconds */
						hole_2[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_2[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_2, 1); /* Update Picture EMPTY State */
						hole_2[1]=0; /* Reset time */
					}
				}
				
					/* hole_3 */
				if (hole_3[0]==EMPTY)
				{
					random_3=ra_3*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_3>=(ra_3-1)) /* Appear Probability */
						random_3_number++;
				
					if (random_3_number>1000)
					{	
						hole_3[0]=POPOUT;
						random_3_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_3[0]==POPOUT)
				{
					hole_3[1]++;
			
					if ( hole_3[1]>0 && hole_3[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 2);
					if ( hole_3[1]>100 && hole_3[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 3);
					if ( hole_3[1]>200 && hole_3[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 4);
					if ( hole_3[1]>300 && hole_3[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 5);
					if ( hole_3[1]>400 && hole_3[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 6);
					if ( hole_3[1]>500 && hole_3[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 7);
					if ( hole_3[1]>600 && hole_3[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 8);
					if ( hole_3[1]>700 && hole_3[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 9);
					if ( hole_3[1]>800 && hole_3[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 10);
					if ( hole_3[1]>900 && hole_3[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 11);
					if ( hole_3[1]>1000 && hole_3[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 11);
					if ( hole_3[1]>1100 && hole_3[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 10);
					if ( hole_3[1]>1200 && hole_3[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 9);
					if ( hole_3[1]>1300 && hole_3[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 8);
					if ( hole_3[1]>1400 && hole_3[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 7);
					if ( hole_3[1]>1500 && hole_3[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 6);
					if ( hole_3[1]>1600 && hole_3[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 5);
					if ( hole_3[1]>1700 && hole_3[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 4);
					if ( hole_3[1]>1800 && hole_3[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 3);
					if ( hole_3[1]>1900 && hole_3[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 2);
					if ( hole_3[1]>2000 )
					{	
						hole_3[1]=0; /* Reset time */
						hole_3[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_3[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_3, 12); /* Update Picture Good HIT State */
				
					if (hole_3[1]<1000) /* Keep for 1 seconds */
						hole_3[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_3[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 1); /* Update Picture EMPTY State */
						hole_3[1]=0; /* Reset time */
					}
				}
			
				if (hole_3[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_3, 13); /* Update Picture Error HIT State */
				
					if (hole_3[1]<1000) /* Keep for 1 seconds */
						hole_3[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_3[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_3, 1); /* Update Picture EMPTY State */
						hole_3[1]=0; /* Reset time */
					}
				}
				
					/* hole_4 */
				if (hole_4[0]==EMPTY)
				{
					random_4=ra_4*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_4>=(ra_4-1)) /* Appear Probability */
						random_4_number++;
				
					if (random_4_number>1000)
					{	
						hole_4[0]=POPOUT;
						random_4_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_4[0]==POPOUT)
				{
					hole_4[1]++;
			
					if ( hole_4[1]>0 && hole_4[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 2);
					if ( hole_4[1]>100 && hole_4[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 3);
					if ( hole_4[1]>200 && hole_4[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 4);
					if ( hole_4[1]>300 && hole_4[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 5);
					if ( hole_4[1]>400 && hole_4[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 6);
					if ( hole_4[1]>500 && hole_4[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 7);
					if ( hole_4[1]>600 && hole_4[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 8);
					if ( hole_4[1]>700 && hole_4[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 9);
					if ( hole_4[1]>800 && hole_4[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 10);
					if ( hole_4[1]>900 && hole_4[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 11);
					if ( hole_4[1]>1000 && hole_4[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 11);
					if ( hole_4[1]>1100 && hole_4[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 10);
					if ( hole_4[1]>1200 && hole_4[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 9);
					if ( hole_4[1]>1300 && hole_4[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 8);
					if ( hole_4[1]>1400 && hole_4[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 7);
					if ( hole_4[1]>1500 && hole_4[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 6);
					if ( hole_4[1]>1600 && hole_4[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 5);
					if ( hole_4[1]>1700 && hole_4[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 4);
					if ( hole_4[1]>1800 && hole_4[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 3);
					if ( hole_4[1]>1900 && hole_4[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 2);
					if ( hole_4[1]>2000 )		
					{	
						hole_4[1]=0; /* Reset time */
						hole_4[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_4[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_4, 12); /* Update Picture Good HIT State */
				
					if (hole_4[1]<1000) /* Keep for 1 seconds */
						hole_4[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_4[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 1); /* Update Picture EMPTY State */
						hole_4[1]=0; /* Reset time */
					}
				}
			
				if (hole_4[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_4, 13); /* Update Picture Error HIT State */
				
					if (hole_4[1]<1000) /* Keep for 1 seconds */
						hole_4[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_4[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_4, 1); /* Update Picture EMPTY State */
						hole_4[1]=0; /* Reset time */
					}
				}
			
					/* hole_5 */
				if (hole_5[0]==EMPTY)
				{
					random_5=ra_5*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_5>=(ra_5-1)) /* Appear Probability */
						random_5_number++;
				
					if (random_5_number>1000)
					{	
						hole_5[0]=POPOUT;
						random_5_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_5[0]==POPOUT)
				{
					hole_5[1]++;
			
					if ( hole_5[1]>0 && hole_5[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 2);
					if ( hole_5[1]>100 && hole_5[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 3);
					if ( hole_5[1]>200 && hole_5[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 4);
					if ( hole_5[1]>300 && hole_5[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 5);
					if ( hole_5[1]>400 && hole_5[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 6);
					if ( hole_5[1]>500 && hole_5[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 7);
					if ( hole_5[1]>600 && hole_5[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 8);
					if ( hole_5[1]>700 && hole_5[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 9);
					if ( hole_5[1]>800 && hole_5[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 10);
					if ( hole_5[1]>900 && hole_5[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 11);
					if ( hole_5[1]>1000 && hole_5[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 11);
					if ( hole_5[1]>1100 && hole_5[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 10);
					if ( hole_5[1]>1200 && hole_5[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 9);
					if ( hole_5[1]>1300 && hole_5[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 8);
					if ( hole_5[1]>1400 && hole_5[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 7);
					if ( hole_5[1]>1500 && hole_5[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 6);
					if ( hole_5[1]>1600 && hole_5[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 5);
					if ( hole_5[1]>1700 && hole_5[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 4);
					if ( hole_5[1]>1800 && hole_5[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 3);
					if ( hole_5[1]>1900 && hole_5[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 2);
					if ( hole_5[1]>2000 )		
					{	
						hole_5[1]=0; /* Reset time */
						hole_5[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_5[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_5, 12); /* Update Picture Good HIT State */
				
					if (hole_5[1]<1000) /* Keep for 1 seconds */
						hole_5[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_5[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 1); /* Update Picture EMPTY State */
						hole_5[1]=0; /* Reset time */
					}
				}
			
				if (hole_5[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_5, 13); /* Update Picture Error HIT State */
				
					if (hole_5[1]<1000) /* Keep for 1 seconds */
						hole_5[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_5[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_5, 1); /* Update Picture EMPTY State */
						hole_5[1]=0; /* Reset time */
					}
				}
			
					/* hole_6 */
				if (hole_6[0]==EMPTY)
				{
					random_6=ra_6*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_6>=(ra_6-1)) /* Appear Probability */
						random_6_number++;
				
					if (random_6_number>1000)
					{	
						hole_6[0]=POPOUT;
						random_6_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_6[0]==POPOUT)
				{
					hole_6[1]++;
			
					if ( hole_6[1]>0 && hole_6[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 2);
					if ( hole_6[1]>100 && hole_6[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 3);
					if ( hole_6[1]>200 && hole_6[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 4);
					if ( hole_6[1]>300 && hole_6[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 5);
					if ( hole_6[1]>400 && hole_6[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 6);
					if ( hole_6[1]>500 && hole_6[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 7);
					if ( hole_6[1]>600 && hole_6[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 8);
					if ( hole_6[1]>700 && hole_6[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 9);
					if ( hole_6[1]>800 && hole_6[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 10);
					if ( hole_6[1]>900 && hole_6[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 11);
					if ( hole_6[1]>1000 && hole_6[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 11);
					if ( hole_6[1]>1100 && hole_6[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 10);
					if ( hole_6[1]>1200 && hole_6[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 9);
					if ( hole_6[1]>1300 && hole_6[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 8);
					if ( hole_6[1]>1400 && hole_6[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 7);
					if ( hole_6[1]>1500 && hole_6[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 6);
					if ( hole_6[1]>1600 && hole_6[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 5);
					if ( hole_6[1]>1700 && hole_6[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 4);
					if ( hole_6[1]>1800 && hole_6[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 3);
					if ( hole_6[1]>1900 && hole_6[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 2);
					if ( hole_6[1]>2000 )		
					{	
						hole_6[1]=0; /* Reset time */
						hole_6[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_6[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_6, 12); /* Update Picture Good HIT State */
				
					if (hole_6[1]<1000) /* Keep for 1 seconds */
						hole_6[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_6[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 1); /* Update Picture EMPTY State */
						hole_6[1]=0; /* Reset time */
					}
				}
			
				if (hole_6[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_6, 13); /* Update Picture Error HIT State */
				
					if (hole_6[1]<1000) /* Keep for 1 seconds */
						hole_6[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_6[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_6, 1); /* Update Picture EMPTY State */
						hole_6[1]=0; /* Reset time */
					}
				}
			
					/* hole_7 */
				if (hole_7[0]==EMPTY)
				{
					random_7=ra_7*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_7>=(ra_7-1)) /* Appear Probability */
						random_7_number++;
				
					if (random_7_number>1000)
					{	
						hole_7[0]=POPOUT;
						random_7_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_7[0]==POPOUT)
				{
					hole_7[1]++;
			
					if ( hole_7[1]>0 && hole_7[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 2);
					if ( hole_7[1]>100 && hole_7[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 3);
					if ( hole_7[1]>200 && hole_7[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 4);
					if ( hole_7[1]>300 && hole_7[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 5);
					if ( hole_7[1]>400 && hole_7[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 6);
					if ( hole_7[1]>500 && hole_7[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 7);
					if ( hole_7[1]>600 && hole_7[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 8);
					if ( hole_7[1]>700 && hole_7[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 9);
					if ( hole_7[1]>800 && hole_7[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 10);
					if ( hole_7[1]>900 && hole_7[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 11);
					if ( hole_7[1]>1000 && hole_7[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 11);
					if ( hole_7[1]>1100 && hole_7[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 10);
					if ( hole_7[1]>1200 && hole_7[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 9);
					if ( hole_7[1]>1300 && hole_7[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 8);
					if ( hole_7[1]>1400 && hole_7[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 7);
					if ( hole_7[1]>1500 && hole_7[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 6);
					if ( hole_7[1]>1600 && hole_7[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 5);
					if ( hole_7[1]>1700 && hole_7[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 4);
					if ( hole_7[1]>1800 && hole_7[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 3);
					if ( hole_7[1]>1900 && hole_7[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 2);
					if ( hole_7[1]>2000 )		
					{	
						hole_7[1]=0; /* Reset time */
						hole_7[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_7[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_7, 12); /* Update Picture Good HIT State */
				
					if (hole_7[1]<1000) /* Keep for 1 seconds */
						hole_7[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_7[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 1); /* Update Picture EMPTY State */
						hole_7[1]=0; /* Reset time */
					}
				}
			
				if (hole_7[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_7, 13); /* Update Picture Error HIT State */
				
					if (hole_7[1]<1000) /* Keep for 1 seconds */
						hole_7[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_7[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_7, 1); /* Update Picture EMPTY State */
						hole_7[1]=0; /* Reset time */
					}
				}
			
					/* hole_8 */
				if (hole_8[0]==EMPTY)
				{
					random_8=ra_8*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_8>=(ra_8-1)) /* Appear Probability */
						random_8_number++;
				
					if (random_8_number>1000)
					{	
						hole_8[0]=POPOUT;
						random_8_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_8[0]==POPOUT)
				{
					hole_8[1]++;
			
					if ( hole_8[1]>0 && hole_8[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 2);
					if ( hole_8[1]>100 && hole_8[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 3);
					if ( hole_8[1]>200 && hole_8[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 4);
					if ( hole_8[1]>300 && hole_8[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 5);
					if ( hole_8[1]>400 && hole_8[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 6);
					if ( hole_8[1]>500 && hole_8[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 7);
					if ( hole_8[1]>600 && hole_8[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 8);
					if ( hole_8[1]>700 && hole_8[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 9);
					if ( hole_8[1]>800 && hole_8[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 10);
					if ( hole_8[1]>900 && hole_8[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 11);
					if ( hole_8[1]>1000 && hole_8[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 11);
					if ( hole_8[1]>1100 && hole_8[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 10);
					if ( hole_8[1]>1200 && hole_8[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 9);
					if ( hole_8[1]>1300 && hole_8[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 8);
					if ( hole_8[1]>1400 && hole_8[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 7);
					if ( hole_8[1]>1500 && hole_8[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 6);
					if ( hole_8[1]>1600 && hole_8[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 5);
					if ( hole_8[1]>1700 && hole_8[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 4);
					if ( hole_8[1]>1800 && hole_8[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 3);
					if ( hole_8[1]>1900 && hole_8[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 2);
					if ( hole_8[1]>2000 )		
					{	
						hole_8[1]=0; /* Reset time */
						hole_8[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_8[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_8, 12); /* Update Picture Good HIT State */
				
					if (hole_8[1]<1000) /* Keep for 1 seconds */
						hole_8[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_8[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 1); /* Update Picture EMPTY State */
						hole_8[1]=0; /* Reset time */
					}
				}
			
				if (hole_8[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_8, 13); /* Update Picture Error HIT State */
				
					if (hole_8[1]<1000) /* Keep for 1 seconds */
						hole_8[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_8[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_8, 1); /* Update Picture EMPTY State */
						hole_8[1]=0; /* Reset time */
					}
				}
			
					/* hole_9 */
				if (hole_9[0]==EMPTY)
				{
					random_9=ra_9*rand() / RAND_MAX; /* Generate Random Probability */
				
					if (random_9>=(ra_9-1)) /* Appear Probability */
						random_9_number++;
				
					if (random_9_number>1000)
					{	
						hole_9[0]=POPOUT;
						random_9_number=0; /* Reset random_1_number */
					}
				}
			
				if (hole_9[0]==POPOUT)
				{
					hole_9[1]++;
			
					if ( hole_9[1]>0 && hole_9[1]<=100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 2);
					if ( hole_9[1]>100 && hole_9[1]<=200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 3);
					if ( hole_9[1]>200 && hole_9[1]<=300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 4);
					if ( hole_9[1]>300 && hole_9[1]<=400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 5);
					if ( hole_9[1]>400 && hole_9[1]<=500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 6);
					if ( hole_9[1]>500 && hole_9[1]<=600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 7);
					if ( hole_9[1]>600 && hole_9[1]<=700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 8);
					if ( hole_9[1]>700 && hole_9[1]<=800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 9);
					if ( hole_9[1]>800 && hole_9[1]<=900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 10);
					if ( hole_9[1]>900 && hole_9[1]<=1000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 11);
					if ( hole_9[1]>1000 && hole_9[1]<=1100 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 11);
					if ( hole_9[1]>1100 && hole_9[1]<=1200 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 10);
					if ( hole_9[1]>1200 && hole_9[1]<=1300 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 9);
					if ( hole_9[1]>1300 && hole_9[1]<=1400 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 8);
					if ( hole_9[1]>1400 && hole_9[1]<=1500 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 7);
					if ( hole_9[1]>1500 && hole_9[1]<=1600 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 6);
					if ( hole_9[1]>1600 && hole_9[1]<=1700 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 5);
					if ( hole_9[1]>1700 && hole_9[1]<=1800 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 4);
					if ( hole_9[1]>1800 && hole_9[1]<=1900 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 3);
					if ( hole_9[1]>1900 && hole_9[1]<=2000 )
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 2);
					if ( hole_9[1]>2000 )		
					{	
						hole_9[1]=0; /* Reset time */
						hole_9[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 1); /* Update Picture EMPTY State */
					}
				}
			
				if (hole_9[0]==HIT) /* Good HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_9, 12); /* Update Picture Good HIT State */
				
					if (hole_9[1]<1000) /* Keep for 1 seconds */
						hole_9[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_9[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 1); /* Update Picture EMPTY State */
						hole_9[1]=0; /* Reset time */
					}
				}
			
				if (hole_9[0]==ERROR) /* Error HIT */
				{	
					SetCtrlVal (panelHandle, PANEL_HOLE_9, 13); /* Update Picture Error HIT State */
				
					if (hole_9[1]<1000) /* Keep for 1 seconds */
						hole_9[1]++;
					else /* Keep for 1 seconds after */
					{	
						hole_9[0]=EMPTY;
						SetCtrlVal (panelHandle, PANEL_HOLE_9, 1); /* Update Picture EMPTY State */
						hole_9[1]=0; /* Reset time */
					}
				}
			
			} /* Start */
		break;
		}
		
	}
	return 0;
}

int CVICALLBACK Hole_1 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_1[0]==POPOUT) /* Good HIT */
			{	
				hole_1[0]=HIT;
				hole_1[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_1[0]==EMPTY) /* Error HIT */
			{	
				hole_1[0]=ERROR;
				hole_1[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_2 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_2[0]==POPOUT) /* Good HIT */
			{	
				hole_2[0]=HIT;
				hole_2[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_2[0]==EMPTY) /* Error HIT */
			{	
				hole_2[0]=ERROR;
				hole_2[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_3 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_3[0]==POPOUT) /* Good HIT */
			{	
				hole_3[0]=HIT;
				hole_3[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_3[0]==EMPTY) /* Error HIT */
			{	
				hole_3[0]=ERROR;
				hole_3[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_4 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_4[0]==POPOUT) /* Good HIT */
			{	
				hole_4[0]=HIT;
				hole_4[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_4[0]==EMPTY) /* Error HIT */
			{	
				hole_4[0]=ERROR;
				hole_4[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_5 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_5[0]==POPOUT) /* Good HIT */
			{	
				hole_5[0]=HIT;
				hole_5[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_5[0]==EMPTY) /* Error HIT */
			{	
				hole_5[0]=ERROR;
				hole_5[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_6 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_6[0]==POPOUT) /* Good HIT */
			{	
				hole_6[0]=HIT;
				hole_6[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_6[0]==EMPTY) /* Error HIT */
			{	
				hole_6[0]=ERROR;
				hole_6[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_7 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_7[0]==POPOUT) /* Good HIT */
			{	
				hole_7[0]=HIT;
				hole_7[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_7[0]==EMPTY) /* Error HIT */
			{	
				hole_7[0]=ERROR;
				hole_7[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_8 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_8[0]==POPOUT) /* Good HIT */
			{	
				hole_8[0]=HIT;
				hole_8[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_8[0]==EMPTY) /* Error HIT */
			{	
				hole_8[0]=ERROR;
				hole_8[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

int CVICALLBACK Hole_9 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click_time[0]=TRUE;
			
			if (hole_9[0]==POPOUT) /* Good HIT */
			{	
				hole_9[0]=HIT;
				hole_9[1]=0; /* Reset time */
				score++;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
			
			if (hole_9[0]==EMPTY) /* Error HIT */
			{	
				hole_9[0]=ERROR;
				hole_9[1]=0; /* Reset time */
				score--;
				SetCtrlVal (panelHandle, PANEL_SCORE, score); /* Update SCORE */
			}
		break;
	}
	return 0;
}

/* Quit */
int CVICALLBACK Quit (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
		break;
	}
	return 0;
}

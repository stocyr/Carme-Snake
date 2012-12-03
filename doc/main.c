/**
 ***************************************************************************
 * \brief   Informatik 3
			uC/GUI example program
 * \version 1.0
 * \date    03.11.2007
 * \author  Juergen Schuepbach
 *
 * \remark  Last Modifications:
 ***************************************************************************
 */
#include <string.h>
#include <stdio.h>


#include <carme.h>
#include <pxa270.h>

#include <GUI.h>						// UC-GUI includes

#include <BSP_UART.h>
#include <BSP_CARMEIO1.h>

extern const GUI_BITMAP bmCARMEIDE;

char regString[1000];

typedef struct colors {
	GUI_COLOR color;
	char name[20];
	GUI_COLOR textColor;
} colors;

colors colorInfoTable[24];

void initColorTable(){

	colorInfoTable[0].color = GUI_BLUE;
	sprintf(colorInfoTable[0].name, "GUI_BLUE");
	colorInfoTable[0].textColor = GUI_BLACK;

	colorInfoTable[1].color = GUI_GREEN;
	sprintf(colorInfoTable[1].name, "GUI_GREEN");
	colorInfoTable[1].textColor = GUI_BLACK;

	colorInfoTable[2].color = GUI_RED;
	sprintf(colorInfoTable[2].name, "GUI_RED");
	colorInfoTable[2].textColor = GUI_BLACK;

	colorInfoTable[3].color = GUI_CYAN;
	sprintf(colorInfoTable[3].name, "GUI_CYAN");
	colorInfoTable[3].textColor = GUI_BLACK;

	colorInfoTable[4].color = GUI_MAGENTA;
	sprintf(colorInfoTable[4].name, "GUI_MAGENTA");
	colorInfoTable[4].textColor = GUI_BLACK;

	colorInfoTable[5].color = GUI_YELLOW;
	sprintf(colorInfoTable[5].name, "GUI_YELLOW");
	colorInfoTable[5].textColor = GUI_BLACK;

	colorInfoTable[6].color = GUI_LIGHTBLUE;
	sprintf(colorInfoTable[6].name, "GUI_LIGHTBLUE");
	colorInfoTable[6].textColor = GUI_WHITE;

	colorInfoTable[7].color = GUI_LIGHTGREEN;
	sprintf(colorInfoTable[7].name, "GUI_LIGHTGREEN");
	colorInfoTable[7].textColor = GUI_WHITE;

	colorInfoTable[8].color = GUI_LIGHTRED;
	sprintf(colorInfoTable[8].name, "GUI_LIGHTRED");
	colorInfoTable[8].textColor = GUI_WHITE;

	colorInfoTable[9].color = GUI_LIGHTCYAN;
	sprintf(colorInfoTable[9].name, "GUI_LIGHTCYAN");
	colorInfoTable[9].textColor = GUI_WHITE;

	colorInfoTable[10].color = GUI_LIGHTMAGENTA;
	sprintf(colorInfoTable[10].name, "GUI_LIGHTMAGENTA");
	colorInfoTable[10].textColor = GUI_WHITE;

	colorInfoTable[11].color = GUI_LIGHTYELLOW;
	sprintf(colorInfoTable[11].name, "GUI_LIGHTYELLOW");
	colorInfoTable[11].textColor = GUI_WHITE;

	colorInfoTable[12].color = GUI_DARKBLUE;
	sprintf(colorInfoTable[12].name, "GUI_DARKBLUE");
	colorInfoTable[12].textColor = GUI_WHITE;

	colorInfoTable[13].color = GUI_DARKGREEN;
	sprintf(colorInfoTable[13].name, "GUI_DARKGREEN");
	colorInfoTable[13].textColor = GUI_WHITE;

	colorInfoTable[14].color = GUI_DARKRED;
	sprintf(colorInfoTable[14].name, "GUI_DARKRED");
	colorInfoTable[14].textColor = GUI_WHITE;

	colorInfoTable[15].color = GUI_DARKCYAN;
	sprintf(colorInfoTable[15].name, "GUI_DARKCYAN");
	colorInfoTable[15].textColor = GUI_WHITE;

	colorInfoTable[16].color = GUI_DARKMAGENTA;
	sprintf(colorInfoTable[16].name, "GUI_DARKMAGENTA");
	colorInfoTable[16].textColor = GUI_WHITE;

	colorInfoTable[17].color = GUI_DARKYELLOW;
	sprintf(colorInfoTable[17].name, "GUI_DARKYELLOW");
	colorInfoTable[17].textColor = GUI_WHITE;

	colorInfoTable[18].color = GUI_WHITE;
	sprintf(colorInfoTable[18].name, "GUI_WHITE");
	colorInfoTable[18].textColor = GUI_BLACK;

	colorInfoTable[19].color = GUI_LIGHTGRAY;
	sprintf(colorInfoTable[19].name, "GUI_LIGHTGRAY");
	colorInfoTable[19].textColor = GUI_WHITE;

	colorInfoTable[20].color = GUI_GRAY;
	sprintf(colorInfoTable[20].name, "GUI_GRAY");
	colorInfoTable[20].textColor = GUI_WHITE;

	colorInfoTable[21].color = GUI_DARKGRAY;
	sprintf(colorInfoTable[21].name, "GUI_DARKGRAY");
	colorInfoTable[21].textColor = GUI_WHITE;

	colorInfoTable[22].color = GUI_BLACK;
	sprintf(colorInfoTable[22].name, "GUI_BLACK");
	colorInfoTable[22].textColor = GUI_WHITE;

	colorInfoTable[23].color = GUI_BROWN;
	sprintf(colorInfoTable[23].name, "GUI_BROWN");
	colorInfoTable[23].textColor = GUI_WHITE;


}
void printStatus(unsigned int uartNb){
	sprintf(regString,"LCSR0 = 0x%08lx LCSR1 = 0x%08lx FDADR0 = 0x%08lx\n\r",
			LCSR0,
			LCSR1,
			FDADR0);

	BSP_UART_printString(uartNb,regString);
	BSP_UART_printString(uartNb,"\n\r");
}


void drawTestScreen() {
	GUI_COLOR colors[8] = {GUI_WHITE, GUI_YELLOW, GUI_CYAN, GUI_GREEN, GUI_MAGENTA, GUI_RED, GUI_BLUE, GUI_BLACK};
	INT8U i;
	INT32U width = GUI_GetScreenSizeX() / 8;
	for (i = 0; i < 8; i++) {
		GUI_SetColor(colors[i]);
		GUI_FillRect((i * width), 0, ((i+1) * width), GUI_GetScreenSizeY());
	}

}

int buttonHandler(INT8U button, INT8U position, INT8U maxpos) {

	if (button == 0x1) {
		// incrment
		position++;
		if (position >= maxpos) {
			position = 0;
		}
	} else if(button == 0x2) {
		//decrement value
		position--;
		if (position > maxpos) {
			position = maxpos - 1;
		}
	}
	return (position);
}
int main_old(void){							//////////////////////////zu Main old umbenennt weil es Fehler gab

	ERR_CODES error = CARME_NO_ERROR;
	INT8U test = 9;
	INT8U i = 0;
	INT8U pushButtonData = 0;


	GUI_Init();
	initColorTable();

	BSP_CARMEIO1_init();
	// init uart
	error = BSP_UART_settings(0,  LOOPBACK_OFF, DATA_8, PARITY_OFF, 0, STOP_1, BAUD_115200);
	error = BSP_UART_activate(0);
	BSP_UART_printString(0,"Welcome to the uC GUI Test      \n\r");
	BSP_UART_printString(0,"Examples choosable with switches\n\r");
	BSP_UART_printString(0,"0 Draw Test Screen\n\r");
	BSP_UART_printString(0,"1 Color Palette Test\n\r");
	BSP_UART_printString(0,"Default Hello uC GUI\n\r\n\r\n\r");

	GUI_SetFont(&GUI_FontComic24B_1);
	while(1) {
		error = BSP_CARMEIO1_SWITCH_get(&test);
		switch(test) {

			case 0:
				drawTestScreen();
				break;
			case 1:
				i = 0;
				while (test == 1) {
					GUI_SetColor(colorInfoTable[i].color);
					GUI_FillRect(0, 0, GUI_GetScreenSizeX(), GUI_GetScreenSizeY());
					GUI_SetBkColor(colorInfoTable[i].color);
					GUI_SetColor(colorInfoTable[i].textColor);
					GUI_DispStringHCenterAt(colorInfoTable[i].name, (GUI_GetScreenSizeX() / 2), (GUI_GetScreenSizeY()/2 - 12));

					while((!pushButtonData) & (test == 1)) {
						error = BSP_CARMEIO1_BUTTON_get(&pushButtonData);
						error = BSP_CARMEIO1_SWITCH_get(&test);
					}
					i = buttonHandler(pushButtonData, i, 24);
					while(pushButtonData & (test == 1)) {
						error = BSP_CARMEIO1_BUTTON_get(&pushButtonData);
						error = BSP_CARMEIO1_SWITCH_get(&test);
					}
					error = BSP_CARMEIO1_SWITCH_get(&test);
					pushButtonData = 0;
				}
				GUI_SetBkColor(GUI_BLACK);

				break;
			case 2:
				i = 0;
				while (test == 2) {
					GUI_SetColor(colorInfoTable[i].color);
					GUI_FillRect(GUI_GetScreenSizeX() / 3, 0, 2* GUI_GetScreenSizeX() / 3, GUI_GetScreenSizeY());
					GUI_SetColor(colorInfoTable[i + 6].color);
					GUI_FillRect(0, 0, GUI_GetScreenSizeX() / 3, GUI_GetScreenSizeY());
					GUI_SetColor(colorInfoTable[i + 12].color);
					GUI_FillRect(2 * GUI_GetScreenSizeX() / 3, 0, GUI_GetScreenSizeX(), GUI_GetScreenSizeY());

					while((!pushButtonData) & (test == 2)) {
						error = BSP_CARMEIO1_BUTTON_get(&pushButtonData);
						error = BSP_CARMEIO1_SWITCH_get(&test);
					}
					i = buttonHandler(pushButtonData, i, 6);
					while(pushButtonData & (test == 2)) {
						error = BSP_CARMEIO1_BUTTON_get(&pushButtonData);
						error = BSP_CARMEIO1_SWITCH_get(&test);
					}
					error = BSP_CARMEIO1_SWITCH_get(&test);
					pushButtonData = 0;
				}
				break;
			case 4:
				GUI_SetColor(GUI_BLACK);
				GUI_FillRect(0, 0, GUI_GetScreenSizeX(), GUI_GetScreenSizeY());
				GUI_SetColor(GUI_WHITE);
				GUI_FillEllipse(GUI_GetScreenSizeX()/2, GUI_GetScreenSizeY()/2, 150, 60);
				GUI_SetColor(GUI_BLUE);
				GUI_FillCircle(GUI_GetScreenSizeX()/2, GUI_GetScreenSizeY()/2, 50);
				GUI_SetColor(GUI_BLACK);
				GUI_FillCircle(GUI_GetScreenSizeX()/2, GUI_GetScreenSizeY()/2, 25);

				break;

			case 8:
				GUI_DrawBitmap(&bmCARMEIDE, 46, 46);
				break;

			default:	// Pushbuttons-test
				GUI_SetColor(GUI_WHITE);
				GUI_DispStringHCenterAt("Hello uC Gui", (GUI_GetScreenSizeX() / 2), (GUI_GetScreenSizeY()/2 - 12));
				break;

		}
		while(!pushButtonData) {
			error = BSP_CARMEIO1_BUTTON_get(&pushButtonData);
		}
		while(pushButtonData) {
			error = BSP_CARMEIO1_BUTTON_get(&pushButtonData);
		}
		pushButtonData = 0;
		GUI_Clear();
	}
}

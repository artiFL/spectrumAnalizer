#include "menu.h"

typedef enum
{
	Button = 0,
	CheckBox,
	FloatValue,
	IntValue,
	ComboBox,
	PaletteBox
} eMenuItemTypeDef;

typedef struct
{
	char Str[30];
}
sComboItemTypeDef;

typedef struct
{
	char Title[40];
	eMenuItemTypeDef ItemType;

	// Параметры изменяемой числовой величины (IntValue, FloatValue)
	float Min;
	float Max;
	float EditStep;
	uint8_t DigitsAfterPoint;
	char Unit[10];

	// Строки выбираемых пунктов (в ComboBox)
	sComboItemTypeDef *ComboItems;
	uint8_t ComboItemsCount;

	// Изменяемое значение
	void *pValue;			// Указатель на изменяемое значение (для IntValue, FloatValue, ComboBox)

	// Action
	void (*Action) (void);	// Указатель на функцию пунктов меню, которые подразумевают действие (например, Button)
} sMenuItemtypeDef;

typedef struct
{
	uint16_t startX;
	uint16_t startY;
	uint16_t width;
	char Title[30];

	sMenuItemtypeDef *items;
	uint8_t itemsCount;
	uint8_t selectedItemIdx;
	uint8_t OnEdit;
} sMenuTypeDef;


static sMenuTypeDef Menu;
static uint8_t posY = 0;




void menu_build(void)
{
	Menu.itemsCount = 0;

	Menu.startX = 45;
	Menu.startY = 41;


}












void menu_render(void)
{

	menu_build();

	uint16_t start_x = Menu.startX;
	uint16_t start_y = Menu.startY;
	uint16_t end_x = TFTWIDTH - start_x;
	uint16_t end_y = TFTHEIGHT - start_y;

	draw_rectangle(start_x, start_y, end_x, end_y, GREEN);





















}


















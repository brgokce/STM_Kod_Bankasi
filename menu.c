#include "menu.h"
#include "main.h"
#include "stdio.h"


typedef enum
{
  Mode_RGB    = 0,
  Mode_RGBW   = 1,
  Mode_R_G_B  = 2,
} Modes;

Modes AddressMode;
typedef enum
{
  Test_RGB    = 0,
  Test_RGBW   = 1,
  Test_R_G_B  = 2,
  Test_RG_BW  = 3
}Test;

Test TestMode;

uint16_t Start_IC_Num = 0;
uint16_t End_IC_Num = 0;
uint16_t Start_Add_Num = 0;
uint16_t End_Add_Num = 0;
char buffer[16];
char * Cursor= "";
typedef void (*FuncPtr)(void);

FuncPtr FPtr; //function pointer

//Structure describes current menu and submenu state
struct Menu_State{
	 uint8_t menuNo;//1,2,3,4
	 uint8_t subMenuNo;//1,2,3
	 uint8_t subSubMenuNo;//1,2,3
}MN;

uint8_t menuLevel;
uint8_t Flag=1; //flag required for exiting from functions loops
uint8_t function_index = 0;
//Menu Strings in flash
const uint8_t MN000[] ="IKONETECH ADDRESS\0";
//menu 1
const uint8_t MN100[] ="ADDRESSING\0";
//menu 1 submenus
const uint8_t MN110[] ="START ADDR: ###\0";
const uint8_t MN120[] ="MODE    RGBW\0";
const uint8_t MN130[] ="WRITE ADDRESS\0";
//menu 2
const uint8_t MN200[] ="TEST MODE\0";
//Submenus of menu 2
const uint8_t MN210[] ="ANIMATION\0";
const uint8_t MN220[] ="CHASER CHANNEL\0";
const uint8_t MN230[] ="UNITARY CONTROL\0";
//Submenus of sub menu 2
const uint8_t MN211[] ="ANIMATION:\0";
const uint8_t MN212[] ="SPEED\0";
const uint8_t MN213[] ="STOP\0";

const uint8_t MN221[] ="CHASER CHANNEL\0";
const uint8_t MN222[] ="FIRST CH:\0";
const uint8_t MN223[] ="LAST CH:\0";
const uint8_t MN224[] ="DELAY: ###x10ms\0";
const uint8_t MN225[] ="STOP\0";

const uint8_t MN231[] ="UNITARY CONTROL\0";
const uint8_t MN232[] ="CHANNEL:\0";
const uint8_t MN233[] ="VALUE:\0";

//menu 3
const uint8_t MN300[] ="ABOUT\0";
//Submenus of menu 3
const uint8_t MN310[] ="ABOUT\0";
const uint8_t MN320[] ="IKONXTECH.COM\0";

//more menus and submenus can be added.
const uint8_t *MENU[] ={
		MN100,	//menu 1 string
		MN200,	//menu 2 string
		MN300,	//menu 3 string
		};
const uint8_t *SUBMENU[] ={
		MN110, MN120, MN130,	//submenus of menu 1              0 0 0
		MN210, MN220, MN230,			//submenus of menu 2      3 5 3
		MN310, MN320			//submenus of menu 3              0 0 0
		};

const uint8_t *SUBSUBMENU[] ={
		MN211, MN212, MN213,//SUB-submenus of menu 1
		MN221, MN222, MN223, MN224, MN225,	//submenus of menu 2
		MN231, MN232, MN233			        //submenus of menu 3
		};

//Menu structure
//[0] -Number of level 0 menu items
//[1]...[n] number of second level menu items
//Eg. MSTR2[1] shows that menu item 1 has 3 submenus
const uint8_t MSTR2[]  ={
	3,	//number of menu items
	3,	//Number of submenu items of menu item 1
	3,	//Number of submenu items of menu item 2
	2,	//Number of submenu items of menu item 3
	3,  //Number of subsubmenu items of submenu item 1
	5,	//Number of subsubmenu items of submenu item 2
	3   //Number of subsubmenu items of submenu item 3
	};

//Arrray of function pointers in Flash
const FuncPtr FuncPtrTable[]=
    { 		func110, func120, func130,	//functions for submenus of menu 1
    		func210, func220, func230, 			//functions for submenus of menu 2
    		func310
		};

//SubMenu and Function table pointer update
uint8_t MFIndex(uint8_t, uint8_t);

static void (*pf[])(void) ={func000,
		func100, func200, func300,
	func110, func120, func130,	//functions for submenus of menu 1
	func210, func220, func230, 			//functions for submenus of menu 2
	func310 			//functions for submenus of menu 3
	};

void call_menu_function(uint8_t const jump_index)
{
   //static void (*pf[])(void) = {fna, fnb, fnc, ..., fnz};
    if (jump_index < sizeof(pf) / sizeof(*pf))
    {
        /* Call the function specified by jump_index */
        pf[jump_index]();
    }
}

void menu_callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == SW3_EXTI_Pin) // Kesme ile kontrol etmek için kullandık
	  {
		 if(menuLevel==1)
		 {
			 MN.menuNo++;
			 call_main_menu();
		 }
		 else if(menuLevel==2)
		 {
			 MN.subMenuNo++;
			 call_sub_menu();
		 }
		 else if(menuLevel==3)
		 {
			 MN.subSubMenuNo++;
			 call_sub_sub_menu();
		 }
	  }
	else if(GPIO_Pin == SW2_EXTI_Pin) // Kesme ile kontrol etmek için kullandık
	{
		// Bulunduğu menünün alt menüsü varmı?
		//


		// Bulunduğu menünün alt menüsü varmı diye soruyoruz
		uint8_t found = 0;
		if(menuLevel==1){
			for(uint8_t i=0; i<sizeof(SUBMENU); i++){
				if(SUBMENU[i] == SUBMENU[MN.menuNo+10]){
					found = 1;
				}
				else{
					found = 0;
				}
			}
		}

		if(found==1){ // sileceğiz sadece kontrol için koyduk
			menuLevel++;
		}

		if(menuLevel==2)
		{
			call_sub_menu();
		}
		else if(menuLevel==3)
		{
			call_sub_sub_menu();
		}
	  }
	else if(GPIO_Pin == SW4_EXTI_Pin) // Kesme ile kontrol etmek için kullandık
	  {
		// Bulunduğu menünün alt menüsü varmı?
		//
		menuLevel--;
		if(menuLevel==1)
		{
			call_main_menu();
		}
		if(menuLevel==2)
		{
			call_sub_menu();
		}
		else if(menuLevel==3)
		{
			call_sub_sub_menu();
		}

	  }
}

void call_main_menu(void)
{
/* Seçme butonuna basıldığında
 * en üstteki menü ise o menüde ileri gidecek
 * sub menüde ise orada ileri gidecek
 * sub sub menüde ise orada gidecek
 */
		if (MN.menuNo==MSTR2[0]) // Değeri şuanda 3
		{
			MN.menuNo=0;
		}
		LCD_Clear();
		DWT_Delay_ms(10);
		LCD_Set_Cursor(1, 1);
		LCD_Write_String(">");
		LCD_Set_Cursor(1, 2);
		LCD_Write_String((char *)MENU[MN.menuNo]);
		LCD_Set_Cursor(2, 1);
		LCD_Write_String(" ");
		LCD_Set_Cursor(2, 2);
		if (MN.menuNo==MSTR2[0]-1) // Değeri şuanda 3
		{
			LCD_Write_String((char *)MENU[MN.menuNo-2]);
		}
		else
		{
			LCD_Write_String((char *)MENU[MN.menuNo+1]);
		}
		Flag=0;
}


void call_sub_menu(void)
{
  uint8_t eleman_sayisi = 0;// Her bir menüdeki eleman sayisi tutuluyor
  uint8_t submenu_indis = 0;// Her bir menüdeki eleman sayisi tutuluyor
   switch (MN.menuNo) {
	case 0:
		eleman_sayisi = 3; //MSTR2[0];
		submenu_indis=0;
		break;
	case 1:
		eleman_sayisi = 3; //MSTR2[1];
		submenu_indis=3;
		break;
	case 2:
		eleman_sayisi =2; //MSTR2[2];
		submenu_indis=6;
		break;
	default:
		eleman_sayisi =3;
		break;
   }

	if (MN.subMenuNo==eleman_sayisi) // Değeri şuanda 3
	{
		MN.subMenuNo=0;
	}
	LCD_Clear();
	DWT_Delay_ms(10);
	LCD_Set_Cursor(1, 1);
	LCD_Write_String(">");
	LCD_Set_Cursor(1, 2);
	LCD_Write_String((char *)SUBMENU[ submenu_indis+MN.subMenuNo]);
	LCD_Set_Cursor(2, 1);
	LCD_Write_String(" ");
	LCD_Set_Cursor(2, 2);
	if (MN.subMenuNo==eleman_sayisi-1) // Değeri şuanda 3
	{
		LCD_Write_String((char *)SUBMENU[submenu_indis+MN.subMenuNo-(eleman_sayisi-1)]);
	}
	else
	{
		LCD_Write_String((char *)SUBMENU[submenu_indis+MN.subMenuNo+1]);
	}

	Flag=0;
}
void call_sub_sub_menu(void)
{
	  uint8_t eleman_sayisi = 0;// Her bir menüdeki eleman sayisi tutuluyor
	  uint8_t subsubmenu_indis = 0;// Her bir menüdeki eleman sayisi tutuluyor
	   switch (MN.subMenuNo) {
		case 0:
			eleman_sayisi = 3; //MSTR2[0];
			subsubmenu_indis=0;
			break;
		case 1:
			eleman_sayisi = 5; //MSTR2[1];
			subsubmenu_indis=3;
			break;
		case 2:
			eleman_sayisi =3; //MSTR2[2];
			subsubmenu_indis=8;
			break;
		default:
			eleman_sayisi =3;
			break;
	   }

		if (MN.subSubMenuNo==eleman_sayisi) // Değeri şuanda 3
		{
			MN.subSubMenuNo=0;
		}
		LCD_Clear();
		DWT_Delay_ms(10);
		LCD_Set_Cursor(1, 1);
		LCD_Write_String(">");
		LCD_Set_Cursor(1, 2);
		LCD_Write_String((char *)SUBSUBMENU[subsubmenu_indis+MN.subSubMenuNo]);
		LCD_Set_Cursor(2, 1);
		LCD_Write_String(" ");
		LCD_Set_Cursor(2, 2);
		if (MN.subSubMenuNo==eleman_sayisi-1) // Değeri şuanda 3
		{
			LCD_Write_String((char *)SUBSUBMENU[subsubmenu_indis+MN.subSubMenuNo-(eleman_sayisi-1)]);
		}
		else
		{
			LCD_Write_String((char *)SUBSUBMENU[subsubmenu_indis+MN.subSubMenuNo+1]);
		}
		Flag=0;

}

void menu_Init(void)
{
	LCD_Clear();
	DWT_Delay_ms(10);
 //   DWT_Delay_ms(10);
    menuLevel = 1;
 	MN.menuNo=0;
	MN.subMenuNo=0;
	MN.subSubMenuNo=0;
	LCD_Clear();
	DWT_Delay_ms(10);
    //Display menu item
    LCD_Set_Cursor(1, 1);
    LCD_Write_String(">");
    LCD_Set_Cursor(1, 2);
    LCD_Write_String((char *)MENU[MN.menuNo]);
    LCD_Set_Cursor(2, 1);
    LCD_Write_String(" ");
    LCD_Set_Cursor(2, 2);
    LCD_Write_String((char *)MENU[(MN.menuNo+1)]);
  //  LCD_Write_String((char *)SUBMENU[(MN.menuNo+1)]);
  //  LCD_Write_String((char *)SUBSUBMENU[(MN.menuNo+1)]);
//    LCD_Set_Cursor(2, 1);
//        LCD_Write_String((char *)SUBSUBMENU[(MN.subSubMenuNo)]);
    //Assign function to function pointer
	// FPtr=(FuncPtr)&FuncPtrTable[0];
   // (FuncPtr)&pf[0];
}

uint8_t MFIndex(uint8_t mn, uint8_t sb)
{
	uint8_t p=0;//points to menu in table of function pointer 
	for(uint8_t i=0; i<(mn-1); i++)
	{
		p=p+MSTR2[i+1];
	}
	p=p+sb-1;
	return p;
}

void func000(void)
{
//	LCD_Clear();
//	AddressMode = Mode_RGB;
//	while(Flag)
//	{
		DWT_Delay_ms(50);
		 //Display menu item
		 LCD_Set_Cursor(1, 1);
		 LCD_Write_String((char *)MENU[MN.menuNo]);
		 LCD_Set_Cursor(2, 1);
		 LCD_Write_String((char *)MENU[MN.menuNo+1]);
		 DWT_Delay_ms(10);
//	}
}

void func100(void)
{ }

void func200(void)
{ }
void func300(void)
{ }

void func110(void)
{
	LCD_Clear();
	AddressMode = Mode_RGB;
	while(Flag)
	{
		DWT_Delay_ms(50);
		 //Display menu item
		 LCD_Set_Cursor(1, 1);
		 LCD_Write_String((char *)MENU[MN.menuNo-1]);
		 DWT_Delay_ms(10);
		 //Display submenu item
		 LCD_Set_Cursor(2, 1);
		 LCD_Write_String("MODE: RGB");
	}
}
void func120(void)
{
	LCD_Clear();
	AddressMode = Mode_RGBW;
	while(Flag)
	{
		DWT_Delay_ms(50);
		//Display menu item
		LCD_Set_Cursor(1, 1);
		LCD_Write_String((char *)MENU[MN.menuNo-1]);
		DWT_Delay_ms(10);
		//Display submenu item
		LCD_Set_Cursor(2, 1);
		LCD_Write_String("MODE: RGBW");
		//DWT_Delay_ms(10);
	}
}
void func130(void)
{
	LCD_Clear();
	AddressMode = Mode_R_G_B;
	while(Flag)
	{
			 DWT_Delay_ms(50);
			 //Display menu item
			 LCD_Set_Cursor(1, 1);
			 LCD_Write_String((char *)MENU[MN.menuNo-1]);
			 //DWT_Delay_ms(10);
			 //Display submenu item
			 LCD_Set_Cursor(2, 1);
			 LCD_Write_String("MODE: R, G, B");
	}
}
void func210(void)
{
	LCD_Clear();
	sprintf(buffer, "Start IC N:%d", Start_IC_Num);
	 DWT_Delay_ms(50);
	 //Display menu item
	 LCD_Set_Cursor(1, 1);
	 LCD_Write_String((char *)MENU[MN.menuNo-1]);
	 //DWT_Delay_ms(10);
	 //Display submenu item
	 LCD_Set_Cursor(2, 1);
	 LCD_Write_String(buffer);

	while(Flag)
	{
//		 if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == GPIO_PIN_SET) // Kesme ile kontrol etmek için kullandık
//		  {
//			 Start_IC_Num++;
//			sprintf(buffer, "Start IC N:%d", Start_IC_Num);
//			 DWT_Delay_ms(50);
//			 //Display menu item
//			 LCD_Set_Cursor(1, 1);
//			 LCD_Write_String((char *)MENU[MN.menuNo-1]);
//			 //DWT_Delay_ms(10);
//			 //Display submenu item
//			 LCD_Set_Cursor(2, 1);
//			 LCD_Write_String(buffer);
//		  }
//		 else if (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin) == GPIO_PIN_SET)// Kesme ile kontrol etmek için kullandık
//		  {
//			 Start_IC_Num--;
//			sprintf(buffer, "Start IC N:%d", Start_IC_Num);
//			 DWT_Delay_ms(50);
//			 //Display menu item
//			 LCD_Set_Cursor(1, 1);
//			 LCD_Write_String((char *)MENU[MN.menuNo-1]);
//			 //DWT_Delay_ms(10);
//			 //Display submenu item
//			 LCD_Set_Cursor(2, 1);
//			 LCD_Write_String(buffer);
//		  }


	}
}
void func220(void)
{
	LCD_Clear();
	while(Flag)
	{
//			 DWT_Delay_ms(50);
//			 //Display menu item
//			 LCD_Set_Cursor(1, 1);
//			 LCD_Write_String((char *)MENU[MN.menuNo-1]);
//			 //DWT_Delay_ms(10);
//			 //Display submenu item
//			 LCD_Set_Cursor(2, 1);
//			 LCD_Write_String("FUNCTION 202");
	}
}

void func230(void)
{
	LCD_Clear();
	while(Flag)
	{	}
}
void func310(void)
{
	LCD_Clear();
	while(Flag)
	{
			 DWT_Delay_ms(50);
			 //Display menu item
			 LCD_Set_Cursor(1, 1);
			 LCD_Write_String((char *)MENU[MN.menuNo-1]);
			 //DWT_Delay_ms(10);
			 //Display submenu item
			 LCD_Set_Cursor(2, 1);
			 LCD_Write_String("FUNCTION 310");
	}
}


#include "menu.h"


typedef void (*FuncPtr)(void);
FuncPtr FPtr; //function pointer

//Structure describes current menu and submenu state
struct Menu_State{
	 uint8_t menuNo;//1,2,3,4
	 uint8_t subMenuNo;//1,2,3
}MN;

uint8_t Flag=1; //flag required for exiting from functions loops
uint8_t function_index = 0;
//Menu Strings in flash
const uint8_t MN000[] ="IKONX ADDRESS\0";
//menu 1
const uint8_t MN100[] =" Color\0";
//menu 1 submenus
const uint8_t MN101[] =" R ON\0";
const uint8_t MN102[] =" G ON\0";
const uint8_t MN103[] =" B ON\0";
//menu 2
const uint8_t MN200[] =" StartChannel\0";
//Submenus of menu 2
const uint8_t MN201[] =" NUM:\0";
const uint8_t MN202[] =" NMN:\0";
//menu 3
const uint8_t MN300[] =" Mode\0";
//Submenus of menu 3
const uint8_t MN301[] =" RGB\0";
const uint8_t MN302[] =" RGBW\0";
//menu 4
const uint8_t MN400[] =" Speed\0";
//submenus of menu 4
const uint8_t MN401[] =" Fast\0";
const uint8_t MN402[] =" Slow\0";
//more menus and submenus can be added.
//Arrays of pointers to menu strings stored in flash
const uint8_t *MENU[] ={
		MN100,	//menu 1 string
		MN200,	//menu 2 string
		MN300,	//menu 3 string
		MN400	//menu 4 string
		};
const uint8_t *SUBMENU[] ={
		MN101, MN102, MN103,	//submenus of menu 1
		MN201, MN202,			//submenus of menu 2
		MN301, MN302,			//submenus of menu 3
		MN401, MN402			//submenus of menu 4
		};

//Menu structure
//[0] -Number of level 0 menu items
//[1]...[n] number of second level menu items
//Eg. MSTR2[1] shows that menu item 1 has 3 submenus
const uint8_t MSTR2[]  ={
	4,	//number of menu items
	3,	//Number of submenu items of menu item 1
	2,	//of menu item 2
	2,	//of menu item 3
	2	//of menu item 4
	};

//Arrray of function pointers in Flash
const FuncPtr FuncPtrTable[]=
    { 	func101, func102, func103,	//functions for submenus of menu 1
		func201, func202, 			//functions for submenus of menu 2
		func301, func302, 			//functions for submenus of menu 3
		func401, func402			//functions for submenus of menu 4
		};

//SubMenu and Function table pointer update
uint8_t MFIndex(uint8_t, uint8_t);

static void (*pf[])(void) ={
	func101, func102, func103,	//functions for submenus of menu 1
	func201, func202, 			//functions for submenus of menu 2
	func301, func302, 			//functions for submenus of menu 3
	func401, func402			//functions for submenus of menu 4
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
	//if button UP pressed
   // if(HAL_GPIO_ReadPin(BUTON1_GPIO_Port, BUTON1_Pin)==GPIO_PIN_SET) // bu kodu while içinden çağırmak için kullan
//      if(GPIO_Pin == SW2_EXTI_Pin) // Kesme ile kontrol etmek için kullandık
//	  {
//		if (MN.menuNo==MSTR2[0])
//		{
//			MN.menuNo++;
//			MN.subMenuNo=1;
//		}
//		else
//		{
//			MN.menuNo=1;
//		}
//		LCD_Clear();
//		DWT_Delay_ms(10);
//		//Display menu item
//		 LCD_Set_Cursor(1, 1);
//		 LCD_Write_String((char *)MENU[MN.menuNo-1]);
//		//Display submenu item
//		 LCD_Set_Cursor(2, 1);
//		 LCD_Write_String((char *)SUBMENU[MFIndex(MN.menuNo, MN.subMenuNo)]);
//		//Assign function to function pointer
//	    //FPtr=(FuncPtr)&FuncPtrTable[MFIndex(MN.menuNo, MN.subMenuNo)];
//		 //call_menu_function(MFIndex(MN.menuNo, MN.subMenuNo));
//		 function_index = MFIndex(MN.menuNo, MN.subMenuNo);
//
//		//set Flag to 0 means menu have changed
//		Flag=0;
//		//wait for button release
//	//	while(HAL_GPIO_ReadPin(SW2_EXTI_GPIO_Port, SW2_EXTI_Pin)==GPIO_PIN_SET);
//	  }
	//if Button DOWN pressed
	 // if(HAL_GPIO_ReadPin(BUTON2_GPIO_Port, BUTON2_Pin)==GPIO_PIN_SET)
	  if(GPIO_Pin == SW3_EXTI_Pin) // Kesme ile kontrol etmek için kullandık
	  {
		if (MN.menuNo==1)
		{ 
			MN.menuNo=MSTR2[0];
			MN.subMenuNo=1;
		}
		else
		{
			MN.menuNo--;
		}
	 LCD_Clear();
	 DWT_Delay_ms(10);
	 //Display menu item
	 LCD_Set_Cursor(1, 1);
	 LCD_Write_String((char *)MENU[MN.menuNo-1]);
	 //Display submenu item
	 LCD_Set_Cursor(2, 1);
	 LCD_Write_String((char *)SUBMENU[MFIndex(MN.menuNo, MN.subMenuNo)]);
	 //Assign function to function pointer
	 //FPtr=(FuncPtr)&FuncPtrTable[MFIndex(MN.menuNo, MN.subMenuNo)];
	// call_menu_function(MFIndex(MN.menuNo, MN.subMenuNo));
	 function_index = MFIndex(MN.menuNo, MN.subMenuNo);
	 Flag=0;
//	 while(HAL_GPIO_ReadPin(SW3_EXTI_GPIO_Port, SW3_EXTI_Pin)==GPIO_PIN_SET);
	}
	//If Button RIGHT pressed
	  //if Button DOWN pressed
	  //if(HAL_GPIO_ReadPin(BUTON3_GPIO_Port, BUTON3_Pin)==GPIO_PIN_SET)
	  //---------------------------------
	  //---------------------------------
	  // Bu kısım alt menü tanımlaması içindir. Kullanmadığımız için kapattık
/*
	  if(GPIO_Pin == SW4_EXTI_Pin) // Kesme ile kontrol etmek için kullandık
	  {
		if (MN.subMenuNo==MSTR2[MN.menuNo])
		{ 
			MN.subMenuNo++;
		}
		else
		{
			MN.subMenuNo=1;
		}
		LCD_Clear();
		//Display menu item
		LCD_Set_Cursor(1, 1);
		LCD_Write_String((char *)MENU[MN.menuNo-1]);
		//Display submenu item
		LCD_Set_Cursor(2, 1);
		LCD_Write_String((char *)SUBMENU[MFIndex(MN.menuNo, MN.subMenuNo)]);
		//Assign function to function pointer
		//FPtr=(FuncPtr)FuncPtrTable[MFIndex(MN.menuNo, MN.subMenuNo)];
		call_menu_function(MFIndex(MN.menuNo, MN.subMenuNo));
		Flag=0;
	//	while(HAL_GPIO_ReadPin(SW4_EXTI_GPIO_Port, SW4_EXTI_Pin)==GPIO_PIN_SET);
	}
	//If button LEFT pressed
	 // if(HAL_GPIO_ReadPin(BUTON4_GPIO_Port, BUTON4_Pin)==GPIO_PIN_SET)
	  if(GPIO_Pin == SW5_EXTI_Pin) // Kesme ile kontrol etmek için kullandık
	  {
		if (MN.subMenuNo==1)
		{ 
			MN.subMenuNo=MSTR2[MN.menuNo];
		}
		else
		{
			MN.subMenuNo--;
		}
	 LCD_Clear();
	 //Display menu item
	 LCD_Set_Cursor(1, 1);
	 LCD_Write_String((char *)MENU[MN.menuNo-1]);
	 //Display submenu item
	 LCD_Set_Cursor(2, 1);
	 LCD_Write_String((char *)SUBMENU[MFIndex(MN.menuNo, MN.subMenuNo)]);
	 //Assign function to function pointer
	 //FPtr=(FuncPtr)&FuncPtrTable[MFIndex(MN.menuNo, MN.subMenuNo)];
	 call_menu_function(MFIndex(MN.menuNo, MN.subMenuNo));
	 Flag=0;
	// while(HAL_GPIO_ReadPin(SW5_EXTI_GPIO_Port, SW5_EXTI_Pin)==GPIO_PIN_SET);
	}
		Flag=1;
		//execute function that is pointed by FPtr
//		FPtr();
 *
*/
//-------------------- Alt menü Sonu
}

//int mainxx(void)
//{
////	LCDinit();
////	LCDclr();
////	LCDhome();
//	//Welcome demo message
//
//
//	//Initial menu and initial function
//
//
////	while(1)
////	{
////	//set flag to 1
////	//when button menu changes flag sets to 0
////	Flag=1;
////	//execute function that is pointed by FPtr
////	FPtr();
////	}
////	return 0;
//}

void menu_Init(void)
{
	LCD_Clear();
    //Display menu item
	DWT_Delay_ms(10);
	LCD_Set_Cursor(1, 1);
    LCD_Write_String((char *)MN000);
    DWT_Delay_ms(10);
 	MN.menuNo=1;
	MN.subMenuNo=1;
	LCD_Clear();
	DWT_Delay_ms(10);
    //Display menu item
    LCD_Set_Cursor(1, 1);
    LCD_Write_String((char *)MENU[MN.menuNo-1]);
    //Display submenu item
    LCD_Set_Cursor(2, 1);
    LCD_Write_String((char *)SUBMENU[(MN.subMenuNo-1)]);
    //Assign function to function pointer
	FPtr=(FuncPtr)&FuncPtrTable[0];
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

void func101(void)
{
	while(Flag)
	{
		// LCD_Clear();
			 DWT_Delay_ms(10);
			 //Display menu item
			 LCD_Set_Cursor(1, 1);
			 LCD_Write_String((char *)MENU[MN.menuNo-1]);
			    DWT_Delay_ms(10);

			 //Display submenu item
			 LCD_Set_Cursor(2, 1);
			 LCD_Write_String("FUNCTION 101");
			    DWT_Delay_ms(10);

	}
}
void func102(void)
{

}
void func103(void)
{

}
void func201(void)
{
	while(Flag)
	{
		while(Flag)
		{
			// LCD_Clear();
				 DWT_Delay_ms(10);
				 //Display menu item
				 LCD_Set_Cursor(1, 1);
				 LCD_Write_String((char *)MENU[MN.menuNo-1]);
				 //Display submenu item
				 LCD_Set_Cursor(2, 1);
				 LCD_Write_String("FUNCTION 201");
		}
	}
}
void func202(void)
{

}
void func301(void)
{
	while(Flag)
	{
		while(Flag)
		{
			// LCD_Clear();
				 DWT_Delay_ms(10);
				 //Display menu item
				 LCD_Set_Cursor(1, 1);
				 LCD_Write_String((char *)MENU[MN.menuNo-1]);
				 //Display submenu item
				 LCD_Set_Cursor(2, 1);
				 LCD_Write_String("FUNCTION 301");
		}
	}
}
void func302(void)
{

}
void func401(void)
{
	while(Flag)
	{
		while(Flag)
		{
			// LCD_Clear();
				 DWT_Delay_ms(10);
				 //Display menu item
				 LCD_Set_Cursor(1, 1);
				 LCD_Write_String((char *)MENU[MN.menuNo-1]);
				 //Display submenu item
				 LCD_Set_Cursor(2, 1);
				 LCD_Write_String("FUNCTION 401");
		}
	}
}
void func402(void)
{

}

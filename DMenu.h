/*
 * MenuLCD.h
 *
 *  Created on: 02/set/2013
 *      Author: dury
 */

#ifndef DMENU_H_
#define DMENU_H_

#define DMENU_ACTION_SELECT 1
#define DMENU_ACTION_BACK 2

//#include "mbed.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "wiring.h"
	#include "WProgram.h"
#endif


#ifndef BYTE
	typedef unsigned char BYTE;
#endif

#define DEFAULT_MAX_ITEM_TEXT_LEN 21
#define MAX_ID 32768

class DMenu {
	public:
		typedef void (*DMenuListener) (DMenu *MenuItem, BYTE Action);
		DMenu(const char MenuItemName[], DMenuListener CallbackFunc, DMenu *Parent);
		~DMenu();
		void SetName(const char ItemName[]);
		DMenu* AddItem(const char Name[]);
		DMenu* Up(void);
		DMenu* Down(void);
		DMenu* Back(void);
		void Select(void);

		DMenu* GetCurrItem(void);
		short int GetItemsCount(void);
		const char* GetName(void);
		short int GetID(void);


	private:
		DMenuListener Callback;
		char* Name;
		DMenu *Parent;
		DMenu *CurrItem;
		short int ItemIndex; //! Index used to handle the current selected Item
		short int ItemsCount;
		short int ID;
		BYTE MaxItemTextLen;
		DMenu** Items;
		// TODO: bool Loop;
};

#endif /* MENULCD_H_ */

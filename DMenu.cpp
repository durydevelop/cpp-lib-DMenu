/*
 * MenuLCD.cpp
 *
 *  Created on: 02/set/2013
 *      Author: dury
 */

#include "DMenu.h"

//! Contructor
/**
 * @param MenuItemName	->	name of new Menu Item
 * @param CallbackFunc	->	pointer to the DMenuListener function that will be called on Select() or Back() call
 * @param ParentItem	->	pointer to the parent Item of the new one. If parameter is NULL the Menu Item is the root one and Back() does't fire the Callback
 */
DMenu::DMenu(const char MenuItemName[], DMenuListener CallbackFunc, DMenu *ParentItem)
{
	Callback=CallbackFunc;
	Parent=ParentItem;
	ID=100;
	ItemIndex=-1;
	ItemsCount=0;
	MaxItemTextLen=DEFAULT_MAX_ITEM_TEXT_LEN;
	SetName(MenuItemName);
	CurrItem=nullptr;
}

//! Destructor
DMenu::~DMenu()
{
	// free all created Items
	/*
	if (Items.size() > 0) {
		for (unsigned int ixI=0;ixI<Items.size();ixI++) {
			delete Items.at(ixI);
		}
		Items.clear();
	}
	*/
}

//! Set the name of Item.
/**
 * @param new name of this Item.
 *
 * N.B. The Name will be truncated to MaxItenTextLen value
 */
void DMenu::SetName(const char ItemName[])
{
	Serial.println(ItemName);
	strncpy(Name,ItemName,MaxItemTextLen);
}

//! Add a new Item to menu
/** The item is added to the end
 * @param ItemName	->	Name of Item
 *
 * @return a pointer to new Item
 */
DMenu* DMenu::AddItem(const char ItemName[])
{
		if (ItemsCount == 0) {
			// No Items yet
			// Allocate first DMenu pointer
			Items=(DMenu **) malloc(sizeof(DMenu*));
			if (Items == NULL) {
				return nullptr;
			}
		}
		else {
			// Items alreay present
			// try to allocate an other DMenu pointer
			DMenu **tmp=(DMenu **) realloc(Items,sizeof(DMenu*)*(ItemsCount+1));
			if (tmp == NULL) {
				return 0;
			}
			Items=tmp;
		}

		// Create new DMenu and assign it to last array pointer
		Items[ItemsCount]=new DMenu(ItemName,Callback,this);
		// Inc items counter
		ItemsCount++;
		return(Items[ItemsCount]);
}

//! Add a list of Items
/** The items are added to the end
 * @param Names	->	a vector of string containing the name of items to create
 *
 * @return a pointer to new Item
 */
/*
short int DMenu::AddItems(vector<string> Names)
{
	for (unsigned short int ixN=0;ixN<Names.size();ixN++) {
		DMenu *Item=new DMenu(Names.at(ixN),Callback,this);
		Items.push_back(Item);
	}
	return(Items.size());
}
*/

//! @return current selected Item inside this
DMenu* DMenu::GetCurrItem(void)
{
	return(CurrItem);
}

//! Change current selected Item to previous one
/**
 * @return	->	a pointer to new current selected Item
 */
DMenu* DMenu::Up(void)
{
	if (ItemIndex > 0) ItemIndex--;
	return(Items[ItemIndex]);
}

//! Change current selected Item to next one
/**
 * @return	->	a pointer to new current selected Item
 */
DMenu* DMenu::Down(void)
{
	if ((unsigned short int) ItemIndex < (ItemsCount-1)) ItemIndex++;
	return(Items[ItemIndex]);
}

//! @return the Parent Item of this
/**
 * If this have a Parent Item, Calling Back() will also fire a Callback event passing the Parent Item as argument, otherwise return NULL.
 */
DMenu* DMenu::Back(void)
{
	if (Parent != NULL) {
		Callback(Parent,DMENU_ACTION_BACK);
	}
	return(Parent);
}

//! Fire a Callback event sending the current selected Item as argument
/**
 * N.B. Callback will be called only if there is a selected Item.
 */
void DMenu::Select(void)
{
	if (CurrItem != NULL) {
		Callback(CurrItem,DMENU_ACTION_SELECT);
	}
}

//! @return name string of this Item
const char* DMenu::GetName(void)
{
	return(Name);
}

//! @return ID of this Item
short int DMenu::GetID(void)
{
	return(ID);
}

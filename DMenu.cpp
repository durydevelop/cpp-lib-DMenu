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
	if (ParentItem == NULL) {
        Parent=this;
	}
	else {
        Parent=ParentItem;
	}
	ID=rand();
	ItemIndex=-1;
	ItemsCount=0;
	Loop=false;
	MaxItemTextLen=DEFAULT_MAX_ITEM_TEXT_LEN;
	Name=NULL;
	SetName(MenuItemName);
}

//! Destructor
DMenu::~DMenu()
{
	// free all created Items
	if (ItemsCount > 0) {
		for (short int ixI=0;ixI<ItemsCount;ixI++) {
			delete Items[ixI];
		}
		free(Items);
	}
}

//! Set the name of Item.
/**
 * @param new name of this Item.
 *
 * N.B. The Name will be truncated to MaxItenTextLen value
 */
void DMenu::SetName(const char ItemName[])
{
    size_t len=strlen(ItemName);
	if (len > MaxItemTextLen) {
        len=MaxItemTextLen;
	}
	if (Name == NULL) {
        Name=new char[len+1];
    }
	strncpy(Name,ItemName,len);
	Name[len]='\0';
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
				return NULL;
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
		DMenu *NewItem=new DMenu(ItemName,Callback,this);
		Items[ItemsCount]=NewItem;
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
	if (ItemIndex == -1) {
        return(this);
	}
	return(Items[ItemIndex]);
}

//! Change current selected Item to previous one
/**
 * @return	->	a pointer to new current selected Item
 */
DMenu* DMenu::Up(void)
{
	if (ItemsCount == 0) {
        return(this);
	}

	if (ItemIndex == -1) {
        ItemIndex=0;
	}
	else if (ItemIndex == 0) {
		if (Loop) {
			ItemIndex=ItemsCount-1;
		}
	}
	else if (ItemIndex > 0) {
            ItemIndex--;
	}

	return(Items[ItemIndex]);
}

//! Change current selected Item to next one
/**
 * @return	->	a pointer to new current selected Item
 */
DMenu* DMenu::Down(void)
{
	if (ItemsCount == 0) {
        return(this);
	}

	if (ItemIndex == -1) {
        ItemIndex=ItemsCount-1;
	}
	else if (ItemIndex == ItemsCount-1) {
		if (Loop) {
			ItemIndex=0;
		}
	}
	else if (ItemIndex < ItemsCount-1) {
        ItemIndex++;
	}

	return(Items[ItemIndex]);
}

//! @return the Parent Item of this
/**
 * If this have a Parent Item, Calling Back() will also fire a Callback event passing the Parent Item as argument, otherwise return NULL.
 */
DMenu* DMenu::Back(void)
{
	if (Parent != this) {
		if (Callback != NULL) {
            Callback(Parent,DMENU_ACTION_BACK);
		}
	}
	return(Parent);
}

//! Fire a Callback event sending the current selected Item as argument
/**
 * N.B. Callback will be called only if there is a selected Item.
 */
DMenu* DMenu::Select(void)
{
	if (ItemIndex == -1) {
		return(this);
	}

    if (Callback != NULL) {
    	Callback(Items[ItemIndex],DMENU_ACTION_SELECT);
    }

	return (Items[ItemIndex]);
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

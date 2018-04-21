# DMenu class to easy create menu structure

***
DMenu is a class to rappresent a single node menu structure in memory. You can create separate menu but they can be nested to create complex menu.
***
#### Specifications

It is written in standard C++ to maximize compatibility with most of compiling toolchains specially for embedded micro contoller systems.

Each menu item cab be a "sub-menu container" or an "action executer".

You can associate a callback function to call when an action is executed (es to run it in separate thread).

It works like a virtual rappresentation of a menu, so, You can print it using printing api of your compiling environment.

#### How to use:

- Widhout callback:

```C++
DMenu *Menu=new DMenu("MainPage");
short id1=Menu->AddItem("Item1",true);
short id2=Menu->AddItem("Item2");

    wchar_t ch;
    do {
        PrintMenu(Menu);
        ch=getch();
        switch (ch) {
            case KEY_UP:
                Item=CurrItem->Up();
                break;
            case KEY_DOWN:
                Item=CurrItem->Down();
                break;
            case KEY_LEFT:
                Item=CurrItem->Back();
                CurrItem=Item;
                break;
            case KEY_RIGHT:
            case KEY_ENTER:
                Item=CurrItem->Select();
                if (Item->GetID() == ID_DIAG_WHEELS) WheelsDiag();
                break;
            case KEY_BACKSPACE:
                return;
            default:
                break;
        }
    }while(ch != 'q');
    

short ID_DIAG_WHEELS;
short ID_DIAG_HEAD;
short ID_DIAG_CAMERA;
short ID_DIAG_IO;

    DMenu *Menu=new DMenu("MainPage",MenuAction);
    ID_DIAG_WHEELS=Menu->AddItem("Wheels Diag",true);
    ID_DIAG_HEAD=Menu->AddItem("Head Diag");
    ID_DIAG_IO=Menu->AddItem("I/O Diag");

    WINDOW *wMenu=newwin(10,20,10,10);
    keypad(wMenu,true);
    //wbkgd(wMenu,COLOR_PAIR(COLOR_BLUE));
    box(wMenu,ACS_VLINE,ACS_HLINE);
    //wrefresh(wMenu);
    //PrintMenu(wMenu,Menu);

    DMenu *CurrItem=Menu;
    DMenu *Item;
    wchar_t ch;
    do {
        PrintMennu(wMenu,Menu);
        ch=wgetch(wMenu);
        switch (ch) {
            case KEY_UP:
                Item=CurrItem->Up();
                break;
            case KEY_DOWN:
                Item=CurrItem->Down();
                break;
            case KEY_LEFT:
                Item=CurrItem->Back();
                CurrItem=Item;
                break;
            case KEY_RIGHT:
            case KEY_ENTER:
                Item=CurrItem->Select();
                if (Item->GetID() == ID_DIAG_WHEELS) WheelsDiag();
                break;
            case KEY_BACKSPACE:
                return;
            default:
                break;
        }
    }while(ch != 'q');

    delwin(wMenu);
    delete Menu;
    ncursesEnd();
}
```

```C++
void MenuAction(DMenu *MenuItem, BYTE Action)
{
    if (MenuItem != NULL) {
        switch (Action) {
            case DMENU_ACTION_SELECT:
                //Log.i("Selected on: %s",MenuItem->GetName());
                //if (MenuItem->GetID() == ID_DIAG_WHEELS) WheelsDiag();
                //else if (MenuItem->GetID() == ID_DIAG_HEAD) HeadDiag();
                break;
            case DMENU_ACTION_BACK:
                // Redraw prev Menu
                //Log.i("Back to: %s",MenuItem->GetName());
                break;
            case DMENU_ACTION_UP:
                // Update Menu draw
                //Log.i("Up to: %s",MenuItem->GetName());
                break;
            case DMENU_ACTION_DOWN:
                // Update Menu draw
                //Log.i("Down to: %s",MenuItem->GetName());
                break;
        }
    }
}
```
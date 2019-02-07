short ID_DIAG_WHEELS=0;
short ID_DIAG_HEAD=0;
short ID_DIAG_CAMERA=0;
short ID_DIAG_IO=0;
void Diagnostic(void)
{
    DMenu *Menu;
    Menu=new DMenu("MainPage");
    ID_DIAG_WHEELS=Menu->AddItem("Wheels Diag",true);
    ID_DIAG_HEAD=Menu->AddItem("Head Diag");
    ID_DIAG_IO=Menu->AddItem("I/O Diag");


    DNCurses::DWindow *wMenu=nc.CreateWindow(2,2,10,20);
    wMenu->AddBox();
    wMenu->Update();

    DMenu *CurrItem=Menu;
    DMenu *Item;
    wchar_t ch;
    do {
        PrintMenu(wMenu,CurrItem);
        ch=wMenu->Getch();
        switch (ch) {
            case KEY_UP:
                Item=CurrItem->Up();
                break;
            case KEY_DOWN:
                Item=CurrItem->Down();
                break;
            case KEY_LEFT:
                Item=CurrItem->Back();
                if (CurrItem->GetID() == ID_DIAG_HEAD) {
                    delete CurrItem;
                }
                CurrItem=Item;
                break;
            case KEY_RIGHT:
            case KEY_ENTER:
                Item=CurrItem->Select();
                if (Item->GetID() == ID_DIAG_WHEELS) {
                    WheelsDiag(&Wheels,&nc);
                }
                else if (Item->GetID() == ID_DIAG_HEAD) {
                    HeadDiag(&ServoPan,&ServoTilt,&nc);
                }
                break;
            case KEY_BACKSPACE:
                return;
            default:
                break;
        }
    }while(ch != 'q');

    delete Menu;
}

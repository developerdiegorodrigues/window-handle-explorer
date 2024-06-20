#include <windows.h>
#include <commctrl.h>

//-------------------------------------------------->>
// Geral
#define TITULO				"Window Handle Explorer"
#define MAINCLASSNAME		"WindowHandleExplorerClass" // Não ultrapassar 32 caracteres
#define JANELA_LARGURA		800
#define JANELA_ALTURA		600
#define ID_TIMER_MOUSE		200
#define TIMER_MOUSE_TIME	500

// Controles (Separados por tipo de fonte !!)
#define STATUS_BAR				1
#define SYS_TREE_VIEW_MAIN		2
#define BUTTON_TOTAL			3
#define EDIT_SEARCH				4
#define BUTTON_SEARCH			5
#define BUTTON_SHOW_HIDE		6
#define EDIT_RECT_A				7
#define EDIT_RECT_B				8
#define EDIT_RECT_C				9
#define EDIT_RECT_D				10
#define EDIT_NEW_TEXT			11
#define BUTTON_SEND_TEXT		12
#define COMBO_BOX_MESSAGE		13
#define COMBO_BOX_PARAMS		14
#define EDIT_LPARAM				15
#define EDIT_WPARAM				16
#define BUTTON_SEND_MESSAGE		17
#define EDIT_DATA				18

#define BUTTON_MOVER			100
#define BUTTON_REDEFINIR		101

//-------------------------------------------------->>
extern HWND hwndMain, hwndTreeView, hwndTarget;
extern HINSTANCE hInstance;
extern char textToSearch[256];
extern RECT targetOldRect;
//-------------------------------------------------->>
extern void wm_create(HWND);
extern void wm_size(void);
extern void wm_command(HWND, WPARAM, LPARAM);
extern void wm_notify(HWND, WPARAM, LPARAM);
extern void wm_timer(WPARAM);
extern void error(LPSTR, bool);
extern void info(LPSTR);
extern HTREEITEM AddTreeViewItem(HTREEITEM, const char*, HWND hWnd);
extern void FillTreeView(HWND, HTREEITEM);
extern void CreateControlsHierarchy();
extern void disableControls();
extern void enableControls();
extern void statusBarMousePos();
extern void sendTargetMessage();
extern void changeSubMessageControls(bool);
extern void validWindow(bool, LPSTR);
//-------------------------------------------------->>






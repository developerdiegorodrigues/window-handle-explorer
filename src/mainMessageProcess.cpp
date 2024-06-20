/*
TODO:
- Alterar visibilidade do controle alvo [x]
- Mover controle alvo [x]
- Limitar quantidade de caracteres EDIT_SEARCH [x]
- Alterar texto do controle alvo [x]
*/

#include "resource.h"

HWND hwndTreeView, hwndTarget=NULL;
char textToSearch[256];
RECT targetOldRect;
//-------------------------------------------------->
void wm_create(HWND hwnd) {
	RECT rect;
	HFONT hfontTahoma16, hWingDings20;
		
	if(!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "msctls_statusbar32", NULL,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwnd, (HMENU) STATUS_BAR, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx STATUS_BAR!\t", true);
	
	if (!(hwndTreeView = CreateWindowEx(
	    WS_EX_WINDOWEDGE, "SysTreeView32", "TreeView",
	    WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_INFOTIP | TVS_FULLROWSELECT | TVS_SHOWSELALWAYS,
	    0, 0, 0, 0, hwnd, (HMENU) SYS_TREE_VIEW_MAIN, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx SYS_TREE_VIEW_MAIN!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Integral",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_TOTAL, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx BUTTON_TOTAL!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_SEARCH, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_SEARCH!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Pesquisa",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_SEARCH, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx BUTTON_SEARCH!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Ocultar",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_SHOW_HIDE, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx BUTTON_SHOW_HIDE!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_CHILD | WS_VISIBLE | ES_MULTILINE, //  | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL
		0, 0, 0, 0, hwnd, (HMENU) EDIT_DATA, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_DATA!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_SEARCH, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_SEARCH!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_DATA, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_DATA!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_RECT_A, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_RECT_A!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_RECT_B, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_RECT_B!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_RECT_C, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_RECT_C!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_RECT_D, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_RECT_D!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Ý",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_MOVER, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx BUTTON_MOVER!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Q",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_REDEFINIR, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx BUTTON_REDEFINIR!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_NEW_TEXT, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_NEW_TEXT!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Enviar",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_SEND_TEXT, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx BUTTON_SEND_TEXT!\t", true);
		
	if(!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "ComboBox", NULL,
		WS_DISABLED | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		0, 0, 0, 0, hwnd, (HMENU) COMBO_BOX_MESSAGE, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx COMBO_BOX_MESSAGE!\t", true);
		
	if(!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "ComboBox", NULL,
		WS_DISABLED | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		0, 0, 0, 0, hwnd, (HMENU) COMBO_BOX_PARAMS, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx COMBO_BOX_PARAMS!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "0",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_LPARAM, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_LPARAM!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "0",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 0, 0, 0, hwnd, (HMENU) EDIT_WPARAM, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx EDIT_WPARAM!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Enviar",
		WS_DISABLED | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_SEND_MESSAGE, hInstance, 0)))
	error((LPSTR) "Erro: CreateWindowEx BUTTON_SEND_MESSAGE!\t", true);
	
	// Limitação de quantidade de caracteres
	SendDlgItemMessage(hwnd, EDIT_SEARCH, EM_LIMITTEXT, 255, 0);
	SendDlgItemMessage(hwnd, EDIT_RECT_A, EM_LIMITTEXT, 4, 0);
	SendDlgItemMessage(hwnd, EDIT_RECT_B, EM_LIMITTEXT, 4, 0);
	SendDlgItemMessage(hwnd, EDIT_RECT_C, EM_LIMITTEXT, 4, 0);
	SendDlgItemMessage(hwnd, EDIT_RECT_D, EM_LIMITTEXT, 4, 0);
	SendDlgItemMessage(hwnd, EDIT_NEW_TEXT, EM_LIMITTEXT, 255, 0);
	SendDlgItemMessage(hwnd, EDIT_LPARAM, EM_LIMITTEXT, 8, 0);
	SendDlgItemMessage(hwnd, EDIT_WPARAM, EM_LIMITTEXT, 8, 0);
	
	// Fontes dos controles
	hfontTahoma16 = CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Tahoma");
	hWingDings20 = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "WingDings 3");
	if (!hfontTahoma16) hfontTahoma16 = (HFONT) GetStockObject(SYSTEM_FONT);
	if (!hWingDings20) hWingDings20 = (HFONT) GetStockObject(SYSTEM_FONT);
	for (int i=STATUS_BAR; i<=EDIT_DATA; i++)
		SendDlgItemMessage(hwndMain, i, WM_SETFONT, (WPARAM) hfontTahoma16, MAKELPARAM(true, 0));
	for (int i=BUTTON_MOVER; i<=BUTTON_REDEFINIR; i++)
		SendDlgItemMessage(hwndMain, i, WM_SETFONT, (WPARAM) hWingDings20, MAKELPARAM(true, 0));
	
	// COMBO_BOX_MESSAGE
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_LBUTTONDOWN");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_LBUTTONUP");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_LBUTTONDBLCLK");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_RBUTTONDOWN");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_RBUTTONUP");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_RBUTTONDBLCLK");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_KEYDOWN");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "WM_KEYUP");
	SendDlgItemMessage(hwnd, COMBO_BOX_MESSAGE, CB_SETCURSEL, 0, 0);
	
	GetWindowRect(GetDesktopWindow(), &rect);
	MoveWindow(hwndMain, rect.right/2 - JANELA_LARGURA/2, rect.bottom/2 - JANELA_ALTURA/2, JANELA_LARGURA, JANELA_ALTURA, TRUE);
	ShowWindow(hwndMain, SW_SHOWNORMAL);
	
	SetTimer(hwndMain, ID_TIMER_MOUSE, TIMER_MOUSE_TIME, 0);
}
//-------------------------------------------------->>
void wm_size() {
	RECT rc;
	GetClientRect(hwndMain, &rc);
	int statusBarDiv[] = {120, 180, 320, rc.right-170, -1};
	
	SendMessage(GetDlgItem(hwndMain, STATUS_BAR), SB_SETPARTS, 5, (LPARAM) statusBarDiv);
	SendMessage(GetDlgItem(hwndMain, STATUS_BAR), SB_SETTEXT, 4, (LPARAM) "\tby @devdiegorodrigues");
	SendMessage(GetDlgItem(hwndMain, STATUS_BAR), WM_SIZE, 0, 0);
	
	MoveWindow(GetDlgItem(hwndMain, SYS_TREE_VIEW_MAIN), 5, 5, rc.right-305, rc.bottom-35, TRUE);
	MoveWindow(GetDlgItem(hwndMain, BUTTON_TOTAL), rc.right-295, 5, 290, 30, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_SEARCH), rc.right-295, 40, 155, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, BUTTON_SEARCH), rc.right-135, 39, 130, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, BUTTON_SHOW_HIDE), rc.right-295, 80, 65, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, BUTTON_MOVER), rc.right-74, 111, 33, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, BUTTON_REDEFINIR), rc.right-38, 111, 33, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_RECT_A), rc.right-295, 112, 50, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_RECT_B), rc.right-240, 112, 50, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_RECT_C), rc.right-185, 112, 50, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_RECT_D), rc.right-130, 112, 50, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_NEW_TEXT), rc.right-295, 143, 215, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, BUTTON_SEND_TEXT), rc.right-75, 142, 70, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, COMBO_BOX_MESSAGE), rc.right-295, 185, 290, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, COMBO_BOX_PARAMS), rc.right-295, 215, 104, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_LPARAM), rc.right-185, 215, 50, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_WPARAM), rc.right-130, 215, 50, 25, TRUE);
	MoveWindow(GetDlgItem(hwndMain, BUTTON_SEND_MESSAGE), rc.right-75, 214, 70, 27, TRUE);
	MoveWindow(GetDlgItem(hwndMain, EDIT_DATA), rc.right-295, 400, 290, rc.bottom-430, TRUE);
}
//-------------------------------------------------->>
void wm_command(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	switch (LOWORD(wParam)) {
		case BUTTON_TOTAL:
			wsprintf(textToSearch, "");
			(hwndTreeView) ?
				CreateControlsHierarchy():
				error((LPSTR)"Controle Tree View não Disponível", false);
		break;
	
		case BUTTON_SEARCH:
			GetDlgItemText(hwnd, EDIT_SEARCH, textToSearch, sizeof(textToSearch));
			(strlen(textToSearch) > 0) ?
				CreateControlsHierarchy():
				info((LPSTR)"Insira um texto para busca!\t");
		break;
	
		case BUTTON_SHOW_HIDE:
			if (hwndTarget) {
				(IsWindowVisible(hwndTarget)) ?
					ShowWindow(hwndTarget, SW_HIDE):
					ShowWindow(hwndTarget, SW_SHOWNORMAL);
				(IsWindowVisible(hwndTarget)) ?
					SetWindowText(GetDlgItem(hwnd, BUTTON_SHOW_HIDE), "Ocultar"):
					SetWindowText(GetDlgItem(hwnd, BUTTON_SHOW_HIDE), "Exibir");
			} else {
				error((LPSTR)"Selecione um item da lista\t", false);
			}
		break;
		
		case BUTTON_MOVER:
			if (hwndTarget) {
				WINBOOL bSuccess[4] = { FALSE };
				int siStore[4];
				siStore[0] = GetDlgItemInt(hwnd, EDIT_RECT_A, &bSuccess[0], true);
				siStore[1] = GetDlgItemInt(hwnd, EDIT_RECT_B, &bSuccess[1], true);
				siStore[2] = GetDlgItemInt(hwnd, EDIT_RECT_C, &bSuccess[2], true);
				siStore[3] = GetDlgItemInt(hwnd, EDIT_RECT_D, &bSuccess[3], true);
				if (bSuccess[0] && bSuccess[1] && bSuccess[2] && bSuccess[3]) {
					MoveWindow(hwndTarget, siStore[0], siStore[1], siStore[2], siStore[3], true);
				} else {
					info((LPSTR)"Preencha os campos com a nova dimensão \nda janela, no formato x y w h\t");
				}
			} else {
				info((LPSTR)"Selecione um item da lista\t");
			}
		break;
	
		case BUTTON_REDEFINIR:
			if (hwndTarget) {
				if (targetOldRect.left != NULL){
					MoveWindow(hwndTarget, targetOldRect.left, targetOldRect.top, targetOldRect.right - targetOldRect.left, targetOldRect.bottom - targetOldRect.top, true);
				} else {
					info((LPSTR)"Nenhum valor salvo\t");
				}
			} else {
				info((LPSTR)"Selecione um item da lista\t");
			}
		break;
	
		case BUTTON_SEND_TEXT:
			if (hwndTarget) {
				char newText[256];
				if (GetDlgItemText(hwnd, EDIT_NEW_TEXT, newText, sizeof(newText)) > 0) {
					SetWindowText(hwndTarget, newText);
				} else {
					info((LPSTR)"Preencha a caixa com o novo texto\t");
				}
			} else {
				info((LPSTR)"Selecione um item da lista\t");
			}
		break;
	
		case BUTTON_SEND_MESSAGE:
			if (hwndTarget) {
				sendTargetMessage();
			} else {
				info((LPSTR)"Selecione um item da lista\t");
			}
		break;
	
		case COMBO_BOX_MESSAGE:
			if (HIWORD(wParam) == CBN_SELENDOK) {
				if (hwndTarget) {
					changeSubMessageControls(true);
				} else {
					info((LPSTR)"Selecione um item da lista\t");
				}
			}
		break;
	}
}
//-------------------------------------------------->>
void wm_notify(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	switch ((int)wParam) {
		case SYS_TREE_VIEW_MAIN: {
			NMHDR *pnmhdr = reinterpret_cast<NMHDR*>(lParam);
			if (pnmhdr->hwndFrom == hwndTreeView && pnmhdr->code == TVN_SELCHANGED) {
				NM_TREEVIEW FAR *pnmtv = reinterpret_cast<NM_TREEVIEW FAR *>(lParam);
				HTREEITEM hSelectedItem = pnmtv->itemNew.hItem;
				if (hSelectedItem == NULL) {
					error((LPSTR)"Erro ao obter dados do controle selecionado!\t", false);
					hwndTarget = NULL;
					break;
				}
				
				TVITEM item;
				char targetText[256];
			    memset(&item, 0, sizeof(item));
			    item.hItem = hSelectedItem;
			    item.mask = TVIF_TEXT | TVIF_PARAM;
				item.pszText = targetText;
	            item.cchTextMax = sizeof(targetText);
				
				if (TreeView_GetItem(hwndTreeView, &item)) {
			    	hwndTarget = reinterpret_cast<HWND>(item.lParam);
			    	(IsWindow(hwndTarget)) ?
			    		validWindow(true, targetText):
						validWindow(false, targetText);
			    }
			}
		}
		break;
	}
}
//-------------------------------------------------->>
void wm_timer(WPARAM wParam) {
	switch (wParam) {
		case ID_TIMER_MOUSE:
			statusBarMousePos();
		break;
	}
}
//-------------------------------------------------->>











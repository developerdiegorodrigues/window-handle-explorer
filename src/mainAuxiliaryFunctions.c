#include "resource.h"

//-------------------------------------------------->>
// Função auxiliar para adicionar um item ao Tree View
HTREEITEM AddTreeViewItem(HTREEITEM hParent, const char* text, HWND hWnd) {
    TVITEM tvItem = { 0 };
    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<char*>(text);
    tvItem.lParam = reinterpret_cast<LPARAM>(hWnd);

    TVINSERTSTRUCT tvInsert = { 0 };
    tvInsert.item = tvItem;
    tvInsert.hParent = hParent;
    tvInsert.hInsertAfter = TVI_LAST;

    return TreeView_InsertItem(hwndTreeView, &tvInsert);
}
//-------------------------------------------------->>
// Função recursiva para preencher o Tree View com a hierarquia dos controles filhos
void FillTreeView(HWND hwndParent, HTREEITEM hParentItem) {
    char className[256], windowTitle[256], textToShow[500];
    HWND hwndChild = GetWindow(hwndParent, GW_CHILD);
    
    while (hwndChild != NULL) {
        GetClassName(hwndChild, className, sizeof(className));
    	GetWindowText(hwndChild, windowTitle, sizeof(windowTitle));
        
        if (strlen(textToSearch) > 0) {
        	if (strstr(className, textToSearch) == NULL && strstr(windowTitle, textToSearch) == NULL) {
        		hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
        		continue;
			}
		}
        
        if (!strcmp(className, MAINCLASSNAME)) {
    		hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
    		continue;
		}
        
    	if (GetWindowTextLength(hwndChild) > 0) {
			wsprintf(textToShow, "(%s) - [%s]", windowTitle, className);
		} else {
			wsprintf(textToShow, "(NO TITLE) - [%s]", className);
		}
		
        HTREEITEM hChildItem = AddTreeViewItem(hParentItem, textToShow, hwndChild);
        FillTreeView(hwndChild, hChildItem);
	    hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
    }
}
//-------------------------------------------------->>
// Função inicial para preencher o Tree View
void CreateControlsHierarchy() {
	HTREEITEM hRootItem;
    TreeView_DeleteAllItems(hwndTreeView);
    hRootItem = AddTreeViewItem(TVI_ROOT, "Hierarquia", NULL);
    FillTreeView(GetDesktopWindow(), hRootItem);
    TreeView_Expand(hwndTreeView, hRootItem, TVE_EXPAND);
}
//-------------------------------------------------->>
void disableControls() {
	EnableWindow(GetDlgItem(hwndMain, BUTTON_SHOW_HIDE), false);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_A), false);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_B), false);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_C), false);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_D), false);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_MOVER), false);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_REDEFINIR), false);
	EnableWindow(GetDlgItem(hwndMain, EDIT_NEW_TEXT), false);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_SEND_TEXT), false);
	EnableWindow(GetDlgItem(hwndMain, COMBO_BOX_MESSAGE), false);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_SEND_MESSAGE), false);
	changeSubMessageControls(false);
}
//-------------------------------------------------->>
void enableControls() {
	EnableWindow(GetDlgItem(hwndMain, BUTTON_SHOW_HIDE), true);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_A), true);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_B), true);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_C), true);
	EnableWindow(GetDlgItem(hwndMain, EDIT_RECT_D), true);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_MOVER), true);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_REDEFINIR), true);
	EnableWindow(GetDlgItem(hwndMain, EDIT_NEW_TEXT), true);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_SEND_TEXT), true);
	EnableWindow(GetDlgItem(hwndMain, COMBO_BOX_MESSAGE), true);
	EnableWindow(GetDlgItem(hwndMain, BUTTON_SEND_MESSAGE), true);
	changeSubMessageControls(true);
}
//-------------------------------------------------->>
void changeSubMessageControls(bool status) {
	if (!status) {
		EnableWindow(GetDlgItem(hwndMain, COMBO_BOX_PARAMS), false);
		EnableWindow(GetDlgItem(hwndMain, EDIT_LPARAM), false);
		EnableWindow(GetDlgItem(hwndMain, EDIT_WPARAM), false);
		return;
	}
	
	char comboText[256];
	GetDlgItemText(hwndMain, COMBO_BOX_MESSAGE, comboText, sizeof(comboText));
	
	if (!strcmp(comboText, "WM_LBUTTONDOWN") || !strcmp(comboText, "WM_LBUTTONUP") || !strcmp(comboText, "WM_LBUTTONDBLCLK") || !strcmp(comboText, "WM_RBUTTONDOWN") || !strcmp(comboText, "WM_RBUTTONUP") || !strcmp(comboText, "WM_RBUTTONDBLCLK")) {
		EnableWindow(GetDlgItem(hwndMain, COMBO_BOX_PARAMS), false);
		EnableWindow(GetDlgItem(hwndMain, EDIT_LPARAM), true);
		EnableWindow(GetDlgItem(hwndMain, EDIT_WPARAM), true);
		SendDlgItemMessage(hwndMain, COMBO_BOX_PARAMS, CB_RESETCONTENT, 0, 0);
	}
	else if (!strcmp(comboText, "WM_KEYDOWN") || !strcmp(comboText, "WM_KEYUP")) {
		EnableWindow(GetDlgItem(hwndMain, COMBO_BOX_PARAMS), true);
		EnableWindow(GetDlgItem(hwndMain, EDIT_LPARAM), false);
		EnableWindow(GetDlgItem(hwndMain, EDIT_WPARAM), false);
		SendDlgItemMessage(hwndMain, COMBO_BOX_PARAMS, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hwndMain, COMBO_BOX_PARAMS, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "VK_RETURN");
		SendDlgItemMessage(hwndMain, COMBO_BOX_PARAMS, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "VK_EXECUTE");
		SendDlgItemMessage(hwndMain, COMBO_BOX_PARAMS, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR) "VK_ESCAPE");
		SendDlgItemMessage(hwndMain, COMBO_BOX_PARAMS, CB_SETCURSEL, 0, 0);
	}
}
//-------------------------------------------------->>
void validWindow(bool status, LPSTR targetText){
	char targetData[256];
	
	if (status) {
		DWORD pid;
		enableControls();
		(IsWindowVisible(hwndTarget)) ?
			SetWindowText(GetDlgItem(hwndMain, BUTTON_SHOW_HIDE), "Ocultar"):
			SetWindowText(GetDlgItem(hwndMain, BUTTON_SHOW_HIDE), "Exibir");
		SetRect(&targetOldRect, NULL, NULL, NULL, NULL);
		GetWindowRect(hwndTarget, &targetOldRect);
		//GetClientRect(hwndTarget, &targetOldRect);
		SetWindowText(GetDlgItem(hwndMain, EDIT_DATA), targetText);
		SendMessage(GetDlgItem(hwndMain, STATUS_BAR), SB_SETTEXT, 3, reinterpret_cast<LPARAM>(targetText));
		GetWindowThreadProcessId(hwndTarget, &pid);
		wsprintf(targetData, "\t%d", pid);
		SendMessage(GetDlgItem(hwndMain, STATUS_BAR), SB_SETTEXT, 1, reinterpret_cast<LPARAM>(targetData));
		wsprintf(targetData, "\t%d %d %d %d", targetOldRect.top, targetOldRect.left, targetOldRect.right, targetOldRect.bottom);
		SendMessage(GetDlgItem(hwndMain, STATUS_BAR), SB_SETTEXT, 2, reinterpret_cast<LPARAM>(targetData));
	} else {
		hwndTarget = NULL;
		disableControls();
		wsprintf(targetData, "\tNot valid HWND!");
		SendMessage(GetDlgItem(hwndMain, STATUS_BAR), SB_SETTEXT, 3, reinterpret_cast<LPARAM>(targetData));
	}
}
//-------------------------------------------------->>
void sendTargetMessage(){
	char comboText[256], subComboText[256], lParamText[32], wParamText[32];
	GetDlgItemText(hwndMain, COMBO_BOX_MESSAGE, comboText, sizeof(comboText));
	
	// SendMessage***
	if (!strcmp(comboText, "WM_LBUTTONDOWN")) {
		if (GetDlgItemText(hwndMain, EDIT_LPARAM, lParamText, sizeof(lParamText)) > 0 && GetDlgItemText(hwndMain, EDIT_WPARAM, wParamText, sizeof(wParamText)) > 0) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_LBUTTONDOWN, NULL, MAKELPARAM(atoi(lParamText), atoi(wParamText)));
		} else {
			info((LPSTR)"Preencha as caixas com os valores de LPARAM e WPARAM\t");
		}
	}
	else if (!strcmp(comboText, "WM_LBUTTONUP")) {
		if (GetDlgItemText(hwndMain, EDIT_LPARAM, lParamText, sizeof(lParamText)) > 0 && GetDlgItemText(hwndMain, EDIT_WPARAM, wParamText, sizeof(wParamText)) > 0) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_LBUTTONUP, NULL, MAKELPARAM(atoi(lParamText), atoi(wParamText)));
		} else {
			info((LPSTR)"Preencha as caixas com os valores de LPARAM e WPARAM\t");
		}
	}
	else if (!strcmp(comboText, "WM_LBUTTONDBLCLK")) {
		if (GetDlgItemText(hwndMain, EDIT_LPARAM, lParamText, sizeof(lParamText)) > 0 && GetDlgItemText(hwndMain, EDIT_WPARAM, wParamText, sizeof(wParamText)) > 0) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_LBUTTONDBLCLK, NULL, MAKELPARAM(atoi(lParamText), atoi(wParamText)));
		} else {
			info((LPSTR)"Preencha as caixas com os valores de LPARAM e WPARAM\t");
		}
	}
	else if (!strcmp(comboText, "WM_RBUTTONDOWN")) {
		if (GetDlgItemText(hwndMain, EDIT_LPARAM, lParamText, sizeof(lParamText)) > 0 && GetDlgItemText(hwndMain, EDIT_WPARAM, wParamText, sizeof(wParamText)) > 0) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_RBUTTONDOWN, NULL, MAKELPARAM(atoi(lParamText), atoi(wParamText)));
		} else {
			info((LPSTR)"Preencha as caixas com os valores de LPARAM e WPARAM\t");
		}
	}
	else if (!strcmp(comboText, "WM_RBUTTONUP")) {
		if (GetDlgItemText(hwndMain, EDIT_LPARAM, lParamText, sizeof(lParamText)) > 0 && GetDlgItemText(hwndMain, EDIT_WPARAM, wParamText, sizeof(wParamText)) > 0) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_RBUTTONUP, NULL, MAKELPARAM(atoi(lParamText), atoi(wParamText)));
		} else {
			info((LPSTR)"Preencha as caixas com os valores de LPARAM e WPARAM\t");
		}
	}
	else if (!strcmp(comboText, "WM_RBUTTONDBLCLK")) {
		if (GetDlgItemText(hwndMain, EDIT_LPARAM, lParamText, sizeof(lParamText)) > 0 && GetDlgItemText(hwndMain, EDIT_WPARAM, wParamText, sizeof(wParamText)) > 0) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_RBUTTONDBLCLK, NULL, MAKELPARAM(atoi(lParamText), atoi(wParamText)));
		} else {
			info((LPSTR)"Preencha as caixas com os valores de LPARAM e WPARAM\t");
		}
	}
	else if (!strcmp(comboText, "WM_KEYDOWN")) {
		GetDlgItemText(hwndMain, COMBO_BOX_PARAMS, subComboText, sizeof(subComboText));
		if (!strcmp(subComboText, "VK_RETURN")) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_KEYDOWN, VK_RETURN, 0);
		}
		else if (!strcmp(subComboText, "VK_EXECUTE")) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_KEYDOWN, VK_EXECUTE, 0);
		}
		else if (!strcmp(subComboText, "VK_ESCAPE")) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_KEYDOWN, VK_ESCAPE, 0);
		}
		else error((LPSTR)"Valor do COMBO_BOX_PARAMS inesperado\t", false);
	}
	else if (!strcmp(comboText, "WM_KEYUP")) {
		GetDlgItemText(hwndMain, COMBO_BOX_PARAMS, subComboText, sizeof(subComboText));
		if (!strcmp(subComboText, "VK_RETURN")) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_KEYUP, VK_RETURN, 0);
		}
		else if (!strcmp(subComboText, "VK_EXECUTE")) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_KEYUP, VK_EXECUTE, 0);
		}
		else if (!strcmp(subComboText, "VK_ESCAPE")) {
			SetFocus(hwndTarget);
			PostMessage(hwndTarget, WM_KEYUP, VK_ESCAPE, 0);
		}
		else error((LPSTR)"Valor do COMBO_BOX_PARAMS inesperado\t", false);
	}
}
//-------------------------------------------------->>
void statusBarMousePos(){
	POINT point;
	char text[32];
	GetCursorPos(&point);
	wsprintf(text, "\t x: %d, y: %d", point.x, point.y);
	SendMessage(GetDlgItem(hwndMain, STATUS_BAR), SB_SETTEXT, 0, (LPARAM) text);
}
//-------------------------------------------------->>











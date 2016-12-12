#include <SFML/Graphics.hpp>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <math.h>
#include "resource.h"
#include "warehouseview.h"
#include "warehouse.h"

const char g_szClassName[] = "myWindowClass";

HWND aboutDlgBox = NULL;
HWND hCmdLine = NULL;
HWND hCmdLog = NULL;
HWND hButtonGo = NULL;
HWND hView = NULL;

sf::RenderWindow sfmlView;
WarehouseView* warehouseView;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void AppendText(const HWND &hwnd, TCHAR* newText);
TCHAR* ProcessCommand(TCHAR* command);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(0));
	sf::Clock clock;

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	warehouseView = new WarehouseView();


	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINICON));

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window registration failed", "Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Automatyczny wózek wid³owy",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, 1223, 1015,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	Msg.message = ~WM_QUIT;
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			//PROCESSING WIN32 MESSAGES
			if (!IsDialogMessage(aboutDlgBox, &Msg))
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		}
		else
		{
			//PROCESSING SFML MESSAGES
			sf::Event event;
			while (sfmlView.pollEvent(event))
			{
				if (event.type == event.MouseButtonPressed
					&& event.mouseButton.button == sf::Mouse::Left)
				{
					if (warehouseView->getRackView())
					{
						if (warehouseView->getButtonBack().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(sfmlView))))
						{
							warehouseView->setRackView(0);
						}
					}
					else
					{
						for (int i = 0; i < RACKQNTY; i++)
						{
							if (warehouseView->getRack(i).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(sfmlView))))
							{
								warehouseView->setRackView(i + 1);
							}
						}
					}
				}
			}

			for (int i = 0; i < RACKQNTY; i++)
			{
				if (warehouseView->rackHighlight[i] == false
					&& warehouseView->getRack(i).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(sfmlView))))
				{
					warehouseView->highlightRack(i, true);
				}
				else if (warehouseView->rackHighlight[i] == true
					&& !warehouseView->getRack(i).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(sfmlView))))
				{
					warehouseView->highlightRack(i, false);
				}
			}
			//SFML RENDERING CODE
			sfmlView.clear(sf::Color(237, 209, 140));

			if (clock.getElapsedTime() > sf::milliseconds(20))
			{
				warehouseView->forkliftUpdate(clock.getElapsedTime());
				clock.restart();
			}

			sfmlView.draw(*warehouseView);

			sfmlView.display();
		}
	}
	return (int)Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		HFONT hfDefault;

		hCmdLog = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
			0, 0, 1200, 130, hwnd, (HMENU)IDC_MAIN_CMDLOG, GetModuleHandle(NULL), NULL);
		hCmdLine = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL,
			0, 130, 1160, 20, hwnd, (HMENU)IDC_MAIN_CMDLINE, GetModuleHandle(NULL), NULL);
		hButtonGo = CreateWindow("BUTTON", "Wykonaj",
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			1160, 130, 60, 20, hwnd, (HMENU)IDC_BUTTON_GO, GetModuleHandle(NULL), NULL);
		hView = CreateWindow("BUTTON", NULL, 
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
			1, 151, 1200, 800, hwnd, NULL, GetModuleHandle(NULL), NULL);

		if (hCmdLog == NULL)
			MessageBox(hwnd, "Could not create CmdLog control.", "Error", MB_OK | MB_ICONERROR);
		if (hCmdLine == NULL)
			MessageBox(hwnd, "Could not create CmdLine control.", "Error", MB_OK | MB_ICONERROR);
		if (hButtonGo == NULL)
			MessageBox(hwnd, "Could not create ButtonGo control.", "Error", MB_OK | MB_ICONERROR);
		if (hView == NULL)
			MessageBox(hwnd, "Could not create View control.", "Error", MB_OK | MB_ICONERROR);

		hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(hCmdLog, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		SendMessage(hCmdLine, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		SendMessage(hButtonGo, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));

		sfmlView.create(hView);
	}
	break;
	case WM_SIZE:
	{
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);

		SetWindowPos(hCmdLog, NULL, 0, 0, rcClient.right, 130, SWP_NOZORDER);
		SetWindowPos(hCmdLine, NULL, 0, 130, rcClient.right - 60, 20, SWP_NOZORDER);
		SetWindowPos(hButtonGo, NULL, rcClient.right - 60, 130, 60, 20, SWP_NOZORDER);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_GO:
		{
			int len = GetWindowTextLength(hCmdLine);
			if (len > 0)
			{
				TCHAR* buf = (TCHAR*)GlobalAlloc(GPTR, (len + 1) * sizeof(TCHAR));
				GetWindowText(hCmdLine, buf, len + 1);
				AppendText(hCmdLog, ">> ");
				AppendText(hCmdLog, buf);
				AppendText(hCmdLog, "\n");
				AppendText(hCmdLog, ProcessCommand(buf));
				SetWindowText(hCmdLine, "");

				SetFocus(hCmdLine);
				GlobalFree(buf);
			}
		}
		break;
		case ID_FILE_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		break;
		case ID_HELP_ABOUT:
			if (aboutDlgBox != NULL)
			{
				ShowWindow(aboutDlgBox, SW_SHOW);
			}
			else
			{
				aboutDlgBox = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT),
					hwnd, AboutDlgProc);
				if (aboutDlgBox != NULL)
				{
					ShowWindow(aboutDlgBox, SW_SHOW);
				}
				else
				{
					MessageBox(hwnd, "About dialog box creation failed", "Error",
						MB_OK | MB_ICONINFORMATION);
				}
			}
		break;
		}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		delete warehouseView;
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
	break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			PostMessage(aboutDlgBox, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(aboutDlgBox);
		break;
	case WM_DESTROY:
		aboutDlgBox = NULL;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void AppendText(const HWND &hwnd, TCHAR* newText)
{
	DWORD StartPos, EndPos;
	SendMessage(hwnd, EM_GETSEL, reinterpret_cast<WPARAM>(&StartPos), reinterpret_cast<WPARAM>(&EndPos));
	int outLength = GetWindowTextLength(hwnd);

	SendMessage(hwnd, EM_SETSEL, outLength, outLength);
	SendMessage(hwnd, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(newText));
	SendMessage(hwnd, EM_SETSEL, StartPos, EndPos);
	return;
}

TCHAR* ProcessCommand(TCHAR* command)
{
	std::string cmd = command;
	if (std::stoi(cmd) >= 100 && std::stoi(cmd) < 1000)
	{
		warehouseView->flTakePackage(std::stoi(cmd));
		std::string temp = "";
		temp += "Zdjeto paczke nr " + cmd + "\n";
		TCHAR* answer = new TCHAR[temp.size() + 1];
		answer[temp.size()] = 0;
		std::copy(temp.begin(), temp.end(), answer);
		return answer;
	}
	return "Nie rozpoznano polecenia.\n";
}



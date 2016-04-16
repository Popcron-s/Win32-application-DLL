#include "Windows.h"

Windows* Windows::m_pSingleton = 0x00;

Windows* Windows::GetSingleton(){
	if(m_pSingleton == 0x00){
		m_pSingleton = new Windows;
	}
	return m_pSingleton;
}
void Windows::Destroy(){
	if(m_pSingleton != 0x00){
		delete m_pSingleton;
		m_pSingleton = 0x00;
	}
}

void Windows::Create(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x, int y){
	m_WndClass.hInstance = hInstance;   			// �ν��Ͻ��� ���� �ڵ�
	m_WndClass.lpszClassName = Title;		// Window Ŭ���� �̸�
	m_WndClass.lpfnWndProc = WndProc;  			// window �Լ�
	m_WndClass.style = 0;     					// �⺻ ��Ÿ�� 
	m_WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE( IDI_APPLICATION)); // ������ ��Ÿ��
	m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// Ŀ�� ��Ÿ��
	m_WndClass.lpszMenuName = NULL;  			// �޴� ������� ����
	m_WndClass.cbClsExtra = 0;    				// �߰� ������ �ʿ����� ����(�޵��찡 ����ϴ� ���� ����)
	m_WndClass.cbWndExtra = 0;    				// �߰� ������ �ʿ����� ����
	m_WndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH) ; // ������ ������ ������� ��

	if(!RegisterClass(&m_WndClass)){
		return;
	}

	// GetSystemMextrics(nInfo)
	// nIndex
	// SM_CXSCREEN = �� ���÷��� ���λ�����
	// SM_CYSCREEN = �� ���÷��� ���λ�����
	// SM_CXSIZEFRAME = ���������� ������
	// SM_CYSIZEFRAME = ���������� ������
	// SM_CYCAPTION = ĸ�ǹ��� ����

	m_hwnd = CreateWindow(
		Title,					// ������ Ŭ���� �̸�
		Title,					// Ÿ��Ʋ
		WS_PCSWINDOW,		// ������ ��Ÿ�� (normal = WS_OVERLAPPEDWINDOW)
		GetSystemMetrics(SM_CXSCREEN)/2 - ((x + FRAMESIZE_X)/2),//CW_USEDEFAULT,				// X��ǥ - Windows�� ����
		GetSystemMetrics(SM_CYSCREEN)/2 - ((y + FRAMESIZE_Y)/2),//CW_USEDEFAULT,				// Y��ǥ - Windows�� ����
		x + FRAMESIZE_X,						// ���� - windows�� ����
		y + FRAMESIZE_Y,						// ���� - windows�� ����
		HWND_DESKTOP,				// �θ� window ����
		NULL,						// �޴� ������� ����
		hInstance,					// �� ���α׷��� �ν��Ͻ� �ڵ�
		(void*)this);						// �߰����� �Ű����� ����

	ShowWindow(m_hwnd, *nCmdShow);
	UpdateWindow(m_hwnd);

	ZeroMemory(&m_msg,sizeof(m_msg));

	m_WinSize.x = x;
	m_WinSize.y = y;

	m_hInstance = hInstance;
}

LRESULT CALLBACK Windows::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	Windows *pWindow = NULL;
	bool Processed = false;

	switch(iMsg){
	case WM_NCCREATE:
		SetWindowLong(hwnd, GWL_USERDATA, (long)((LPCREATESTRUCT(lParam))->lpCreateParams));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		pWindow = (Windows*) GetWindowLong(hwnd, GWL_USERDATA);
		if( pWindow != NULL ){
			if(pWindow->MessageHandler != NULL){
				pWindow->MessageHandler(hwnd, iMsg, wParam, lParam);
			}
		}
		break;
	}
	if( Processed == false ){
		return DefWindowProc (hwnd, iMsg, wParam, lParam);
	}
}

void Windows::Run(){
	while(WM_QUIT != m_msg.message){
		if(PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE)){
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		if(Render != NULL){
			Render();
		}
	}
}
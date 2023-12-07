#include "Util.h"

// â�� �ּ� �� �ִ� ũ�� ����
void SetMinMaxWindowSizes(HWND hWnd, MINMAXINFO* minMaxInfo, int minWidth, int minHeight) {
	// ������ ���� ũ�� ����
	RECT rect = { 0, 0, minWidth, minHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// MINMAXINFO ����ü�� ����Ͽ� â ũ�� ���� ����
	minMaxInfo->ptMinTrackSize.x = width; // �ּ� �ʺ�
	minMaxInfo->ptMinTrackSize.y = height; // �ּ� ����
	minMaxInfo->ptMaxTrackSize.x = width; // �ִ� �ʺ�
	minMaxInfo->ptMaxTrackSize.y = height; // �ִ� ����
}

// Ŀ�� ����
void UpdateCursor(HWND hwnd, const RECT& drawing_area) {
	// Ŀ���� ��ġ�� �����ɴϴ�.
	POINT pt;
	GetCursorPos(&pt);
	// �ش� ��ġ�� Ŭ���̾�Ʈ ������ ��ǥ�� ��ȯ�մϴ�.
	ScreenToClient(hwnd, &pt);
	// ����� ���� ���� Ŀ���� �ִ��� Ȯ���մϴ�.
	if (PtInRect(&drawing_area, pt))
	{
		// ����� ���� �ȿ� ������ Ŀ���� ũ�ν��� �����մϴ�.
		SetCursor(LoadCursor(NULL, IDC_CROSS));
	}
	else
	{
		// ����� ���� �ۿ� ������ �⺻ Ŀ���� ����մϴ�.
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
}


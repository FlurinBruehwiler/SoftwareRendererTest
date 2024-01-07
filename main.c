#include <windows.h>
#include <stdbool.h>

const char g_szClassName[] = "myWindowClass";
HDC hdc;

typedef struct Vector2 {
    int x;
    int y;
} Vector2;

bool edgeFunction(Vector2 startLine, Vector2 endLIne, Vector2 point)
{
    return ((point.x - startLine.x) * (endLIne.y - startLine.y) - (point.y - startLine.y) * (endLIne.x - startLine.x) >= 0);
}

bool pointIsInsideTriangle(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 point)
{
    bool inside = true;
    inside &= edgeFunction(v0, v1, point);
    inside &= edgeFunction(v1, v2, point);
    inside &= edgeFunction(v2, v0, point);

    return inside;
}

void DrawLine(int startX, int startY, int endX, int endY, COLORREF color){
    int m_new = 2 * (endY - startY);
    int slope_error_new = m_new - (endX - startX);
    for (int x = startX, y = startY; x <= endX; x++) {
        SetPixel(hdc, x, y, color);

        // Add slope to increment angle formed
        slope_error_new += m_new;

        // Slope error reached limit, time to
        // increment y and update slope error.
        if (slope_error_new >= 0) {
            y++;
            slope_error_new -= 2 * (endX - startX);
        }
    }
}

void DrawTriangle(Vector2 v0, Vector2 v1, Vector2 v2, COLORREF color){
    for (int x = 0; x < 500; ++x) {
        for (int y = 0; y < 500; ++y) {
            if(pointIsInsideTriangle(v0, v1, v2, (Vector2){ x, y })){
                SetPixel(hdc, x, y, color);
            }
        }
    }
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static COLORREF pixelColor = RGB(255, 0, 0); // Set initial color (red)

    switch (msg) {
        case WM_PAINT:
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);

            DrawTriangle((Vector2){400, 100}, (Vector2){100, 100}, (Vector2){400, 400}, pixelColor);

            EndPaint(hwnd, &ps);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return
            DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx( & wc)) {
        MessageBox(NULL,
            "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "SoftwareRendering",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL,
            "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage( & Msg, NULL, 0, 0) > 0) {
        TranslateMessage( & Msg);
        DispatchMessage( & Msg);
    }
    return Msg.
    wParam;
}

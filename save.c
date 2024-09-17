#include <windows.h>
#include <stdio.h>

#define HOTKEY_ID 1
#define HOTKEY_MOD (MOD_CONTROL | MOD_SHIFT)
#define HOTKEY_KEY 'S'
#define OUTPUT_FILE "C:\\Users\\Sikus\\Music\\pobieranie.txt"
#define SLEEP_DURATION 10 // Sleep duration in milliseconds

void SaveClipboardToFile(const char* filename) {
    if (!OpenClipboard(NULL)) {
        fprintf(stderr, "Failed to open clipboard. Error code: %lu\n", GetLastError());
        return;
    }

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == NULL) {
        fprintf(stderr, "No text data in clipboard. Error code: %lu\n", GetLastError());
        CloseClipboard();
        return;
    }

    char* pszText = GlobalLock(hData);
    if (pszText == NULL) {
        fprintf(stderr, "Failed to lock global memory. Error code: %lu\n", GetLastError());
        CloseClipboard();
        return;
    }

    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for appending. Error code: %d\n", GetLastError());
        GlobalUnlock(hData);
        CloseClipboard();
        return;
    }

    fprintf(file, "\n%s", pszText);
    fclose(file);

    GlobalUnlock(hData);
    CloseClipboard();

    // Print a success message to the console
    printf("Clipboard contents saved to file: %s\n", filename);
}

int main() {
    if (!RegisterHotKey(NULL, HOTKEY_ID, HOTKEY_MOD, HOTKEY_KEY)) {
        fprintf(stderr, "Failed to register hotkey. Error code: %d\n", GetLastError());
        return 1;
    }

    MSG msg;
    printf("Press CTRL+SHIFT+S to save clipboard contents to file.\n");

    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }

            if (msg.message == WM_HOTKEY) {
                SaveClipboardToFile(OUTPUT_FILE);
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // Sleep for a short time to reduce CPU usage
        Sleep(SLEEP_DURATION);
    }

    UnregisterHotKey(NULL, HOTKEY_ID);
    return 0;
}

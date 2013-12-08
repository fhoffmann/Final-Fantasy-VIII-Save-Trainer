#include <Windows.h>

void main() {
	HWND handle = NULL;
	HANDLE process = NULL;
	DWORD processID = -1;
	char buffer = -1;		
	unsigned int save_addresses[3] = { 0x01CE637B, 0x01D004F9, 0x01D0052D};
	char save_values[3] = {01, 01, 03};
	short i = 0;

	handle = FindWindow(NULL, L"FINAL FANTASY VIII");
	if(handle) {			
		GetWindowThreadProcessId(handle, &processID);
		process = OpenProcess(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFF, FALSE, processID);
		for(i=0; i<3; i++) {
			if(ReadProcessMemory(process, (LPVOID) save_addresses[i], &buffer, sizeof(buffer), NULL)) {
				if(buffer != -1 && buffer != save_values[i]) {
					WriteProcessMemory(process, (LPVOID) save_addresses[i], &save_values[i], sizeof(save_values[i]), NULL);
				}
			}
		}
	}
}
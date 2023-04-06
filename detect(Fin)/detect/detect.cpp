#include <windows.h>
#include <tlhelp32.h>
#include <iostream>	
#include <string>
#include "psapi.h"
//Made by Fin 
//Youtube : https://www.youtube.com/@fin_1221

DWORD GetProcessByFileName(char* name) { //프로세스 파일이름 가져오기
	DWORD process_id_array[1024];
	DWORD bytes_returned;
	DWORD num_processes;
	HANDLE hProcess;
	char image_name[256];
	char buffer[256];
	int i;
	DWORD exitcode;
	EnumProcesses(process_id_array, 256 * sizeof(DWORD), &bytes_returned);
	num_processes = (bytes_returned / sizeof(DWORD));
	for (i = 0; i < num_processes; i++) {
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process_id_array[i]);
		if (GetModuleBaseName(hProcess, 0, image_name, 256)) {
			if (!stricmp(image_name, name)) {
				CloseHandle(hProcess);
				return process_id_array[i];
			}
		}
		CloseHandle(hProcess);
	}
	return 0;
}


DWORD GetProcID(LPCSTR procName) { //프로세스 ID 가져오기
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hSnap) {
		if (Process32First(hSnap, &ProcEntry)) {
			do {
				if (!strcmp(ProcEntry.szExeFile, procName))
					break;
			} while (Process32Next(hSnap, &ProcEntry));
		}
		CloseHandle(hSnap);
	}


	return ProcEntry.th32ProcessID;
}
DWORD ProcID = 0;

int main()
{
	char* lpProcessName = "x32dbg.exe"; //프로세스 이름
	if (lpProcessName == "")
	{
		printf("Error(1)\n");//Error 1이 뜨면 비어있음
	}
	else if(lpProcessName != "")
	{
		system("title Programe Detect");
		system("cls");
		Sleep(1000); //1초 정도 기달림
		while (1)
		{
			DWORD dwPID;
			dwPID = GetProcessByFileName(lpProcessName);
			if (dwPID == NULL) //파일이 있는지 없는지 체크
			{
				system("cls");
				system("mode con: cols=70 lines=25"); //콘솔 사이즈 조정!
				printf("Waiting for %s", lpProcessName);
				while (1)
				{
					dwPID = GetProcessByFileName(lpProcessName);
					if (dwPID != NULL)
					{
						Sleep(1000);
						break;
					}
				}
			}

			system("cls");
			system("mode con: cols=70 lines=25");
			printf("detect program\n");
			Sleep(1000);
			while (1)
			{

			}
			//while (1) //프로그램 종료 감지 로직
			//{
			//	dwPID = GetProcessByFileName(lpProcessName);
			//	if (dwPID == NULL)
			//	{
			//		system("cls");
			//		printf("exit program\n");
			//		Sleep(2000);
			//		break;
			//	}
			//}
			//break;
		}
	}
	else
	{
		printf("Error(0)\n"); //Error 0이 뜨면 이유 모를 에러
	}

}

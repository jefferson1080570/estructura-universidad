#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

bool cerrarProcesoPorNombre(const std::wstring& nombreProceso) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::wcerr << L"No se pudo crear el snapshot del sistema." << std::endl;
        return false;
    }

    PROCESSENTRY32 proceso;
    proceso.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &proceso)) {
        do {
            if (nombreProceso == proceso.szExeFile) {
                HANDLE handleProceso = OpenProcess(PROCESS_TERMINATE, FALSE, proceso.th32ProcessID);
                if (handleProceso != NULL) {
                    if (TerminateProcess(handleProceso, 0)) {
                        std::wcout << L"Proceso " << nombreProceso << L" cerrado correctamente." << std::endl;
                        CloseHandle(handleProceso);
                        CloseHandle(snapshot);
                        return true;
                    } else {
                        std::wcerr << L"No se pudo cerrar el proceso." << std::endl;
                    }
                    CloseHandle(handleProceso);
                } else {
                    std::wcerr << L"No se pudo obtener el handle del proceso." << std::endl;
                }
            }
        } while (Process32Next(snapshot, &proceso));
    }

    CloseHandle(snapshot);
    std::wcerr << L"Proceso " << nombreProceso << L" no encontrado." << std::endl;
    return false;
}

int main() {
    std::wstring nombre = L"sam.garces.exe";  // Nombre simulado del proceso
    cerrarProcesoPorNombre(nombre);
    return 0;
}
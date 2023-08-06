#include <Windows.h>
#include <iostream>

int main() {
    // O caminho para o arquivo do driver (.sys) 
    LPCWSTR driverPath = L"C:\\Windows\\System32\\WinHttpDriver.sys";

    // Carregando o driver usando a API CreateService
    SC_HANDLE scManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scManager) {
        std::cerr << "Falha ao abrir o Gerenciador de Controle de Servi�o. Erro: " << GetLastError() << std::endl;
        return 1;
    }

    SC_HANDLE service = CreateService(
        scManager,
        L"WinHttpDriver",    // Nome do servi�o
        L"WinHttpDriver", // Display Name
        SERVICE_ALL_ACCESS,
        SERVICE_KERNEL_DRIVER,
        SERVICE_BOOT_START,
        SERVICE_ERROR_IGNORE,
        driverPath,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    );

    if (!service) {
        std::cerr << "Falha ao criar o servi�o. Erro: " << GetLastError() << std::endl;
        CloseServiceHandle(scManager);
        return 1;
    }

    std::cout << "Servi�o criado com sucesso." << std::endl;

    // Iniciando o servi�o
    if (!StartService(service, 0, nullptr)) {
        std::cerr << "Falha ao iniciar o servi�o. Erro: " << GetLastError() << std::endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scManager);
        return 1;
    }

    std::cout << "Servi�o iniciado com sucesso." << std::endl;

    // Fechando as al�as de servi�o e Gerenciador de Controle de Servi�o
    CloseServiceHandle(service);
    CloseServiceHandle(scManager);

    return 0;
}

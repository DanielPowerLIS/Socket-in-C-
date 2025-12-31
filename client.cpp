#include<iostream>
#include<winsock2.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

int main(){
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[1024] = {0};

    // Iniciliamos Winsock
    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        cout << "Fallo en WSAStartup. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }

    // Ahora necesitamos crear el socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket == INVALID_SOCKET){
        cout << "No se pudo crear el socket." << endl;
        WSACleanup();
        return 1;
    }

    // Configuramos ahora la direccion del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if(bind(serverSocket, (sockaddr*) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        cout << "Bind failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    return 0;
}
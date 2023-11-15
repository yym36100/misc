//#include <windows.h>
#include <winsock2.h>
#include <stdio.h>

//Prototypen

int startWinsock(void);

int main(int argc, char* argv[])
{
	char mySrv[] = "127.0.0.1";

	int i;
	for (i = 0; i < argc; i++)
	{	printf("Param %i=%s \n", i, argv[i]);
	}

	long rc;

	//initialisieren Winsock-DLL
	rc = startWinsock();
	if (rc != 0) 
	{	printf("Fehler: startWinsock, FehlerCode: %d\n", rc);
		return 1;
	}
	else
	{	printf("Winsock gestartet.\n");
	}

	//Socket öffnen (erstellen)
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{	printf("Fehler Socket nicht erstellt - Code=: %d\n", WSAGetLastError());
		return 1;
	} 
	else
	{	printf("Socket erstellt.\n");
	}

	//connect zum Server
	SOCKADDR_IN srvAdr;
	memset(&srvAdr, 0, sizeof(SOCKADDR_IN)); //Memory immer mit 0 initialisieren
	srvAdr.sin_family = AF_INET;
	srvAdr.sin_port = htons(12345); //PortNummer
	srvAdr.sin_addr.s_addr = inet_addr(mySrv); //IP von Zielrechner

	char c;
	printf(">>connecten...:"); c = getchar();
	rc = connect(s, (SOCKADDR*) &srvAdr, sizeof(SOCKADDR));
	if (rc == SOCKET_ERROR)
	{	printf("Fehler connect() - Code=: %d\n", WSAGetLastError());
		return 1;
	}
	else
	{	printf("Server %s connected.\n", mySrv);
	}

	printf(">>senden 1...:"); c = getchar();
	// Daten senden
	char buf[256];
	strcpy_s(buf, "Hallo, is there anybody?");
	rc = send(s, buf, (int) strlen(buf), 0);
	if (rc >= 0 && rc <= 256)
	{	printf("Daten gesendet %d.\n", rc);
	}
	else
	{	printf("Problem senden - Code=:%d RC=:%d.\n", WSAGetLastError(), rc);
		return 1;
	}

	printf(">>empfangen 1..."); //c = getchar();
	// Daten empfangen
	rc = recv(s, buf, 255, 0);
	if (rc == 0 || rc == SOCKET_ERROR)
	{	printf("Zu Server no Connection - Code=: %d.\n", WSAGetLastError());
		closesocket(s);
		return 1;
	}
	else
	{	// Daten ausgeben
		if (rc < 256)	// Buffergröße absichern
		{	buf[rc] = '\0';	// char(0) an das Ende des Buffers setzen ;-)
		} else
		{	buf[256] = '\0';
		}
		printf("%s<\n", buf);
	}
	
	printf(">>senden 2...:"); c = getchar();
	// Daten senden
//	char buf[256];
	strcpy_s(buf, "I see you!");
	rc = send(s, buf, (int) strlen(buf), 0);
	if (rc >= 0 && rc <= 256)
	{	printf("Daten gesendet %d.\n", rc);
	}
	else
	{	printf("Problem senden - Code=:%d RC=:%d.\n", WSAGetLastError(), rc);
		return 1;
	}

	printf(">>empfangen 2..."); //c = getchar();
	// Daten empfangen
	rc = recv(s, buf, 255, 0);
	if (rc == 0 || rc == SOCKET_ERROR)
	{	printf("Zu Server no Connection - Code=: %d.\n", WSAGetLastError());
		closesocket(s);
		return 1;
	}
	else
	{	// Daten ausgeben
		if (rc < 256)	// Buffergröße absichern
		{	buf[rc] = '\0';	// char(0) an das Ende des Buffers setzen ;-)
		} else
		{	buf[256] = '\0';
		}
		printf("%s<\n", buf);
	}

	printf(">>Shutdown...:"); c = getchar();
	rc = shutdown(s, SD_SEND);
	if (rc) // rc == SOCKET_ERROR
	{	printf("Problem shutdown() - Code=:%d RC=:%d.\n", WSAGetLastError(), rc);
	}

	printf("--- sleeping...");
	Sleep(3 * 1000);

	printf("---closesocket() Client Ende...:"); c = getchar();
//	gets(buf); printf("\n");

//////////////////////////////////////////////////////////////////////////////////
	//Cleanup
	closesocket(s);
	WSACleanup();

	return 0;
}

int startWinsock(void)
{
	WSADATA wsa;
	//wir wollen Version 2.0
	return WSAStartup(MAKEWORD(2,0), &wsa);
}


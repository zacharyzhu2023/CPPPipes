#define DEFAULT_LENGTH 2048

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
	/* Connect to the server pipe */
	HANDLE clientPipe = CreateFile(L"\\\\.\\pipe\\pipeName", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (clientPipe == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to connect to server pipe." << endl;
		CloseHandle(clientPipe);
		return 1;
	}

	/* Receive data from the pipe */
	DWORD bytesRead;
	char messageReceiver[DEFAULT_LENGTH];
	int counter = 0;
	while (true)
	{
		bool works = ReadFile(clientPipe, messageReceiver, DEFAULT_LENGTH, &bytesRead, NULL);
		if (works)
		{
			cout << "Bytes read: " << bytesRead << endl;
			printf("Message read:\n%.*s", bytesRead, messageReceiver);
			cout << endl;
		}
		else
		{
			/*cout << "Failed to receive message." << endl;
			CloseHandle(clientPipe);
			return 1;*/
		}
		counter++;
	}

	/* Disconnect from the pipe */
	CloseHandle(clientPipe);
	return 0;

}
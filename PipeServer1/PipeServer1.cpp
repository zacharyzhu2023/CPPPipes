#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
	/* Creating an instance of a named pipe */
	// Pipe names start with: \\.pipe\
	
	HANDLE serverPipe = CreateNamedPipe(L"\\\\.\\pipe\\pipeName", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE,
		1, 0, 0, 0, NULL);
	if (serverPipe == NULL || serverPipe == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to create server pipe." << endl;
		return 1;
	}

	/* Waiting for client program to connect */
	bool works = ConnectNamedPipe(serverPipe, NULL); // Wait for client to connect
	if (!works)
	{
		cout << "Client connection failed" << endl;
		CloseHandle(serverPipe);
		return 1;
	}
	else
	{
		cout << "Success! Client has connected." << endl;
	}
	/* Sending data down the pipe */
	string serverMessage1 = "Testing a message to send.\nThe second line of the message."
		"\nThe third line of the message.\n";
	string serverMessage2 = "Sending another message.\nThis is message #2\n";
	string serverMessage3 = "The third message.\nFolk etymology dominates.\n"
		"How can this be the end?\n";
	string serverMessage4 = "Ok this is the last one.\nFour messages should be enough.\n";
	string toSend[4] = { serverMessage1, serverMessage2, serverMessage3, serverMessage4 };
	int counter = 0;
	while (counter < 4)
	{
		DWORD bytesWritten = 0;
		works = WriteFile(serverPipe, toSend[counter].c_str(), toSend[counter].length(), &bytesWritten, NULL);
		if (works)
		{
			cout << "Success! Bytes sent: " << bytesWritten << endl;
		}
		else
		{
			cout << "Failed to send data. Error: " << GetLastError() << endl;
			return 1;
		}
		counter++;
	}

	/* Disconnect/close pipe instance */
	CloseHandle(serverPipe);
	return 0;

}
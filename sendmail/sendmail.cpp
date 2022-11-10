////////////////////////////////////////////////////////////////////////////////////
// title : sendmail
// desc : ������ �ֿܼ��� ������ ���� ������ ���α׷�
// author : ysoftman
// os : Windows
////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

// E-mail ������ �Լ�
int SendMail(char *EmailServer, char *EmailTo, char *EmailFrom, char *EmailSubject, char *EmailMsg)
{
	SOCKET mySocket;
	WSADATA wsaData;
	FILE *fpSmtpLog = NULL;

	struct hostent *host;
	struct sockaddr_in dest_addr;

	int BufferSize = 300;
	int Waittime = 500;
	int Sent = 0;
	int Received = 0;
	int len1 = strlen(EmailTo);
	int len2 = strlen(EmailFrom);
	int len3 = strlen(EmailSubject);
	int len4 = strlen(EmailMsg);

	char *EmailBuf = NULL;
	char *LogBuf = NULL;

	EmailBuf = (char*)malloc(len1+len2+len3+len4+100);
	LogBuf = (char*)malloc(BufferSize+1);

	// ���� ������ �α�
	fpSmtpLog = fopen("sendmail.log", "a");

	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR)
	{
		fputs("WSAStartup failed\n", fpSmtpLog);
		WSACleanup();
		return -1;
	}

	if ( (host=gethostbyname(EmailServer)) == NULL)
	{
		perror("gethostbyname");
		return -1;
	}

	memset(&dest_addr, 0, sizeof(dest_addr));
	memcpy(&(dest_addr.sin_addr), host->h_addr, host->h_length);

	// prepare dest_addr
	dest_addr.sin_family = host->h_addrtype;	// AF_INET from gethostbyname
	dest_addr.sin_port = htons(25);				// Port ����

	// Get socket
	if ( (mySocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return -1;
	}

	// Connect 
	fputs("Connecting...\n", fpSmtpLog);

	if (connect(mySocket, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1)
	{
		perror("Connect failed.");
		return -1;
	}

	// SMTP ���������� ����Ͽ� ���� ������
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// ȯ�� �޼��� ����
	LogBuf[Received] = '\0';	
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "HELO google.co.kr\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// ȯ�� �޼��� ����

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// ���� ����
	LogBuf[Received] = '\0';	
	fputs(LogBuf, fpSmtpLog);
	sprintf(EmailBuf, "MAIL FROM:<%s>\n", EmailFrom);
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// ������ ��� �ּ� ����

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// ���� ����
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	sprintf(EmailBuf, "RCPT TO:<%s>\n", EmailTo);
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// �޴� ��� �ּ� ����

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// ���� ����
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "DATA\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// ���� ������ ����

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// ���� ����
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	Sleep(Waittime);
	strcpy(EmailBuf, "To:");
	strcat(EmailBuf, EmailTo);
	strcat(EmailBuf, "\n");
	strcat(EmailBuf, "From:");
	strcat(EmailBuf, EmailFrom);
	strcat(EmailBuf, "\n");
	strcat(EmailBuf, "Subject:");
	strcat(EmailBuf, EmailSubject);
	strcat(EmailBuf, "\n");
	strcat(EmailBuf, EmailMsg);
	strcat(EmailBuf, "\r\n.\r\n");							// ���� ������ <CRLR>.<CRLR>�� ������ ��.
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// ����� ���� ����

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// ���� ����
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "QUIT\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// ���� �޼��� ����

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// ���� ����
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);

	fclose(fpSmtpLog);

	if (EmailBuf != NULL)
	{
		free(EmailBuf);
	}
	if (LogBuf != NULL)
	{
		free(LogBuf);
	}

#ifdef WIN32
	closesocket(mySocket);
	WSACleanup();
#else
	close(mySocket);
#endif

	return 0;
}


int main(int argc, char **argv)
{
	if (argc != 6)
	{
		//printf("argc(%d) != 6\n", argc);
		printf("[Usage]\n%s   EmailServer   To   From   Subject   Message\n", argv[0]);
		string examArgs = "   gmail-smtp-in.l.google.com"
			"   ysoftman@gmail.com"
			"   ysoftman@naver.com"
			"   \"sendmail ���α׷� �׽�Ʈ\""
			"   \"�׽�Ʈ ���� �����Դϴ�.\"";
		printf("\n[Example]\n%s %s\n", argv[0], examArgs.c_str());

		string desc = "�޴� ����� ���� ������ ���� �������̾�� �Ѵ�.\n"
			"���� ������ �� ��� �ܼ�(cmd.exe) ���� nslookup -querytype=mx �����θ� ���� Ȯ�� �� �� �ִ�.\n"
			"��) nslookup -querytype=mx gmail.com";

		printf("\n[Tip]\n%s\n", desc.c_str());
		return 0;
	}


	if (argc == 6)
	{
		printf("EmailServer : %s\n", argv[1]);
		printf("To : %s\n", argv[2]);
		printf("From : %s\n", argv[3]);
		printf("Subject : %s\n", argv[4]);
		printf("Message : %s\n", argv[5]);
		
		printf("sending... ");
		if (SendMail(argv[1], argv[2], argv[3], argv[4], argv[5]) == 0)
		{
			printf("Success.\n");
		}
		else
		{
			printf("Fail.\n");
		}
	}

	return 0;
}

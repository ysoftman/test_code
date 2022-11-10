////////////////////////////////////////////////////////////////////////////////////
// title : sendmail
// desc : 윈도우 콘솔에서 간단한 메일 보내는 프로그램
// author : ysoftman
// os : Windows
////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

// E-mail 보내는 함수
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

	// 메일 보내기 로그
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
	dest_addr.sin_port = htons(25);				// Port 설정

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

	// SMTP 프로토콜을 사용하여 메일 보내기
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 환영 메세지 받음
	LogBuf[Received] = '\0';	
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "HELO google.co.kr\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 환영 메세지 보냄

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';	
	fputs(LogBuf, fpSmtpLog);
	sprintf(EmailBuf, "MAIL FROM:<%s>\n", EmailFrom);
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 보내는 사람 주소 보냄

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	sprintf(EmailBuf, "RCPT TO:<%s>\n", EmailTo);
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 받는 사람 주소 보냄

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "DATA\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 메일 데이터 보냄

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
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
	strcat(EmailBuf, "\r\n.\r\n");							// 메일 내용은 <CRLR>.<CRLR>로 끝나야 함.
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 제목과 내용 보냄

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "QUIT\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 종료 메세지 보냄

	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
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
			"   \"sendmail 프로그램 테스트\""
			"   \"테스트 메일 내용입니다.\"";
		printf("\n[Example]\n%s %s\n", argv[0], examArgs.c_str());

		string desc = "받는 사람은 메일 서버와 같은 도메인이어야 한다.\n"
			"메일 서버를 모를 경우 콘솔(cmd.exe) 에서 nslookup -querytype=mx 도메인명 으로 확인 할 수 있다.\n"
			"예) nslookup -querytype=mx gmail.com";

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

////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// linux function test
////////////////////////////////////////////////////////////////////////////////////
#ifdef linux
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>

// copy fileA to fileB
static bool SimpleCopyFile(const char *srcpath, const char *dstpath)
{
	int fd_src;
	int fd_dst;
	struct stat stat_buf;
	off_t offset = 0;

	fd_src = open(srcpath, O_RDONLY);
	if (fd_src == -1)
	{
		return false;
	}
	fstat(fd_src, &stat_buf);
	fd_dst = open(dstpath, O_WRONLY | O_CREAT, stat_buf.st_mode);
	if (fd_dst == -1)
	{
		return false;
	}
	sendfile(fd_dst, fd_src, &offset, stat_buf.st_size);

	close(fd_src);
	close(fd_dst);

	return true;
}

void SignalHandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("Ctrl+C pressed.\n");
	}
}

int main()
{
	// set signalhandler
	//signal(SIGINT, SignalHandler);	

	// get host name
	char hostname[256];
	size_t hostnamelen = 256;
	if (gethostname(hostname, hostnamelen) == -1)
	{
		printf("can't read host name\n");
	}
	else
	{
		printf("%s\n", hostname);
	}

	// get ip address
	struct ifaddrs *ifp = NULL;
	if (getifaddrs(&ifp) < 0)
	{
		printf("getifaddrs() fail\n");
		return -1;
	}
	struct ifaddrs *ifa = NULL;
	for (ifa=ifp; ifa; ifa = ifa->ifa_next)
	{
		socklen_t salen;
		char ip[125];
		if (ifa->ifa_addr->sa_family == AF_INET)
		{
			salen = sizeof(struct sockaddr_in);
		}
		if (getnameinfo(ifa->ifa_addr, salen, ip, sizeof(ip), NULL, 0, NI_NUMERICHOST) < 0)
		{
			continue;
		}
		printf("ip : %s\n", ip);
	}

	// get current time
	printf("%d\n", (int)time(NULL));

	// get current date
	time_t CurrentTime;
	memset(&CurrentTime, 0, sizeof(CurrentTime));
	time(&CurrentTime);
	struct tm *stCurrentTime = localtime(&CurrentTime);
	char szDate[32];
	memset(szDate, 0, sizeof(szDate));
	snprintf(szDate, sizeof(szDate), "%04d-%02d-%02d %02d-%02d-%02d", stCurrentTime->tm_year+1900, stCurrentTime->tm_mon+1, stCurrentTime->tm_mday, stCurrentTime->tm_hour, stCurrentTime->tm_min, stCurrentTime->tm_sec);
	printf("%s\n", szDate);

	// get current path
	char resolved_path[256];
	memset(resolved_path, 0, sizeof(resolved_path));
	realpath(".", resolved_path);
	printf("%s\n", resolved_path);	

	// get file status
	char *path = (char*)"/home/ysoftman/a.txt";
	struct stat filest;
	if (stat(path, &filest) == 0)
	{
		printf("%s is exist.\n", path);
	}
	else
	{
		printf("%s is not exist.\n", path);
	}

	// get module(file) name
	char id[32];
	memset(id, 0, sizeof(id));
	sprintf(id, "/proc/%d/exe", getpid());
	printf("%s\n", id);
	memset(resolved_path, 0, sizeof(resolved_path));
	readlink(id, resolved_path, 256);
	printf("%s\n", resolved_path);

	// create directory
	char *path2 = (char*)"/home/ysoftman/abcd";
	if (mkdir(path2, 0755) == 0)
	{
		printf("create directory success => %s\n", path2);
	}
	else
	{
		printf("create directory fail => %s\n", path2);
	}

	// ctrl+c
	printf("press Ctrl+C to exit program...\n");
	while(1)
	{
		sleep(1);
	}

	return 0;
}
#endif


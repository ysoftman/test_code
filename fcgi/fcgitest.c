#include <stdio.h>
#include <stdlib.h>
#include "fcgi_stdio.h"

int main()
{
	while (FCGI_Accept() >= 0)
	{
		printf("Content-type: text/html\r\n"
				"\r\n"
				"<h1>fastcgi test</h1>"
				"\r\n");
	}
	return 0;
}

			

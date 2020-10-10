// ysoftman
// 아래는 strtok() 함수를 이용해서 토큰을 가져오는 코드이다.
// strtok()은 입력문자열(첫번째인자)에서 구분자문자들(두번째인자)로 구분될 수 있는 토큰을 찾아 준다.
// strtok()를 한번 호출하면 입력문자열의 첫번째 토큰을 찾아준다.
// 그렇다면 두번째, 세번째... 문자열의 끝까지 토큰을 계속해서 얻어오려면 어떻게 해야 될까?
// 아래 코드처럼 연속 토큰을 추출하려면 처음 strtok() 로 첫번째 토큰을 찾고
// 그 다음부터는 strtok(NULL, 구분자)로 호출하여 연속되는 토큰을 계속 찾을 수 있다.
// 여기서 한가지 의문의 생긴다... 입력문자열에 NULL 값을 집어넣는데 어떻게 토큰을 계속 찾을 수 있을까?
// strtok() 내부에서는 토큰을 찾고 찾은 토큰 바로 뒤의 문자를 NULL 로 만들어 버린다.
// 즉 입력 문자열이 되어 strtok() 사용전 입력문자열를 복사해두고 사용해아 한다.
// 처음 strtok() 를 호출할 때 strtok() 함수 내부에서 첫번째 토큰을 리턴하기 전 NULL 다음부터의 문자열을 기억하고 있는다.
// 두번째 strtok() 를 호출할 때 입력문자열 대신 NULL 값을 주면 바로 이전에 사용되었던 문자열을 끄집어내서 사용하게 된다.

#include <stdio.h>
#include <string.h>

int main()
{
	char str[50] = "My name is Byoung Hoon,,, Yoon...";
	char *pToken = NULL;
	// 구분자로 공백 , . 등 여러개를 사용할 수 있다.
	const char Separator[] = " ,.";
	printf("1) %s  (Separator:%s)\n", str, Separator);
	pToken = strtok(str, Separator);
	printf("%s\n", pToken);
	while ((pToken = strtok(NULL, Separator)) != NULL)
	{
		printf("%s\n", pToken);
	}

	// str 이 변경되어 재사용할 수 없다.
	printf("2) %s  (Separator:%s)\n", str, Separator);

	for (int i = 0; i < 50; ++i)
	{
		if (str[i] == '\0')
			printf("_");
		else
			printf("%c", str[i]);
	}
	printf("\n");

	pToken = strtok(str, Separator);
	printf("%s\n", pToken);
	while ((pToken = strtok(NULL, Separator)) != NULL)
	{
		printf("%s\n", pToken);
	}

	return 0;
}

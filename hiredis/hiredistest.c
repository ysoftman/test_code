#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./hiredis/hiredis.h"

// hiredis 설치
// git clone https://github.com/redis/hiredis.git
// cd hiredis
// make
// sudo make install
// ldconfig
// 빌드시 makefile 에 -lhiredis 옵션 추가


//hiredis 를 이용한 redis 테스트(hiredis example 소스 발췌)
int test_hiredis()
{
    unsigned int j;
    redisContext *c;
    redisReply *reply;
    const char *hostname = "127.0.0.1";
    int port = 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* PING server */
    reply = (redisReply*)redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

    /* Set a key */
    reply = (redisReply*)redisCommand(c,"SET %s %s", "foo", "hello world");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    /* Set a key using binary safe API */
    reply = (redisReply*)redisCommand(c,"SET %b %b", "bar", (size_t) 3, "hello", (size_t) 5);
    printf("SET (binary API): %s\n", reply->str);
    freeReplyObject(reply);

    /* Try a GET and two INCR */
    reply = (redisReply*)redisCommand(c,"GET foo");
    printf("GET foo: %s\n", reply->str);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(c,"INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);
    /* again ... */
    reply = (redisReply*)redisCommand(c,"INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);

    /* Create a list of numbers, from 0 to 9 */
    reply = (redisReply*)redisCommand(c,"DEL mylist");
    freeReplyObject(reply);
    for (j = 0; j < 10; j++) {
        char buf[64];

        snprintf(buf,64,"%d",j);
        reply = (redisReply*)redisCommand(c,"LPUSH mylist element-%s", buf);
        freeReplyObject(reply);
    }

    /* Let's check what we have inside the list */
    reply = (redisReply*)redisCommand(c,"LRANGE mylist 0 -1");
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (j = 0; j < reply->elements; j++) {
            printf("%u) %s\n", j, reply->element[j]->str);
        }
    }
    freeReplyObject(reply);

    /* Disconnects and frees the context */
    redisFree(c);

    return 0;
}


int main()
{
	int	ysoftman_is_very_good_persion = 0;
	ysoftman_is_very_good_persion = 10;
	printf("ysoftman_is_very_good_persion : %d\n", ysoftman_is_very_good_persion);
	printf("RAND_MAX(%d)\n",RAND_MAX);


	for (int i = 0; i<100; i++)
	{
		int value = rand();
		printf("랜덤값(%d)\n", value);
		value = value%100000;
		printf("랜덤값(%d)\n", value);
	}
	int a = 1;
	long b = 1;
	long long c = 1;
	printf("sizeof(int) = %lu\n", sizeof(a));
	printf("sizeof(long) = %lu\n", sizeof(b));
	printf("sizeof(long long) %lu\n", sizeof(c));


	test_hiredis();
	return 0;
}



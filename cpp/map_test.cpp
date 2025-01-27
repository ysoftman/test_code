/*
author: ysoftman
title: map 관련 테스트
*/
#include <stdio.h>

#include <iostream>
#include <map>

using namespace std;

struct aa {
    int a;
    long b;
};

struct aa my = {10, 200};

int main() {
    int a = 10;
    printf("a=%d\n", a);
    std::cout << "a=" << a << std::endl;
    std::cout << "my.a:" << my.a << std::endl;
    std::cout << "my.b:" << my.b << std::endl;

    map<int, int> mymap;
    map<int, int>::iterator iter;
    mymap[0] = 1;
    mymap[1] = 2;
    mymap[2] = 3;

    // insert() 는 키가 존재한다면 추가하지 않는다.
    mymap.insert(make_pair(2, 5));

    // count() 는 맵의 키에 매칭되는 원소를 카운트하지만
    // map 의 키는 유니크해서 매칭되는 카운트는 1, 없으면 0만 올 수 있다.
    printf("mymap count elements : %lu\n", mymap.count(2));
    for (iter = mymap.begin(); iter != mymap.end(); iter++) {
        printf("mymap[%d] = %d\n", (*iter).first, (*iter).second);
    }

    //////////

    map<int, int> mapTest;
    // map<int, int>::iterator iter;

    printf("-- map 설정 값 테스트 --\n");
    int index = 1000;
    for (int i = 0; i < index; i++) {
        mapTest[i] = i;
    }
    printf("mapTest[%d] ~ [%d] 설정 완료\n", index - 1, mapTest[index - 1]);
    printf("mapTest[%d] = %d 설정된 값\n", index - 1, mapTest[index - 1]);
    // set 하지 않은 곳은 NULL 로 되어있다.
    printf("mapTest[%d] = %d 미설정시 값은 디폴트 NULL(0) 로 추가\n", index, mapTest[index + 1]);

    printf("\n");
    printf("-- map find() 테스트 --\n");

    int key = 5;
    iter = mapTest.find(key);
    printf("mapTest.find(%d) .. %d\n", key, iter->second);

    mapTest.erase(key);
    printf("mapTest.erase(%d) .. ok\n", key);

    iter = mapTest.find(key);
    // iter 값이 invalid
    printf("mapTest.find(%d) .. %d\n", key, iter->second);

    return 0;
}

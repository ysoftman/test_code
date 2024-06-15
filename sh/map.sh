#/bin/bash
# map 만들기
#
# associatgive array variable 로 선언해야 한다.
declare -A map
map["key1"]="lemon"
map["key2"]="apple"
map["key3"]=123

# value 만 파악
for value in ${map[@]}; do
    echo 'value:' $value
done

# key 만 파악
for key in ${!map[@]}; do
    echo 'key:' $key, 'value:'${map[$key]}
done

# update
map["key3"]="zzz123"
for key in ${!map[@]}; do
    echo 'key:' $key, 'value:'${map[$key]}
done


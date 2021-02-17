# shell script 파일을 cat 으로 생성할 경우
# \ $ ` 는 \ 로 처리해야 누락되지 않는다.
rm -rf cat_delimiter.test.sh
# cat > cat_delimiter.test.sh << zzz
# #!/bin/sh
# var1="ysoftman"
# echo "\$var1"
# zzz

# 또는 구분자를 'zzz' 또는 "zzz" 로 묶어서 구분한다.
# zzz 를 입력되기 까지 모든 내용을 cat 입력(<<)으로 받고
# cat 은 입력받은 내용을 stout 출력하는데 > 를 통해 파일에 쓴다.
# here-document(heredoc, https://en.wikipedia.org/wiki/Here_document)
cat > redirect.test.sh << 'zzz'
#!/bin/sh
var1="ysoftman"
echo "$var1"
zzz


# heredoc 의 내용을 파이프(|)로 전달 할 수 도 있다.
cat << zzz | xargs echo "args->$*"
apple
lemon
banana
123
orange
zzz


# <<< $'' 을 사용하면 명령에 stdin 을 전달할 수 있다.
# 다음 pipe 이용 방법과 같다. 
# echo -e 'bill\npassword123' | bash read_password_test.sh
bash read_password_test.sh <<< $'bill\npassword123'

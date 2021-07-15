#!/bin/bash

# file descriptor id
# 0 - stdin
# 1 - stdout
# 2 - stderr

# https://www.gnu.org/software/bash/manual/html_node/Redirections.html
# [n]<> redirection 은 파일을 read, write 둘다 사용되도록 오픈한다.
# redirect.open_read_write.txt 파일이 존재 하지 않으면 삭제된다.
echo "ysoftman" 1<> redirect.open_read_write.txt
rm -f redirect.open_read_write.txt


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
# cat 은 입력받은 내용을 stdout으로 출력하는데 > 를 통해 파일에 쓴다.
# here-document(heredoc, https://en.wikipedia.org/wiki/Here_document)
cat > redirect.test.sh << 'zzz'
#!/bin/sh
var1="ysoftman"
echo "$var1"
zzz
echo "[cat redirect.test.sh]"; cat redirect.test.sh
echo "[rm redirect.test.sh]"; rm -f redirect.test.sh

# heredoc 은 2단계로 수행된다.
# 1. open file.txt
# 2. cat (> or >>) file.txt
# sudo 명령이 필요한 경우
# sudo cat > /etc/redirect.test.sh << 'zzz' ...
# 1. /etc/redirect.test.sh 파일은 현재 사용자 계정으로 오픈하고
# 2. 그 후에 sudo cat 명령을 실행하게 되어 permission denied 가 된다.
# 그래서 다음과 같이 bash -c 로 묶어 처리해야 한다.
sudo bash -c "cat > /etc/redirect.test.sh" << 'zzz'
#!/bin/sh
var1="ysoftman"
echo "$var1"
zzz
echo "[cat /etc/redirect.test.sh]"; cat /etc/redirect.test.sh
echo "[rm /etc/redirect.test.sh]"; sudo rm /etc/redirect.test.sh

echo ""
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

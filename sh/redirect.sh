#!/bin/bash

# file descriptor id
# 0 - stdin
# 1 - stdout
# 2 - stderr

# << 는 here-document(heredoc, https://en.wikipedia.org/wiki/Here_document)를 사용하겠다는 뜻
# <<< 는 heredoc string(스트링 한줄 한번만 입력)를 사용하겠다는 뜻
# cat << ysoftman
# > aaa
# > bbb
# > ysoftman 입력하면 끝
# cat <<< ysoftman
# ysoftman 출력후 끝


# https://www.gnu.org/software/bash/manual/html_node/Redirections.html
# [n]<> redirection 은 파일을 read, write 둘다 사용되도록 오픈한다.
# redirect_open_read_write_test.txt 파일이 존재 하지 않으면 삭제된다.
echo "ysoftman" 1<> redirect_open_read_write_test.txt
echo "[cat redirect_open_read_write_test.txt]"; cat redirect_open_read_write_test.txt
echo "[rm -f redirect_open_read_write_test.txt]"; rm -f redirect_open_read_write_test.txt

# zzz 를 입력되기 까지 모든 내용을 cat 입력(<<)으로 받고
# cat 은 입력받은 내용을 stdout으로 출력하는데 > 를 통해 파일에 쓴다.
# cat > redirect_script_test.sh << zzz
# 또는 << zzz 를 먼저 명시해도 되고 구분자를 'zzz' 또는 "zzz" 로 묶어서도 구분
cat << 'zzz' > redirect_test.sh
#!/bin/sh
var1="ysoftman"
echo "$var1"
zzz
echo "[cat redirect_test.sh]"; cat redirect_test.sh
echo "[rm -f redirect_test.sh]"; rm -f redirect_test.sh

# heredoc 은 2단계로 수행된다.
# 1. open file.txt(랜덤 파일 생성)
# 2. cat (> or >>) file.txt
# sudo 명령이 필요한 경우
# sudo cat > /etc/redirect_sudo_test.sh << 'zzz' ...
# 1. /etc/redirect_sudo_test.sh 파일은 현재 사용자 계정으로 오픈하고
# 2. 그 후에 sudo cat 명령을 실행하게 되어 permission denied 가 된다.
# 그래서 다음과 같이 bash -c 로 묶어 처리해야 한다.
sudo bash -c "cat > /etc/redirect_sudo_test.sh" << 'zzz'
#!/bin/sh
var1="ysoftman"
echo "$var1"
zzz
echo "[cat /etc/redirect_sudo_test.sh]"; cat /etc/redirect_sudo_test.sh
echo "[sudo rm /etc/redirect_sudo_test.sh]"; sudo rm /etc/redirect_sudo_test.sh

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

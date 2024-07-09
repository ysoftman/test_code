#!/bin/zsh
# zsh 다른 테마의 프롬프트를 사용하기 source 로 현재 쉘에 반영해야 한다.
# . ./change_zsh_prompt.zsh

# autoload 는 ksh autoloader를 Bash로 포팅한것으로
# 함수 선언시 사용하면 함수를 호출할때 외부파일에서 로드한다.
# promptinit() 는 /usr/share/zsh/5.3/functions/promptinit 파일에 정의되어 있다.
# -U alias expansion 확장 비활성화
# -z zsh 에서 사용
# 참고 man zshbuiltins
autoload -Uz promptinit; promptinit
if [ -f ${HOME}/.zprezto/init.zsh ]; then; source ${HOME}/.zprezto/init.zsh; fi
current_theme=$(prompt -c | grep -v Current | tr -d ' ')
prompt_list=($(prompt -l | grep -v Current))
for ((i=1;i<=${#prompt_list};i++)); do
    echo $current_theme ${prompt_list[$i]}
    if [[ $current_theme == ${prompt_list[$i]} ]]; then
        choice=$(($i+1))
        break
    fi
done
if (( $choice > ${#prompt_list} )); then
    choice=1
fi
peek_random_prompt=${prompt_list[$choice]}
echo $choice $peek_random_prompt
prompt $peek_random_prompt

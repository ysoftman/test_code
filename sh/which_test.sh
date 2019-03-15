#!/bin/bash

# zsh 에서 gcc nocorrect 로 alias 되어 있다고 나오면서 위치가 안나온다.
# which gcc
# gcc: aliased to nocorrect gcc

# -a 으로 모든 실행 가능한 인스턴스 리스트를 출력하면 보이긴 한다.
which -a gcc
# gcc: aliased to nocorrect gcc
# /usr/bin/gcc

# zsh 에서 gcc 다음과 같이 alias 하고 있다.
# gcc='nocorrect gcc'

# zsh 은 오타에 대해 다음처럼 교정할 수 있다.
# cleary
# zsh: correct cleary to clear [nyae]?

# nocorrect 는 zsh 에서 명령어 앞에 선언하는 수정자로
# gcc 글자에 대해선 스펠 교정을 하지 않게 한다.
# http://bolyai.cs.elte.hu/zsh-manual/zsh_5.html#SEC19

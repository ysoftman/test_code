# glob test

```bash
# *(와이들카드), .sh(패턴)의 glob(global) 사용
ls -ahl *.sh

# extended glob 활성화(bash)
shopt -s extglob

# extended glob 활성화(zsh)
# setopt extendedglob
setopt extended_glob
setopt EXTENDEDGLOB


# ?(패턴) : 0번 또는 1번
# *(패턴) : 0번 이상이상
# +(패턴) : 1번 이상
# @(패턴) : 1번
# !(패턴) : 패턴외

# sed 또는 aaa 가 포함된 파일
ls -l *(sed|aaa)*
```

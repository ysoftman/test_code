# cpp test

- 테스트코드 실행

```bash
# x86
g++ hello_world.cpp && ./a.out

# mac arm64 에서 clang(llvm) 설치해서 사용하는 경우
brew install llvm
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
clang++ hello_world.cpp && ./a.out

# mac arm64 에서 gcc 설치해서 사용하는 경우
brew install gcc
# /opt/homebrew/bin/g++-14
g++-14 hello_world.cpp && ./a.out
```

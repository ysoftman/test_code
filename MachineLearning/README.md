# MachineLearning 테스트

ML(MachineLearning) 관련 테스트 코드들입니다.

## 실행 환경

- 설치

```bash
# pip 설치
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
sudo python get-pip.py
sudo python3 get-pip.py
# pip3가 생성되지 않으면 복사하고 첫줄을 변경해서 써도 된다.
cp /usr/local/bin/pip /usr/local/bin/pip3
vi /usr/loca/bin/pip3
#!/usr/local/opt/python3/bin/python3

# 패키지 설치
sudo pip3 install sklearn scikit-learn numpy matplotlib pandas pillow seaborn graphviz tensorflow jupyter
# jupyter 는 설치 에러 발생시
sudo pip3 install --upgrade --force-reinstall --no-cache-dir jupyter

# .ipynb 인경우 jupyter notebook 실행
# http://localhost:8888/?token=xxx 으로 접속
jupyter notebook
```

- 2018-10 현재 tensowflow 는 python 3.7 을 지원하지 않아 python 3.6.5 로 다운그레이드가 필요하다.

```bash
# 현재 python 3.7 링크 제거
brew unlink python
# python 3.6.5 버전 설치
brew install https://raw.githubusercontent.com/Homebrew/homebrew-core/f2a764ef944b1080be64bd88dca9a1d80130c558/Formula/python.rb
```

- tensorflow r1.0 정식 릴리즈 이후 버전과 이전은 몇몇 api 들이 인자들의 개수나 순서가 다르다.
- 인터넷의 많은 자료가 아직 1.0 정식 릴리즈전의 tensorflow 버전으로 설명하고 있다.
- ipython(jupyter) notebok(.ipynb) -> python(.py) 변환

```bash
bash convert_ipynb_to_py.sh
```

## 책,강의 내용 정리

- [book - deeplearning from scratch 정리](deeplearning_from_scratch.md)
- [kmooc - kmooc_2018_인공지능_및_기계학습](kmooc_2018_인공지능_및_기계학습.md)
- [kmooc - kmooc_2019_인공지능의_기초](kmooc_2019_인공지능의_기초.md)

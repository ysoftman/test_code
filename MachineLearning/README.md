# MachineLearning 테스트

ML(MachineLearning) 관련 테스트 코드들입니다.

## 실행 환경

```bash
# 파이썬 패키지 설치
python -m pip install --upgrade pip
sudo pip install sklearn scikit-learn numpy matplotlib pandas seaborn graphviz
sudo pip3 install sklearn scikit-learn numpy matplotlib pandas seaborn graphviz
# tensorflow jupyter 는 설치 에러 발생시
sudo pip3 install --upgrade --force-reinstall --no-cache-dir jupyter
sudo pip3 install https://storage.googleapis.com/tensorflow/mac/cpu/tensorflow-1.10.1-py3-none-any.whl

# .ipynb 인경우 jupyter notebook 실행
# http://localhost:8888/?token=xxx 으로 접속
jupyter notebook
```

- tensorflow r1.0 정식 릴리즈 이후 버전과 이전은 몇몇 api 들이 인자들의 개수나 순서가 다르다.
- 인터넷의 많은 자료가 아직 1.0 정식 릴리즈전의 tensorflow 버전으로 설명하고 있다.

## 책,강의 내용 정리

- [deeplearning from scratch 정리](deeplearning_from_scratch.md)
- [kmooc - 기계학습 정리](kmooc_machine_learning.md)

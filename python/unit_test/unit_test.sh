#!/bin/bash
# 유닛테스트 실행하기
# 방법1 - main 에서 unittest.main 을 호출하는 경우 그냥 코드 실행
python unit_test.py
python test1/test1.py

# 방법2 - unittest 모듈 이용
# 파일 명시할때 ./ 로 시작하면 안된다.
python -m unittest -v unit_test
python -m unittest -v test1/test1.py
python -m unittest -v test1/*.py

# 방법3 - green 패키지 사용
# pip install green
# python 실행시 다음과 같이 green 으로 수행하면 된다.
# -v 옵션에 v 가 많을 수록 좀더 자세한 결과가 보여진다.
green -vv python unit_test.py
green -vv python test1/test1.py


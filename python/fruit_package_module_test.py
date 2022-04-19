# 패키지(모듈이 모인 디렉토리)가이닌 모듈이 같은 경로에 있는 경우
# import fruite_module as fm
# alias 로 패키지.모듈 사용하기
import fruite_package.fruit_module as fm
fm.fruit.apple(100)
fm.fruit.lemon("2000")

# 패키지.모듈 전체 사용하기
from fruite_package.fruit_module import *
fruit.apple(100)

# 패키지.모듈 중 fruit 클래스를 fr 이름으로 사용
from fruite_package.fruit_module import fruit as fr
fr.lemon(200)
fr.apple(50)
fr.orange(100)


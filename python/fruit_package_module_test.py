# 패키지(모듈이 모인 디렉토리)가 아닌 모듈이 같은 경로에 있는 경우
# import fruite_module as fm
# alias 로 패키지.모듈 사용하기
import fruite_package.fruit_module as fm

# 패키지.모듈 중 fruit 클래스를 fr 이름으로 사용
from fruite_package.fruit_module import fruit as fr

fm.fruit.apple(100)
fm.fruit.lemon("2000")
fm.fruit.orange(300)

fr.apple(100)
fr.lemon("2000")
fr.orange(300)

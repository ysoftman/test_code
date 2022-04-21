# import 패키지.모듈
# import ..패키지  # 상위에 있는 패키지 사용시
# 모듈.변수,메소드,클래스 사용해야 한다.
import datetime
print(datetime.date(2010, 12, 31))

# from 패키지.모듈 import 변수,메소드,클래스
# 변수,메소드,클래스만 명시해 사용할 수 있다.
# from datetime import *
# 또는
from datetime import date
print(date(2010, 12, 31))

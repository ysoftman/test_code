#!/bin/bash

# 참고 diff
diff <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")

# common 2개의 파일내용(정렬된)을 비교해 다음의 3개열로 표시한다.
# 첫번째열: 첫번째 파일에만 있는 내용
# 두번째열: 두번째 파일에만 있는 내용
# 세번째열: 공통으로 있는 내용
echo "====="
comm <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")

# -1 첫번째열 숨김(숨겨진 열만큼 indent 가 줄어든다.)
# -12 첫번째열,두번째열 숨김
echo "====="
comm -1 <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")
echo "====="
comm -2 <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")
echo "====="
comm -3 <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")
echo "====="
comm -12 <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")
echo "====="
comm -13 <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")
echo "====="
comm -23 <(echo -e "a\nb\nc") <(echo -e "a\n\b\nd\ne")

# blogger 관리

## 포스트 관련

- 포스팅 중 line-height 스타일 제거

  ```bash
  #  <title type='text'> 부분들 엔터(newline추가)
  sed -i '.backup' -e 's/<title type/\
  <title type/g' blog-07-03-2019.xml
  # line-height 적용된 포스트의 타이틀 파악
  rg 'line-height' blog-07-03-2019.xml | sed -e "s/<title   type=\'text\'>//g" -e "s/<\/title>.*//"
  ```

- 파악된 blogger post line-height, div, span, style 속성등 수정

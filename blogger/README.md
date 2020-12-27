# blogger 관리

## 테마 파일(.html) 관련

- 테마 파일을 vscode 로 수정 후 적용하기 위해 blogger_theme.html 로 저장함
- 모바일 편의성 관련 오류 수정, 리포팅 : [google search console](https://search.google.com/search-console/?resource_id=sc-domain:yoonbh2714.blogspot.com)
  - 클릭할 수 있는 요소가 서로 너무 가까움
  - 표시 영역이 '기기 폭'으로 설정되어 있지 않음
  - 콘텐츠 폭이 화면 폭보다 넓음
  - 텍스트가 너무 작아 읽을 수 없음

- 모바일 블로그 화면에서 포스트에 삽입된 이미지가 포스트 영역을 넘어서 보이는 경우 수정

  ```css
  /* 포스트 이미지 속성 최대폭 및 그에 따른 높이 비율 자동 설정 */
  .post-body img
  max-width: 100%;
  height: auto;
  ```

## 포스트 백업 파일(.xml) 관련

- 포스팅 중 line-height 스타일 제거

  ```bash
  #  <title type='text'> 부분들 엔터(newline추가)
  sed -i '.backup' -e 's/<title type/\
  <title type/g' blog-07-03-2019.xml
  # line-height 적용된 포스트의 타이틀 파악
  rg 'line-height' blog-07-03-2019.xml | sed -e "s/<title   type=\'text\'>//g" -e "s/<\/title>.*//"
  ```

- 파악된 blogger post line-height, div, span, style 속성등 수정

# blogger 관리

## blogger theme

- blogger 테마를 파일을 vscode 로 수정 후 적용하기 위해 파일로 저장함
- 모바일 편의성 관련 오류 수정, 리포팅 : [google search console](https://search.google.com/search-console/?resource_id=sc-domain:yoonbh2714.blogspot.com)
  - 클릭할 수 있는 요소가 서로 너무 가까움
  - 표시 영역이 '기기 폭'으로 설정되어 있지 않음
  - 콘텐츠 폭이 화면 폭보다 넓음
  - 텍스트가 너무 작아 읽을 수 없음

## 블로그 포스팅 중 line-height 스타일 제거

```bash
# 블로그 백업(.xml)을 vscode 로 열고,
# <title type='text'> 부분들 선택후 엔터(newline추가)
# line-height 적용된 포스트의 타이틀 파악
rg 'line-height' blog-07-02-2019.xml | awk '{print $2$3}' | tr -d "type=\'text\'>"
```

- 파악된 blogger post line-height 수정

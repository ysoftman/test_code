# blogger 관리

## blogger > 설정 > 콘텐츠 백업(.xml)에서 조회(google takeout 으로 백업바뀌면서 구글 드라이브에 저장)

```bash
# xml formatting(newline,indentation)
# 예전에 사용됐던 백업 파일 형식
# xmllint --format blog-10-26-2023.xml > blog.xml
# google takeout .zip 다운로드 후
xmllint --format feed.atom > blog.xml

# 포스트 제목 리스트(댓글도 포함되어 있음)
rg -N '<title.+</title>' blog.xml

# line-height 적용된 포스트의 타이틀 파악
rg -N '<title.+</title>|<content type="html">.*</content>' blog.xml | rg -N " line-heightyle" -B1

# style 적용된 포스트의 타이틀 파악
rg -N '<title.+</title>|<content type="html">.*</content>' blog.xml | rg -N " style=" -B1
```

## blogger api 관련

- apikey: <https://developers.google.com/blogger/docs/3.0/using?hl=ko#APIKey>
- api doc: <https://developers.google.com/blogger/docs/3.0/reference/posts/list?hl=ko>

```bash
apikey=""

# bloggerid 파악
curl -s "https://www.googleapis.com/blogger/v3/blogs/byurl?url=https://yoonbh2714.blogspot.com&key=${apikey}"

bloggerid=""

# post 조회
curl -s "https://www.googleapis.com/blogger/v3/blogs/${bloggerid}/posts?key=${apikey}"

# post title 만 조회
# maxResults=500 (500개까지만 된다)
curl -s "https://www.googleapis.com/blogger/v3/blogs/${bloggerid}/posts?key=${apikey}&maxResults=500" | jq ".items[].title"

# music 태그 포스트들의 title, id 필드만 조회
curl -s "https://www.googleapis.com/blogger/v3/blogs/${bloggerid}/posts?key=${apikey}&labels=music&maxResults=500" | jq '.items[] | "\(.title) --> \(.id)"'
```

## theme

- blogger 설정 > 테마 > 맞춤설정 > html 편집, 내용은 theme.xml 참고

## tags 페이지 만들기

- tag 가젯 사용지 전체 태그를 표시하면 포스트 내용보타 커져 스팸으로 취급될 수 있어 tags 이름의 페이지를 만든다.
- blogger 설정 > 페이지 > tags 이름으로 페이지 생성, 내용은 tags.html 참고

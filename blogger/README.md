# blogger 관리

## blogger > 설정 >  콘텐츠 백업(.xml)에서 조회

```bash
# xml formatting(newline,indentation)
xmllint --format blog-10-26-2023.xml > blog.xml

# 포스트 제목 리스트(댓글도 포함되어 있음)
rg -N '<title type="text">.*</title>' blog.xml

# line-height 적용된 포스트의 타이틀 파악
rg -N '<title type="text">.*</title>|<content type="html">.*</content>' blog.xml | rg -N "line-heightyle" -B1

# style 적용된 포스트의 타이틀 파악
rg -N '<title type="text">.*</title>|<content type="html">.*</content>' blog.xml | rg -N "style=" -B1
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


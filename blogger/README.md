# blogger 관리

## 백업된 포스트(.xml) 관련

- blogger post line-height, div, span, style 속성 파악

```bash
# line-height 적용된 포스트의 타이틀 파악
sed -e "s/<title type='text'>/\n/g" ./blog-09-11-2023.xml | rg "line-height" | sed -e "s/<\/title>.*//g"

# style 적용된 포스트의 타일틀 파악
sed -e "s/<title type='text'>/\n/g" ./blog-09-11-2023.xml | rg "style=" | sed -e "s/<\/title>.*//g"
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


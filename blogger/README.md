# blogger 관리

## 포스트 관련

- blogger post line-height, div, span, style 속성  파악

```bash
# line-height 적용된 포스트의 타이틀 파악
sed -e "s/<title type='text'>/\n/g" ./blog-09-11-2023.xml | rg "line-height" | sed -e "s/<\/title>.*//g"

# style 적용된 포스트의 타일틀 파악
sed -e "s/<title type='text'>/\n/g" ./blog-09-11-2023.xml | rg "style=" | sed -e "s/<\/title>.*//g"
```


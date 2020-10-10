# shell script 파일을 cat 으로 생성할 경우
# \ $ ` 는 \ 로 처리해야 누락되지 않는다.
rm -rf cat_delimiter.test.sh
# cat > cat_delimiter.test.sh << zzz
# #!/bin/sh
# var1="ysoftman"
# echo "\$var1"
# zzz

# 또는 구분자를 'zzz' 또는 "zzz" 로 묶어서 구분한다.
cat > cat_delimiter.test.sh << 'zzz'
#!/bin/sh
var1="ysoftman"
echo "$var1"
zzz

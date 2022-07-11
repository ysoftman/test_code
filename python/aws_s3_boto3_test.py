# boto3 test
# pip install boto3, tqdm
import os
from tqdm import tqdm
import boto3


AWS_URL = "https://s3.amazonaws.com"
AWS_REGION = "ap-northeast-2"
AWS_ACCESS_KEY_ID = ""
AWS_SECRET_ACCESS_KEY = ""
AWS_BUCKET = ""
client = boto3.client(
    "s3",
    endpoint_url=AWS_URL,
    region_name=AWS_REGION,
    aws_access_key_id=AWS_ACCESS_KEY_ID,
    aws_secret_access_key=AWS_SECRET_ACCESS_KEY,
)


filename = "ysoftman_10MB"
# 업로드 테스트용 더미 파일 생성
os.system(f"dd if=/dev/urandom of={filename} bs=1024 count=10000")

file_size = os.path.getsize(filename)
pbar = tqdm(
    unit="B",
    unit_scale=True,
    total=file_size,
    desc=f"[upload] {file_size}",
    mininterval=0.1,
)

path = f"/test/{filename}"
# / 로 시작하면 업로드 후 파일이 없는것으로 표시된다.
path = path.lstrip("/")

# upload to s3
client.upload_file(
    Filename=filename,
    Bucket=AWS_BUCKET,
    Key=path,
    Callback=lambda bytes_transferred: pbar.update(bytes_transferred),
)

download_filename = "zzz_ysoftman_10MB"
pbar = tqdm(
    unit="B",
    unit_scale=True,
    total=file_size,
    desc=f"[download] {file_size}",
    mininterval=0.1,
)

# download from s3
client.download_file(
    Bucket=AWS_BUCKET,
    Key=path,
    Filename=download_filename,
    Callback=lambda bytes_transferred: pbar.update(bytes_transferred),
)


os.remove(f"{filename}")
os.remove(f"{download_filename}")

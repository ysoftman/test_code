import os

filename = os.path.basename(__file__)
filename += ".text"


def write_file():
    myfile = open(filename, "w", encoding="utf8")
    for idx in range(1, 4):
        strMsg = str(idx) + "_test" + "\n"
        myfile.write(strMsg)
    myfile.close()
    return None


def read_chunk(chunk_size):
    with open(filename, "r") as f:
        file_size = os.fstat(f.fileno()).st_size
        read = 0
        print("--file_size:", file_size)
        while read < file_size:
            # size 디폴트 -1, 파일 전체 읽기
            r = f.read(chunk_size)
            print(r)
            read += len(r)
            print(f"---read_size:{read}")


write_file()
read_chunk(-1)
read_chunk(10)
# size 를 크게하더라고 파일 크기를 넘어서진 않는다.
read_chunk(100000)

os.remove(filename)
print(f"{filename} has been removed.")

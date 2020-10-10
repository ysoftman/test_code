# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : PIL(python Imaging Library)  test
# pip install pillow

from PIL import Image
from PIL import ImageFilter

def pil_test():
    # 이미지 열기
    img = Image.open("lena.png")
    img.show()
    
    # 이미지 복사
    img.save("lena_copy.png")

    # 필터 적용
    img2 = img.filter(ImageFilter.EMBOSS)
    img2.show()

    # 리사이즈
    img2 = img.resize((200,200), Image.ANTIALIAS)
    img2.show()

if __name__ == '__main__':
    pil_test()

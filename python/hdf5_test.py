# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x, 3.x
# desc : HDF5(Hierarchical Data Format, 대용량 데이터 저장을 위한 파일 포맷)
# pip install h5py

import h5py
import numpy as np

# hdf5 파일 쓰기
file = h5py.File("dset.h5", "w")
# 루트 그룹에 데이터 생성
dataset = file.create_dataset("dset", (4, 6), h5py.h5t.STD_I32BE)
print("Dataset dataspace is", dataset.shape)
print("Dataset Numpy datatype is", dataset.dtype)
print("Dataset name is", dataset.name)
print("Dataset is a member of the group", dataset.parent)
print("Dataset was created in the file", dataset.file)
# 데이터 쓰기
num = 0
data = np.zeros((4, 6))
for i in range(4):
    for j in range(6):
        num += 1
        data[i][j] = num

dataset[...] = data
data_read = dataset[...]
# print("data_read", data_read)
file.close()


# hdf5 파일 읽기
file = h5py.File("dset.h5", "r")
dataset = file["/dset"]
data_read = dataset[...]
print("data_read", data_read)
file.close()

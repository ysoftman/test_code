LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := JNIImpl
LOCAL_SRC_FILES := JNIImpl.cpp
include $(BUILD_SHARED_LIBRARY)

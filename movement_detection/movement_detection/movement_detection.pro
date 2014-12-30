#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T22:08:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = movement_detection
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += C:\\opencv\\build\\include

LIBS += -LC:\\opencv\\build\\x86\\mingw\\lib\
-lopencv_calib3d2410 \
-lopencv_contrib2410 \
-lopencv_core2410 \
-lopencv_features2d2410 \
-lopencv_flann2410 \
-lopencv_gpu2410 \
-lopencv_highgui2410 \
-lopencv_imgproc2410 \
-lopencv_legacy2410 \
-lopencv_ml2410 \
-lopencv_nonfree2410 \
-lopencv_objdetect2410 \
-lopencv_ocl2410 \
-lopencv_photo2410 \
-lopencv_stitching2410 \
-lopencv_superres2410 \
-lopencv_ts2410 \
-lopencv_video2410 \
-lopencv_videostab2410 \

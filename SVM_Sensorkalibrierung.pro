QT += core
QT -= gui

CONFIG += c++11

TARGET = SVM_Sensorkalibrierung
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face -lopencv_photo -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_flann -lopencv_xobjdetect -lopencv_imgcodecs -lopencv_objdetect -lopencv_xphoto -lopencv_imgproc -lopencv_core

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    labeled_data/non_wheels/IMG_20180426_101708.jpg \
    labeled_data/non_wheels/IMG_20180426_101733.jpg \
    labeled_data/non_wheels/IMG_20180426_101750.jpg \
    labeled_data/non_wheels/IMG_20180426_101802.jpg \
    labeled_data/non_wheels/IMG_20180426_101840.jpg \
    labeled_data/non_wheels/IMG_20180426_101857.jpg \
    labeled_data/wheels/wheel1.jpg \
    labeled_data/wheels/wheel2.jpg \
    labeled_data/wheels/wheel3j.jpg \
    labeled_data/wheels/wheel4.jpg \
    labeled_data/wheels/wheel5.jpg \
    labeled_data/wheels/wheel6.jpg

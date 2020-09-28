QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG -= qt

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#CONFIG += link_pkgconfig
#PKGCONFIG += --static --libs glfw3

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += \ \
SOURCES += \
#    3.Development_environment/VulkanTest/VulkanTest/main.cpp \
#    4.Drawing_a_triangle/1.Setup/01_Base_code/00_base_code.cpp \
#    4.Drawing_a_triangle/1.Setup/01_Base_code/00_base_code_me.cpp \
#    4.Drawing_a_triangle/1.Setup/01_Base_code/base_code.cpp \
#    4.Drawing_a_triangle/1.Setup/02_Instance/instance_creation.cpp \
#    4.Drawing_a_triangle/Hello_Triangle/Hello Triangle/main.cpp \
#    5.Vertex_Buffers/source/main.cpp \
#    6.Uniform_Buffers/source/main.cpp \
#    7.Texture_Mapping/source/main.cpp \
#    8.Depth_Buffing/source/main.cpp \
#    9.Loading_Models/source/main.cpp \
#    10.Generating_Mipmaps/source/main.cpp \
     11.Multisampling/source/main.cpp



#增加头文件包含路径
INCLUDEPATH += /usr/include \
#INCLUDEPATH += /usr/include/opencv \
#INCLUDEPATH += /usr/include/c++/8 \
               /usr/include/c++/9 \
#INCLUDEPATH += /usr/include/c++/7.4.0 \
               /usr/local/include \
               /media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/include \
               /media/liusheng/Programfiles/Programs/libs/glm/0.9.9.8 \
#INCLUDEPATH += $(VULKAN_SDK_PATH)/include \
               /media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/ubuntu/x86_64/include \
               /media/liusheng/Programfiles/Programs/libs/stb_image \
               3rdparty/stb_image \
               3rdparty/tinyobj


#INCLUDEPATH += /home/xxx/openpose/3rdparty/caffe/include \
#INCLUDEPATH += include \
#INCLUDEPATH += 3rdparty/caffe/include

##增加库文件包含路径

#LIBS += -L/usr/lib \
#        -L/usr/local/lib \
#        -L/usr/lib/x86_64-linux-gnu \
#        -L/usr/lib64/glibc-2.32/lib \
#        -L/media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/src \
##LIBS += -L$(VULKAN_SDK_PATH)/lib \
#        -L/media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/ubuntu/x86_64/lib


#LIBS += -lcurand -lcublas -lcublas_device -lcudnn -lcudart_static
#LIBS += -lcurand -lcublas -lcudnn -lcudart_static

LIBS+= /media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/ubuntu/x86_64/lib/libvulkan.so
LIBS+= /media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/src/libglfw.so
LIBS+= /usr/lib64/glibc-2.32/lib/libm.so.6
#LIBS+= /media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/src/libglfw.so.3
#LIBS+= /media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/src/libglfw.so.3.3

#LIBS+= libglfw.so


#LIBS += -static
#LIBS += -L/media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/src -lglfw

#LIBS += -lglfw # passed!

#LIBS += $(pkg-config /media/liusheng/Programfiles/Programs/libs/glfw/3.3.2/build/src/libglfw3.a --libs --static)
#LIBS += -ldl

#LIBS += -lvulkan -lc -lm
# LIBS += -static

#LIBS += -lrt
#LIBS += -ldl
#        /media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/ubuntu/x86_64/lib/libvulkan.so

#LIBS += -lglfw3
#LIBS += -lglslang -lHLSL -lOGLCompiler -lOSDependent - - - - - - - - - - -
#libglslang.a
#libHLSL.a                 libSPVRemapper.a
#libOGLCompiler.a
#libOSDependent.a
#libshaderc.a
#libshaderc_combined.a
#libSPIRV.a
#libspirv-cross-c.a
#libspirv-cross-core.a
#libspirv-cross-cpp.a
#libspirv-cross-glsl.a
#libspirv-cross-hlsl.a
#libspirv-cross-msl.a
#libspirv-cross-reflect.a  libVkLayer_utils.a
#libspirv-cross-util.a
#libSPIRV-Tools.a          libvulkan.so
#libSPIRV-Tools-link.a     libvulkan.so.1
#libSPIRV-Tools-opt.a      libvulkan.so.1.1.114
#libSPIRV-Tools-reduce.a

#    -lopencv_core \
#    -lopencv_imgproc \
#    -lopencv_highgui \
#    -lopencv_ml \

#LIBS += -lopenpose

#LIBS += -lGLU -lGL -lglut
#LIBS += -lcudnn -lglog -lgflags -lboost_system -lboost_filesystem -lm -lboost_thread
#LIBS += -pthread -fPIC -std=c++11 -fopenmp
#LIBS+=-L/home/neu-lu/qt_project/pose_test \
#LIBS += -lopenpose -lcaf

#QMAKE_CFLAGS = 'pkg-config --cflags --static --libs glfw3'
#QMAKE_CXXFLAGS=$$QMAKE_CFLAGS

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    TARGET = VulkanTutorialQT
    DESTDIR = QT_Creator/x64/Debug
#    DESTDIR = ../x64/Debug
}else{
    TARGET = VulkanTutorialQT
    DESTDIR = QT_Creator/x64/Release
#    DESTDIR = ../x64/Release
}




# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES += \ \
#    5.Vertex_Buffers/shaders/compile.bat \
#    5.Vertex_Buffers/shaders/frag.spv \
#    5.Vertex_Buffers/shaders/shader_base.frag \
#    5.Vertex_Buffers/shaders/shader_base.vert \
#    5.Vertex_Buffers/shaders/vert.spv \
#    5.Vertex_Buffers/source/5.Vertex_Buffers.cflags \
#    5.Vertex_Buffers/source/5.Vertex_Buffers.cxxflags \
#    6.Uniform_Buffers/shaders/compile.bat \
#    6.Uniform_Buffers/shaders/frag.spv \
#    6.Uniform_Buffers/shaders/shader_base.frag \
#    6.Uniform_Buffers/shaders/shader_base.vert \
#    6.Uniform_Buffers/shaders/vert.spv \
#    7.Texture_Mapping/Texture_Mapping \
#    7.Texture_Mapping/shaders/compile.bat \
#    7.Texture_Mapping/shaders/compile.sh \
#    7.Texture_Mapping/shaders/frag.spv \
#    7.Texture_Mapping/shaders/shader_base.frag \
#    7.Texture_Mapping/shaders/shader_base.vert \
#    7.Texture_Mapping/shaders/vert.spv
     11.Multisampling/Texture_Mapping \
     11.Multisampling/shaders/compile.bat \
     11.Multisampling/shaders/compile.sh \
     11.Multisampling/shaders/frag.spv \
     11.Multisampling/shaders/shader_base.frag \
     11.Multisampling/shaders/shader_base.vert \
     11.Multisampling/shaders/vert.spv


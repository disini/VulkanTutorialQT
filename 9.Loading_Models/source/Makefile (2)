VULKAN_SDK_PATH = /media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/ubuntu/x86_64
#VULKAN_SDK_PATH = /opt/vulkan/sdk/1.1.114.0/x86_64
CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
HelloTriangle:main.cpp
	g++ $(CFLAGS) -o ../HelloTriangle main.cpp $(LDFLAGS)

.PHONY:test clean

test:../HelloTriangle
	LDF_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_APTH)/etc/vulkan/explicit_layer.d ./HelloTriangle

clean:
	rm -f HelloTriangle









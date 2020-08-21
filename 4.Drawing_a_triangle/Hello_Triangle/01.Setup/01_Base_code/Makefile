VULKAN_SDK_PATH = /media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/x86_64
CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
HelloTriangle:base_code.cpp
	g++ $(CFLAGS) -o HelloTriangle 00_base_code_me.cpp $(LDFLAGS)

.PHONY:test clean

test:HelloTriangle
	LDF_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_APTH)/etc/vulkan/explicit_layer.d ./HelloTriangle

clean:
	rm -f HelloTriangle









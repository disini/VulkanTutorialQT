// #include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#include <glm/vec4.hpp>
//#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>
//#include <functional>

#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>

#define NDEBUG

using namespace std;

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifndef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }


    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }


    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };


class HelloTriangleApplication {
public:
  void run(){
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }



private:
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;

    uint32_t availableValidationLayerFoundCount = 0;
   
      void initWindow()
      {
          glfwInit();

          glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);      
          glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

          window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Triangle", nullptr, nullptr);
          //VkAndroidSurfaceCreateInfoKHR::window = glfwCreateWindow(800, 600, "Vulkan Triangle", nullptr, nullptr);
      }

      void initVulkan() {
          checkAvailableExtensions();
          createInstance();
          setupDebugMessenger();
          pickPhysicalDevice();
          createLogicalDevice();
      }
	  
	   void mainLoop() {
          while (!glfwWindowShouldClose(window))
          {
              glfwPollEvents();
          }

      }

    void cleanup() {
        vkDestroyDevice(device, nullptr);

		if (enableValidationLayers)
		{
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
		}
        
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
		glfwTerminate();
    }


    void checkAvailableExtensions()
    {
		uint32_t extensionCount;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::cout << extensionCount << " extensions supported.\n\n" << std::endl;       


        std::vector<VkExtensionProperties> extensions(extensionCount);
        
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions : \n";

        for (const auto& extension:extensions)
        {
            std::cout << "\t" << extension.extensionName << "\n";
        }

        /*
		13 extensions supported
        available extensions :
			VK_KHR_device_group_creation
			VK_KHR_external_fence_capabilities
			VK_KHR_external_memory_capabilities
			VK_KHR_external_semaphore_capabilities
			VK_KHR_get_physical_device_properties2
			VK_KHR_get_surface_capabilities2
			VK_KHR_surface
			VK_KHR_surface_protected_capabilities
			VK_KHR_win32_surface
			VK_EXT_debug_report
			VK_EXT_debug_utils
			VK_EXT_swapchain_colorspace
			VK_NV_external_memory_capabilities
        */
    }

    void createInstance() {
        
        if (enableValidationLayers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("\n\n validation layers requested, but not available!");
        }
        
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        /*uint32_t glfwExtensionCount = 0;
        const char** glfwExtentions;

        glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtentions;*/

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;

        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }


        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }



    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;

       

    }


    void setupDebugMessenger() {
        if (!enableValidationLayers) 
            return;
        
        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

		if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to setup debug messenger!");
		}
    }

    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            //std::cout << 
            throw std::runtime_error("failed to find GPUs with vulkan support!");
        }
		/* else
		 {

		 }*/

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }


    }

    void createLogicalDevice() {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;

        float queuePriority = 1.0f;

        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFreatures = {};
        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &deviceFreatures;
        createInfo.enabledExtensionCount = 0;

        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create logical device!");
        }
        
        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    }


    bool isDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = findQueueFamilies(device);

        return indices.isComplete();
    }


    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);


        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily:queueFamilies)
        {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
            }

            if (indices.isComplete())
            {
                break;
            }
            i++;
        }

        return indices;
    }



	std::vector<const char*> getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}


    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        size_t availableLayersListedYetCount = 0;
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        std::cout << "\n\nValidation Layers Listed Count == " << availableLayers.size() << endl;

        std::cout << "\n\nAvailable Layers : \n";

        for (const auto& layerProperties : availableLayers)
        {
            if (availableLayersListedYetCount < availableLayers.size())
            {
                std::cout << availableLayers[availableLayersListedYetCount++].layerName << endl;
                //availableLayersListedYetCount++;
            }
        }

        for (const char* layerName : validationLayers)
        {
            bool layerFound = false;

            /*
            Available Layers :
                VK_LAYER_NV_optimus
                VK_LAYER_RENDERDOC_Capture
                VK_LAYER_NV_nsight
                VK_LAYER_VALVE_steam_overlay
                VK_LAYER_VALVE_steam_fossilize
                VK_LAYER_EOS_Overlay
                VK_LAYER_EOS_Overlay
                VK_LAYER_NV_nsight-sys
                VK_LAYER_LUNARG_api_dump
                VK_LAYER_LUNARG_device_simulation
                VK_LAYER_KHRONOS_validation
                VK_LAYER_LUNARG_monitor
                VK_LAYER_LUNARG_screenshot
                VK_LAYER_LUNARG_vktrace
                VK_LAYER_LUNARG_standard_validation

            */ // 11 in total

            for (const auto& layerProperties : availableLayers)
            {

                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    std::cout << "\n\nAvailable Validation Layer Found, it's name is : " << layerName << endl;// VK_LAYER_KHRONOS_validation
                    layerFound = true;
                    availableValidationLayerFoundCount++;
                    break;
                    //continue;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        std::cout << "\n\nAvailable Validation Layers Listed Count == " << availableLayersListedYetCount << endl;// 15
        std::cout << "\n\nAvailable Validation Layers Found Count == " << availableValidationLayerFoundCount << endl;// 1
        //  VK_LAYER_KHRONOS_validation

        return true;
    }



	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageSeverityFlagsEXT mesasgeType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {

		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}


     
};



int main() {
  HelloTriangleApplication app;
  cout << "HelloTriangle Application will running!" << endl;
  try{
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  cout << "HelloTriangle Application run finished!" << endl;

  return EXIT_SUCCESS;

}

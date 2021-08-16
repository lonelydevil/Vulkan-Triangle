#include "../Headers/std_c.h"
#include "../Headers/ext.h"
#include "../Headers/vk_fun.h"
#include "../Headers/glfw_fun.h"

int main(){
	glfwInit();

	VkInstance instance = createInstance();

	uint32_t physicalDeviceNumber = getPhysicalDeviceNumber(&instance);
	VkPhysicalDevice *physicalDevices = getPhysicalDevices(&instance, physicalDeviceNumber);
	uint32_t bestPhysicalDeviceIndex = getBestPhysicalDeviceIndex(physicalDevices, physicalDeviceNumber);
	VkPhysicalDevice *pBestPhysicalDevice = &physicalDevices[bestPhysicalDeviceIndex];

	uint32_t queueFamilyNumber = getqueueFamilyNumber(pBestPhysicalDevice);
	VkQueueFamilyProperties *queueFamilyProperties = getQueueFamilyProperties(pBestPhysicalDevice, queueFamilyNumber);

	VkDevice device = createDevice(pBestPhysicalDevice, queueFamilyNumber, queueFamilyProperties);

	uint32_t bestGraphicsQueueFamilyindex = getBestGraphicsQueueFamilyindex(queueFamilyProperties, queueFamilyNumber);
	uint32_t graphicsQueueMode = getGraphicsQueueMode(queueFamilyProperties, bestGraphicsQueueFamilyindex);
	VkQueue drawingQueue = getDrawingQueue(&device, bestGraphicsQueueFamilyindex);
	VkQueue presentingQueue = getPresentingQueue(&device, bestGraphicsQueueFamilyindex, graphicsQueueMode);
	deleteQueueFamilyProperties(&queueFamilyProperties);

	char windowTitle[] = "Vulkan Triangle";
	GLFWwindow *window = createVulkanWindow(600, 600, windowTitle);
	VkSurfaceKHR surface = createSurface(window, &instance);
	VkBool32 surfaceSupported = getSurfaceSupport(&surface, pBestPhysicalDevice, bestGraphicsQueueFamilyindex);
	if( ! surfaceSupported){
		printf("vulkan surface not supported!\n");

		deleteSurface(&surface, &instance);
		deleteWindow(window);
		deleteDevice(&device);
		deletePhysicalDevices(&physicalDevices);
		deleteInstance(&instance);

		return 1;
	}

	VkSurfaceCapabilitiesKHR surfaceCapabilities = getSurfaceCapabilities(&surface, pBestPhysicalDevice);
	VkSurfaceFormatKHR bestSurfaceFormat = getBestSurfaceFormat(&surface, pBestPhysicalDevice);
	VkPresentModeKHR bestPresentMode = getBestPresentMode(&surface, pBestPhysicalDevice);
	VkExtent2D bestSwapchainExtent = getBestSwapchainExtent(&surfaceCapabilities, window);
	uint32_t imageArrayLayers = 1;
	VkSwapchainKHR swapchain = createSwapChain(&device, &surface, &surfaceCapabilities, &bestSurfaceFormat, &bestSwapchainExtent, &bestPresentMode, imageArrayLayers, graphicsQueueMode);

	uint32_t swapchainImageNumber = getSwapchainImageNumber(&device, &swapchain);
	VkImage *swapchainImages = getSwapchainImages(&device, &swapchain, swapchainImageNumber);

	VkImageView *swapchainImageViews = createImageViews(&device, &swapchainImages, &bestSurfaceFormat, swapchainImageNumber, imageArrayLayers);

	VkRenderPass renderPass = createRenderPass(&device, &bestSurfaceFormat);
	VkFramebuffer *framebuffers = createFramebuffers(&device, &renderPass, &bestSwapchainExtent, &swapchainImageViews, swapchainImageNumber);

	uint32_t vertexShaderSize = 0;
	char vertexShaderFileName[] = "Shaders/triangle_vertex.spv";
	char *vertexShaderCode = getShaderCode(vertexShaderFileName, &vertexShaderSize);
	if(vertexShaderCode == VK_NULL_HANDLE){
		printf("vertex %s shader not found!", vertexShaderFileName);

		deleteFramebuffers(&device, &framebuffers, swapchainImageNumber);
		deleteRenderPass(&device, &renderPass);
		deleteImageViews(&device, &swapchainImageViews, swapchainImageNumber);
		deleteSwapchainImages(&swapchainImages);
		deleteSwapchain(&device, &swapchain);
		deleteSurface(&surface, &instance);
		deleteWindow(window);
		deleteDevice(&device);
		deletePhysicalDevices(&physicalDevices);
		deleteInstance(&instance);

		return 1;
	}
	VkShaderModule vertexShaderModule = createShaderModule(&device, vertexShaderCode, vertexShaderSize);

	uint32_t fragmentShaderSize = 0;
	char fragmentShaderFileName[] = "Shaders/triangle_fragment.spv";
	char *fragmentShaderCode = getShaderCode(fragmentShaderFileName, &fragmentShaderSize);
	if(fragmentShaderCode == VK_NULL_HANDLE){
		printf("fragment shader %s not found", fragmentShaderFileName);

		deleteShaderModule(&device, &vertexShaderModule);
		deleteShaderCode(&vertexShaderCode);

		deleteFramebuffers(&device, &framebuffers, swapchainImageNumber);
		deleteRenderPass(&device, &renderPass);
		deleteImageViews(&device, &swapchainImageViews, swapchainImageNumber);
		deleteSwapchainImages(&swapchainImages);
		deleteSwapchain(&device, &swapchain);
		deleteSurface(&surface, &instance);
		deleteWindow(window);
		deleteDevice(&device);
		deletePhysicalDevices(&physicalDevices);
		deleteInstance(&instance);

		return 1;
	}
	VkShaderModule fragmentShaderModule = createShaderModule(&device, fragmentShaderCode, fragmentShaderSize);

	VkPipelineLayout pipelineLayout = createPipelineLayout(&device);
	VkPipeline graphicsPipeline = createGraphicsPipeline(&device, &pipelineLayout, &vertexShaderModule, &fragmentShaderModule, &renderPass, &bestSwapchainExtent);

	deleteShaderModule(&device, &fragmentShaderModule);
	deleteShaderCode(&fragmentShaderCode);
	deleteShaderModule(&device, &vertexShaderModule);
	deleteShaderCode(&vertexShaderCode);

	VkCommandPool commandPool = createCommandPool(&device, bestGraphicsQueueFamilyindex);
	VkCommandBuffer *commandBuffers = createCommandBuffers(&device, &commandPool, swapchainImageNumber);
	recordCommandBuffers(&commandBuffers, &renderPass, &framebuffers, &bestSwapchainExtent, &graphicsPipeline, swapchainImageNumber);

	uint32_t maxFrames = 2;
	VkSemaphore *waitSemaphores = createSemaphores(&device, maxFrames), *signalSemaphores = createSemaphores(&device, maxFrames);
	VkFence *frontFences = createFences(&device, maxFrames), *backFences = createEmptyFences(swapchainImageNumber);

	presentImage(&device, window, commandBuffers, frontFences, backFences, waitSemaphores, signalSemaphores, &swapchain, &drawingQueue, &presentingQueue, maxFrames);

	deleteEmptyFences(&backFences);
	deleteFences(&device, &frontFences, maxFrames);
	deleteSemaphores(&device, &signalSemaphores, maxFrames);
	deleteSemaphores(&device, &waitSemaphores, maxFrames);
	deleteCommandBuffers(&device, &commandBuffers, &commandPool, swapchainImageNumber);
	deleteCommandPool(&device, &commandPool);
	deleteGraphicsPipeline(&device, &graphicsPipeline);
	deletePipelineLayout(&device, &pipelineLayout);
	deleteFramebuffers(&device, &framebuffers, swapchainImageNumber);
	deleteRenderPass(&device, &renderPass);
	deleteImageViews(&device, &swapchainImageViews, swapchainImageNumber);
	deleteSwapchainImages(&swapchainImages);
	deleteSwapchain(&device, &swapchain);
	deleteSurface(&surface, &instance);
	deleteWindow(window);
	deleteDevice(&device);
	deletePhysicalDevices(&physicalDevices);
	deleteInstance(&instance);

	glfwTerminate();
	return 0;
}

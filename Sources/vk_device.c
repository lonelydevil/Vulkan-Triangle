#include "../Headers/vk_fun.h"

VkDevice createDevice(VkPhysicalDevice *pPhysicalDevice, uint32_t queueFamilyNumber, VkQueueFamilyProperties *pQueueFamilyProperties){
	VkDeviceQueueCreateInfo *deviceQueueCreateInfo = (VkDeviceQueueCreateInfo *)malloc(queueFamilyNumber * sizeof(VkDeviceQueueCreateInfo));
	float **queuePriorities = (float **)malloc(queueFamilyNumber * sizeof(float *));

	for(uint32_t i = 0; i < queueFamilyNumber; i++){
		queuePriorities[i] = (float *)malloc(pQueueFamilyProperties[i].queueCount * sizeof(float));
		for(uint32_t j = 0; j < pQueueFamilyProperties[i].queueCount; j++){
			queuePriorities[i][j] = 1.0f;
		}

		deviceQueueCreateInfo[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		deviceQueueCreateInfo[i].pNext = VK_NULL_HANDLE;
		deviceQueueCreateInfo[i].flags = 0;
		deviceQueueCreateInfo[i].queueFamilyIndex = i;
		deviceQueueCreateInfo[i].queueCount = pQueueFamilyProperties[i].queueCount;
		deviceQueueCreateInfo[i].pQueuePriorities = queuePriorities[i];
	}

	const char extensionList[][VK_MAX_EXTENSION_NAME_SIZE] = {
		"VK_KHR_swapchain"
	};
	const char *extensions[] = {
		extensionList[0]
	};
	VkPhysicalDeviceFeatures physicalDeviceFeatures;
	vkGetPhysicalDeviceFeatures(*pPhysicalDevice, &physicalDeviceFeatures);

	VkDeviceCreateInfo deviceCreateInfo = {
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		VK_NULL_HANDLE,
		0,
		queueFamilyNumber,
		deviceQueueCreateInfo,
		0,
		VK_NULL_HANDLE,
		1,
		extensions,
		&physicalDeviceFeatures
	};

	VkDevice device;
	vkCreateDevice(*pPhysicalDevice, &deviceCreateInfo, VK_NULL_HANDLE, &device);

	for(uint32_t i = 0; i < queueFamilyNumber; i++){
		free(queuePriorities[i]);
	}
	free(queuePriorities);
	free(deviceQueueCreateInfo);
	return device;
}

void deleteDevice(VkDevice *pDevice){
	vkDestroyDevice(*pDevice, VK_NULL_HANDLE);
}

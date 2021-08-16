#include "../Headers/vk_fun.h"

uint32_t getqueueFamilyNumber(VkPhysicalDevice *pPhysicalDevice){
	uint32_t queueFamilyNumber = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(*pPhysicalDevice, &queueFamilyNumber, VK_NULL_HANDLE);
	return queueFamilyNumber;
}

VkQueueFamilyProperties *getQueueFamilyProperties(VkPhysicalDevice *pPhysicalDevice, uint32_t queueFamilyNumber){
	VkQueueFamilyProperties *queueFamilyProperties = (VkQueueFamilyProperties *)malloc(queueFamilyNumber * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(*pPhysicalDevice, &queueFamilyNumber, queueFamilyProperties);
	return queueFamilyProperties;
}

void deleteQueueFamilyProperties(VkQueueFamilyProperties **ppQueueFamilyProperties){
	free(*ppQueueFamilyProperties);
}

uint32_t getBestGraphicsQueueFamilyindex(VkQueueFamilyProperties *pQueueFamilyProperties, uint32_t queueFamilyNumber){
	uint32_t graphicsQueueFamilyNumber = 0;
	uint32_t *graphicsQueueFamilyIndices = (uint32_t *)malloc(queueFamilyNumber * sizeof(uint32_t));

	for(uint32_t i = 0; i < queueFamilyNumber; i++){
		if((pQueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0){
			graphicsQueueFamilyIndices[graphicsQueueFamilyNumber] = i;
			graphicsQueueFamilyNumber++;
		}
	}

	uint32_t bestGraphicsQueueFamilyQueueCount = 0, bestGraphicsQueueFamilyIndex = 0;

	for(uint32_t i = 0; i < graphicsQueueFamilyNumber; i++){
		if(pQueueFamilyProperties[graphicsQueueFamilyIndices[i]].queueCount > bestGraphicsQueueFamilyQueueCount){
			bestGraphicsQueueFamilyQueueCount = pQueueFamilyProperties[graphicsQueueFamilyIndices[i]].queueCount;
			bestGraphicsQueueFamilyIndex = i;
		}
	}

	free(graphicsQueueFamilyIndices);
	return bestGraphicsQueueFamilyIndex;
}

uint32_t getGraphicsQueueMode(VkQueueFamilyProperties *pQueueFamilyProperties, uint32_t graphicsQueueFamilyindex){
	if(pQueueFamilyProperties[graphicsQueueFamilyindex].queueCount == 1){
		return 0;
	}else if(pQueueFamilyProperties[graphicsQueueFamilyindex].queueCount > 1){
		return 1;
	}else{
		return 2;
	}
}

VkQueue getDrawingQueue(VkDevice *pDevice, uint32_t graphicsQueueFamilyindex){
	VkQueue drawingQueue = VK_NULL_HANDLE;
	vkGetDeviceQueue(*pDevice, graphicsQueueFamilyindex, 0, &drawingQueue);
	return drawingQueue;
}

VkQueue getPresentingQueue(VkDevice *pDevice, uint32_t graphicsQueueFamilyindex, uint32_t graphicsQueueMode){
	VkQueue presentingQueue = VK_NULL_HANDLE;
	if(graphicsQueueMode == 0){
		vkGetDeviceQueue(*pDevice, graphicsQueueFamilyindex, 0, &presentingQueue);
	}else if(graphicsQueueMode == 1){
		vkGetDeviceQueue(*pDevice, graphicsQueueFamilyindex, 1, &presentingQueue);
	}
	return presentingQueue;
}

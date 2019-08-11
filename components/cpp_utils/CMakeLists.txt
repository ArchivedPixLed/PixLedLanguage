idf_component_register(
	SRCS FreeRTOS.cpp GeneralUtils.cpp GPIO.cpp
	INCLUDE_DIRS .
	REQUIRES nvs_flash
	)

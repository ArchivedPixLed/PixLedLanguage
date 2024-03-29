#include <driver/rmt.h>
#include <driver/gpio.h>
#include <string.h>

#include "GPIO.h"
#include "sdkconfig.h"
#include "LedStrip.h"

#if CONFIG_CXX_EXCEPTIONS != 1
#error "C++ exception handling must be enabled within make menuconfig. See Compiler Options > Enable C++ Exceptions."
#endif
/**
 * @file LedStrip.cpp
 *
 * Two functions, RGBtoRGBW1 and RGBtoRGBW2, are available to convert RGB
 * components to RGBW components.
 *
 * By default, RGBtoRGBW2 is used. You can set up the function :
 *  - at compile time, with Make Menuconfig => Component config => Led Strip Config
 *  - at runtime, see RGBW_Strip::setRgbToRgbwConverter
 *
 */



/**
* @brief rgb_pixel constructor.
* @param[in] red, between 0 and 255
* @param[in] green, between 0 and 255
* @param[in] blue, between 0 and 255
*
*/
 rgb_pixel::rgb_pixel(uint8_t red, uint8_t green, uint8_t blue){
	 this->red = red;
	 this->green = green;
	 this->blue = blue;
 }

 /**
 * @brief rgb_pixel default constructor.
 *
 */
 rgb_pixel::rgb_pixel(){
	 rgb_pixel(0, 0, 0);
 }

 /**
 * @brief rgbw_pixel constructor.
 *
 * @param[in] red, between 0 and 255
 * @param[in] green, between 0 and 255
 * @param[in] blue, between 0 and 255
 * @param[in] white, between 0 and 255
 *
 */
 rgbw_pixel::rgbw_pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t white){
	 this->red = red;
	 this->green = green;
	 this->blue = blue;
	 this->white = white;
 }

 /**
 * @brief rgbw_pixel default constructor.
 */
 rgbw_pixel::rgbw_pixel(){
	 rgbw_pixel(0, 0, 0, 0);
 }

/**
 * @brieg hsb_pixel constructor
 *
 * @param[in] hue, between 0 and 360
 * @param[in] saturation, between 0 and 1
 * @param[in] brightness, between 0 and 1
 */
hsb_pixel::hsb_pixel(float hue, float saturation, float brightness)
{
	this->hue = hue;
	this->saturation = saturation;
	this->brightness = brightness;
}

/**
 * @brief hesb_pixel default constructor.
 */
hsb_pixel::hsb_pixel()
{
	hsb_pixel(0, 0, 0);
}

/**
 * @brief Set up RMT strip value 1.
 *
 * Set two levels of RMT output to the Neopixel value for a "1".
 * This is:
 * 	- a logic 1 during t1h
 * 	- a logic 0 during t1l
 */
void Strip::setItem1(rmt_item32_t* pItem) {
	assert(pItem != nullptr);
	pItem->level0    = 1;
	pItem->duration0 = this->t1h;
	pItem->level1    = 0;
	pItem->duration1 = this->t1l;
} // setItem1



/**
 * @brief Set up RMT strip value 0.
 *
 * Set two levels of RMT output to the Neopixel value for a "0".
 * This is:
 * a logic 1 for t0h
 * a logic 0 for t0l
 */
void Strip::setItem0(rmt_item32_t* pItem) {
	assert(pItem != nullptr);
	pItem->level0    = 1;
	pItem->duration0 = this->t0h;
	pItem->level1    = 0;
	pItem->duration1 = this->t0l;
} // setItem0


/*
 * Add an RMT terminator into the RMT data.
 */
static void setTerminator(rmt_item32_t* pItem) {
	assert(pItem != nullptr);
	pItem->level0    = 0;
	pItem->duration0 = 0;
	pItem->level1    = 0;
	pItem->duration1 = 0;
} // setTerminator

/*
 * Internal function not exposed.  Get the pixel channel color from the channel
 * type which should be one of 'R', 'G' or 'B'.
 */
static uint8_t getChannelValueByType(char type, rgb_pixel pixel) {
	switch (type) {
		case 'r':
		case 'R':
			return pixel.red;
		case 'b':
		case 'B':
			return pixel.blue;
		case 'g':
		case 'G':
			return pixel.green;
		default:
			ESP_LOGW(LOG_TAG, "Unknown color channel 0x%2x", type);
			return 0;
	}
} // getChannelValueByType

/**
 * @brief RGB_Strip constructor.
 *
 * Notice that several strips can be connected, but they must be connected on different RMT channels.
 * You shouldn't need to call this class directly, but you can use it to drive
 * other led strips not currently supported, with custom duration values.
 *
 * @param[in] gpioNum, Led Strip GPIO.
 * @param[in] pixelCount, Number of leds.
 * @param[in] channel, RMT channel to use. See https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#enumerations
 * @param[in] t0h, high value duration for bit 0, expressed in RMT ticks.
 * @param[in] t0l, low value duration for bit 0, expressed in RMT ticks.
 * @param[in] t1h, high value duration for bit 1, expressed in RMT ticks.
 * @param[in] t1l, low value duration for bit 0, expressed in RMT ticks.
 */
RGB_Strip::RGB_Strip(gpio_num_t gpioNum, uint16_t pixelCount, int channel, uint8_t t0h, uint8_t t0l, uint8_t t1h, uint8_t t1l):
	Strip(gpioNum, pixelCount, channel, t0h, t0l, t1h, t1l){
		this->pixels     = new rgb_pixel[pixelCount];
		this->items      = new rmt_item32_t[pixelCount * 24 + 1];
		clear();
	};

/**
* @brief WS2812 (RGB) constructor.
*
* @param[in] gpioNum, Led Strip GPIO.
* @param[in] pixelCount, Number of leds.
* @param[in] channel, RMT channel to use. See https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#enumerations
*
*/
WS2812::WS2812(gpio_num_t gpioNum, uint16_t pixelCount, int channel):
	RGB_Strip(
		gpioNum,
		pixelCount,
		channel,
		WS2812_T0H * RMT_RATIO,
		WS2812_T0L * RMT_RATIO,
		WS2812_T1H * RMT_RATIO,
		WS2812_T1L * RMT_RATIO
	){
		this->colorOrder = (char*) "GRB";
	};

/**
* @brief WS2815 (RGB) constructor.
*
* @param[in] gpioNum, Led Strip GPIO.
* @param[in] pixelCount, Number of leds.
* @param[in] channel, RMT channel to use. See https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#enumerations
*
*/
WS2815::WS2815(gpio_num_t gpioNum, uint16_t pixelCount, int channel):
	RGB_Strip(
		gpioNum,
		pixelCount,
		channel,
		WS2815_T0H * RMT_RATIO,
		WS2815_T0L * RMT_RATIO,
		WS2815_T1H * RMT_RATIO,
		WS2815_T1L * RMT_RATIO
	){
		this->colorOrder = (char*) "GRB";
	};

/**
*	@brief SK6812 (RGB) constructor.
*
* @param[in] gpioNum, Led Strip GPIO.
* @param[in] pixelCount, Number of leds.
* @param[in] channel, RMT channel to use. See https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#enumerations
*
*/
SK6812::SK6812(gpio_num_t gpioNum, uint16_t pixelCount, int channel):
	RGB_Strip(
		gpioNum,
		pixelCount,
		channel,
		SK6812_T0H * RMT_RATIO,
		SK6812_T0L * RMT_RATIO,
		SK6812_T1H * RMT_RATIO,
		SK6812_T1L * RMT_RATIO
	){
		this->colorOrder = (char*) "GRB";
	};

/**
* @brief RGBW_Strip constructor.
*
* Notice that several strips can be connected, but they must be connected on different RMT channels.
* You shouldn't need to call this class directly, but you can use it to drive
* other led strips not currently supported, with custom duration values.
*
* @param[in] gpioNum, Led Strip GPIO.
* @param[in] pixelCount, Number of leds.
* @param[in] channel, RMT channel to use. See https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#enumerations
* @param[in] t0h, high value duration for bit 0, expressed in RMT ticks.
* @param[in] t0l, low value duration for bit 0, expressed in RMT ticks.
* @param[in] t1h, high value duration for bit 1, expressed in RMT ticks.
* @param[in] t1l, low value duration for bit 0, expressed in RMT ticks.
*/
RGBW_Strip::RGBW_Strip(gpio_num_t gpioNum, uint16_t pixelCount, int channel, uint8_t t0h, uint8_t t0l, uint8_t t1h, uint8_t t1l):
	Strip(gpioNum, pixelCount, channel, t0h, t0l, t1h, t1l){
		this->pixels     = new rgbw_pixel[pixelCount];
		this->items      = new rmt_item32_t[pixelCount * 32 + 1];
		if (RGB_TO_RGBW_1) {
			ESP_LOGI(LOG_TAG, "RGB_TO_RGBW_1 selected");
			this->rgb2rgbwConverter = RGBtoRGBW1;
		}
 	  else if (RGB_TO_RGBW_2) {
			ESP_LOGI(LOG_TAG, "RGB_TO_RGBW_2 selected");
			this->rgb2rgbwConverter = RGBtoRGBW2;
		}
		clear();
	};

/**
* @brief Sets the RGB to RGBW converter used for RGBW strips.
*
* @param[in] converter, reference to the converter function.
*/
void RGBW_Strip::setRgbToRgbwConverter(rgbw_pixel (*converter) (uint8_t, uint8_t, uint8_t)) {
	this->rgb2rgbwConverter = converter;
}

/**
* @brief SK6812W constructor.
*
* @param[in] gpioNum, Led Strip GPIO.
* @param[in] pixelCount, Number of leds.
* @param[in] channel, RMT channel to use. See https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#enumerations
*
*/
SK6812W::SK6812W(gpio_num_t gpioNum, uint16_t pixelCount, int channel):
	RGBW_Strip(
		gpioNum,
		pixelCount,
		channel,
		SK6812W_T0H * RMT_RATIO,
		SK6812W_T0L * RMT_RATIO,
		SK6812W_T1H * RMT_RATIO,
		SK6812W_T1L * RMT_RATIO
	){
		this->colorOrder = (char*) "GRB";
	};

/**
 * @brief Construct a wrapper for the pixels.
 *
 * Set up all the RMT driver and other common parameters for every strip types.

 * Because Strip is abstract, this constructor should not be used directly, but
 * will be call by implementing classes (WS2812, SK6812W...) with correct time
 * values.
 *
 * @param[in] gpioNum, Led Strip GPIO.
 * @param[in] pixelCount, Number of leds.
 * @param[in] channel, RMT channel to use. See https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#enumerations
 * @param[in] t0h, high value duration for bit 0, expressed in RMT ticks.
 * @param[in] t0l, low value duration for bit 0, expressed in RMT ticks.
 * @param[in] t1h, high value duration for bit 1, expressed in RMT ticks.
 * @param[in] t1l, low value duration for bit 0, expressed in RMT ticks.
 *
 */
Strip::Strip(gpio_num_t gpioNum, uint16_t pixelCount, int channel, uint8_t t0h, uint8_t t0l, uint8_t t1h, uint8_t t1l) {
	assert(ESP32CPP::GPIO::inRange(gpioNum));

	this->t0h = t0h;
	this->t0l = t0l;
	this->t1h = t1h;
	this->t1l = t1l;

	this->pixelCount = pixelCount;
	this->channel    = (rmt_channel_t) channel;

	rmt_config_t config;
	config.rmt_mode                  = RMT_MODE_TX;
	config.channel                   = this->channel;
	config.gpio_num                  = gpioNum;
	config.mem_block_num             = 8 - this->channel;
	config.clk_div                   = 8;
	config.tx_config.loop_en         = 0;
	config.tx_config.carrier_en      = 0;
	config.tx_config.idle_output_en  = 1;
	config.tx_config.idle_level      = (rmt_idle_level_t) 0;
	config.tx_config.carrier_freq_hz = 10000;
	config.tx_config.carrier_level   = (rmt_carrier_level_t)1;
	config.tx_config.carrier_duty_percent = 50;

	ESP_ERROR_CHECK(rmt_config(&config));
	ESP_ERROR_CHECK(rmt_driver_install(this->channel, 0, 0));
} // Strip


/**
 * @brief Show the current pixel data for RGB strips.
 *
 * Drive the LEDs with the values that were previously set.
 */
void RGB_Strip::show() {
	auto pCurrentItem = this->items;

	for (uint16_t i = 0; i < this->pixelCount; i++) {
		uint32_t currentPixel =
				(getChannelValueByType(this->colorOrder[0], this->pixels[i]) << 16) |
				(getChannelValueByType(this->colorOrder[1], this->pixels[i]) << 8)  |
				(getChannelValueByType(this->colorOrder[2], this->pixels[i]));

		ESP_LOGD(LOG_TAG, "Pixel value: %x", currentPixel);
		for (int8_t j = 23; j >= 0; j--) {
			// We have 24 bits of data representing the red, green amd blue channels. The value of the
			// 24 bits to output is in the variable current_pixel.  We now need to stream this value
			// through RMT in most significant bit first.  To do this, we iterate through each of the 24
			// bits from MSB to LSB.
			if (currentPixel & (1 << j)) {
				setItem1(pCurrentItem);
			} else {
				setItem0(pCurrentItem);
			}
			pCurrentItem++;
		}
	}
	setTerminator(pCurrentItem); // Write the RMT terminator.

	// Show the pixels.
	ESP_ERROR_CHECK(rmt_write_items(this->channel, this->items, this->pixelCount * 24, 1 /* wait till done */));
} // show

/**
 * @brief Show the current pixel data for RGBW strips.
 *
 * Drive the LEDs with the values that were previously set.
 */
void RGBW_Strip::show() {
	auto pCurrentItem = this->items;

	for (uint16_t i = 0; i < this->pixelCount; i++) {
		uint32_t currentPixel =
				(getChannelValueByType(this->colorOrder[0], this->pixels[i]) << 24) |
				(getChannelValueByType(this->colorOrder[1], this->pixels[i]) << 16) |
				(getChannelValueByType(this->colorOrder[2], this->pixels[i]) << 8) |
				this->pixels[i].white;

		ESP_LOGD(LOG_TAG, "Pixel value: %x", currentPixel);
		for (int8_t j = 31; j >= 0; j--) {
			// We have 32 bits of data representing the red, green, blue and white channels. The value of the
			// 32 bits to output is in the variable current_pixel.  We now need to stream this value
			// through RMT in most significant bit first.  To do this, we iterate through each of the 32
			// bits from MSB to LSB.
			if (currentPixel & (1 << j)) {
				setItem1(pCurrentItem);
			} else {
				setItem0(pCurrentItem);
			}
			pCurrentItem++;
		}
	}
	setTerminator(pCurrentItem); // Write the RMT terminator.

	// Show the pixels.
	ESP_ERROR_CHECK(rmt_write_items(this->channel, this->items, this->pixelCount * 32, 1 /* wait till done */));
} // show


/**
 * @brief Set the color order of data sent to the LEDs.
 *
 * Data is sent to the WS2812s in a serial fashion.  There are 8 bits of data for each of the three
 * channel colors (red, green and blue).  The WS2812 LEDs typically expect the data to arrive in the
 * order of "green" then "red" then "blue".  However, this has been found to vary between some
 * models and manufacturers.  What this means is that some want "red", "green", "blue" and still others
 * have their own orders.  This function can be called to override the default ordering of "GRB".
 * We can specify
 * an alternate order by supply an alternate three character string made up of 'R', 'G' and 'B'
 * for example "RGB".
 *
 * Can also be set for RGBW strips, but the white component is always at the end.
 *
 */
void Strip::setColorOrder(char* colorOrder) {
	if (colorOrder != nullptr && strlen(colorOrder) == 3) {
		this->colorOrder = colorOrder;
	}
} // setColorOrder


/**
 * @brief Set the given pixel to the specified color for RGB strips.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] red, The amount of red in the pixel, between 0 and 255.
 * @param [in] green, The amount of green in the pixel, between 0 and 255.
 * @param [in] blue, The amount of blue in the pixel, between 0 and 255.
 *
 */
void RGB_Strip::setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
	assert(index < pixelCount);
	this->pixels[index].red   = red;
	this->pixels[index].green = green;
	this->pixels[index].blue  = blue;
} // setPixel

/**
 * @brief Set the given pixel to the specified color for RGBW strips.
 *
 * The RGBtoRGBW converter is used to convert from RGB to RGBW.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] red, The amount of red in the pixel, between 0 and 255.
 * @param [in] green, The amount of green in the pixel, between 0 and 255.
 * @param [in] blue, The amount of blue in the pixel, between 0 and 255.
 *
 */
void RGBW_Strip::setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
	assert(index < pixelCount);
	this->pixels[index] = this->rgb2rgbwConverter(red, green, blue);
} // setPixel

/**
 * @brief Set the given pixel to the specified color for RGBW strips.
 *
 * The RGBtoRGBW converter is used to convert from RGB to RGBW.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] pixel, rgb pixel
 */
void RGBW_Strip::setPixel(uint16_t index, rgb_pixel pixel) {
	assert(index < pixelCount);
	this->pixels[index] = this->rgb2rgbwConverter(pixel.red, pixel.green, pixel.blue);
} // setPixel

/**
 * @brief Set the given pixel to the specified color for RGBW strips.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] red, The amount of red in the pixel, between 0 and 255.
 * @param [in] green, The amount of green in the pixel, between 0 and 255.
 * @param [in] blue, The amount of blue in the pixel, between 0 and 255.
 * @param [in] white, The amount of white in the pixel, between 0 and 255.
 */
void RGBW_Strip::setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
	assert(index < pixelCount);
	this->pixels[index].red   = red;
	this->pixels[index].green = green;
	this->pixels[index].blue  = blue;
	this->pixels[index].white = white;
} // setPixel



/**
 * @brief Set the given pixel to the specified color for RGB strip.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] pixel, The RGB color value of the pixel.
 */
void RGB_Strip::setPixel(uint16_t index, rgb_pixel pixel) {
	assert(index < pixelCount);
	this->pixels[index] = pixel;
} // setPixel

/**
 * @brief Set the given pixel to the specified color for RGBW strip.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index The pixel that is to have its color set.
 * @param [in] pixel The RGBW color value of the pixel.
 */
void RGBW_Strip::setPixel(uint16_t index, rgbw_pixel pixel) {
	assert(index < pixelCount);
	this->pixels[index] = pixel;
} // setPixel


/**
 * @brief Set the given pixel to the specified color for an RGB strip.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] pixel, The RGB color value of the pixel.
 */
void RGB_Strip::setPixel(uint16_t index, uint32_t pixel) {
	assert(index < pixelCount);
	this->pixels[index].red   = pixel & 0xff;
	this->pixels[index].green = (pixel & 0xff00) >> 8;
	this->pixels[index].blue  = (pixel & 0xff0000) >> 16;
} // setPixel

/**
 * @brief Set the given pixel to the specified color for an RGBW strip.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] pixel, The RGBW color value of the pixel.
 */
void RGBW_Strip::setPixel(uint16_t index, uint32_t pixel) {
	assert(index < pixelCount);
	this->setPixel(index, rgbw_pixel(
		pixel & 0xff,
		(pixel & 0xff00) >> 8,
		(pixel & 0xff0000) >> 16,
		(pixel & 0xff000000) >> 24
	));
} // setPixel

/**
 * @brief Set the given pixel to the specified HSB color for an RGB strip.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] hue, The amount of hue in the pixel (0-360).
 * @param [in] saturation, The amount of saturation in the pixel (0-1).
 * @param [in] brightness, The amount of brightness in the pixel (0-1).
 */
void RGB_Strip::setHSBPixel(uint16_t index, float hue, float saturation, float brightness) {
	assert(index < pixelCount);
	this->pixels[index] = HSBtoRGB(hue, saturation, brightness);
} // setHSBPixel

/**
 * @brief Set the given pixel to the specified HSB color for an RGB strip.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index, The pixel that is to have its color set.
 * @param [in] hsb_pixel, HSB colors.
 */
void RGB_Strip::setHSBPixel(uint16_t index, hsb_pixel hsb_pixel) {
	assert(index < pixelCount);
	this->pixels[index] = HSBtoRGB(hsb_pixel.hue, hsb_pixel.saturation, hsb_pixel.brightness);
} // setHSBPixel

/**
 * @brief Set the given pixel to the specified HSB color for an RGBW strip.
 *
 * Compute the RGB value from HSB, and then the RGBW value from RGB.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index The pixel that is to have its color set.
 * @param [in] hsb_pixel, HSB colors.
 */
void RGBW_Strip::setHSBPixel(uint16_t index, hsb_pixel hsb_pixel) {
	assert(index < pixelCount);

	rgb_pixel _rgb_pixel = HSBtoRGB(hsb_pixel.hue, hsb_pixel.saturation, hsb_pixel.brightness);
	this->pixels[index] = this->rgb2rgbwConverter(_rgb_pixel.red, _rgb_pixel.green, _rgb_pixel.blue);
} // setHSBPixel


/**
 * @brief Set the given pixel to the specified HSB color for an RGBW strip.
 *
 * Compute the RGB value from HSB, and then the RGBW value from RGB.
 *
 * The LEDs are not actually updated until a call to show().
 *
 * @param [in] index The pixel that is to have its color set.
 * @param [in] hue The amount of hue in the pixel (0-360).
 * @param [in] saturation The amount of saturation in the pixel (0-1).
 * @param [in] brightness The amount of brightness in the pixel (0-1).
 */
void RGBW_Strip::setHSBPixel(uint16_t index, float hue, float saturation, float brightness) {
	assert(index < pixelCount);

	rgb_pixel _rgb_pixel = HSBtoRGB(hue, saturation, brightness);
	this->pixels[index] = this->rgb2rgbwConverter(_rgb_pixel.red, _rgb_pixel.green, _rgb_pixel.blue);
} // setHSBPixel


/**
 * @brief Clear all the pixel colors for an RGB strip.
 *
 * This sets all the pixels to off which is no brightness for all of the color channels.
 * The LEDs are not actually updated until a call to show().
 */
void RGB_Strip::clear() {
	for (uint16_t i = 0; i < this->pixelCount; i++) {
		this->pixels[i].red   = 0;
		this->pixels[i].green = 0;
		this->pixels[i].blue  = 0;
	}
} // clear

/**
 * @brief Clear all the pixel colors for an RGBW strip.
 *
 * This sets all the pixels to off which is no brightness for all of the color channels.
 * The LEDs are not actually updated until a call to show().
 */
void RGBW_Strip::clear() {
	for (uint16_t i = 0; i < this->pixelCount; i++) {
		this->pixels[i].red   = 0;
		this->pixels[i].green = 0;
		this->pixels[i].blue  = 0;
		this->pixels[i].white = 0;
	}
} // clear


/**
 * @brief Strip instance destructor.
 */
Strip::~Strip() {
	delete this->items;
} // ~Strip()

/**
 * @brief RGB_Strip instance destructor.
 */
RGB_Strip::~RGB_Strip() {
	delete this->pixels;
}

/**
 * @brief RGBW_Strip instance destructor.
 */
RGBW_Strip::~RGBW_Strip() {
	delete this->pixels;
}

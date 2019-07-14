
#ifndef MAIN_LEDSTRIP_H_
#define MAIN_LEDSTRIP_H_
#include <stdint.h>
#include <stdlib.h>
#include <stdexcept>
#include <algorithm>

#include <driver/rmt.h>
#include <driver/gpio.h>
#include "esp_log.h"

#ifdef CONFIG_RGB_TO_RGBW_1
	#define RGB_TO_RGBW_1 CONFIG_RGB_TO_RGBW_1
#else
	#define RGB_TO_RGBW_1 false
#endif

#ifdef CONFIG_RGB_TO_RGBW_2
	#define RGB_TO_RGBW_2 CONFIG_RGB_TO_RGBW_2
#else
	#define RGB_TO_RGBW_2 true
#endif

#define RMT_DIVIDER 8
#define RMT_CLOCK 8 //8Mhz, 80000000Hz
#define RMT_RATIO (RMT_CLOCK / RMT_DIVIDER) / 100 // Deduced from nS to S convertion : (([nS]) / 1000000000) * 80000000 / 8, simplified to avoid int overflow

// Delays in nS

// RGB WS2812
#define WS2812_T0H 350
#define WS2812_T0L 800
#define WS2812_T1H 700
#define WS2812_T1L 600

// RGB WS2815
#define WS2815_T0H 300
#define WS2815_T0L 800
#define WS2815_T1H 800
#define WS2815_T1L 300

// RGB SK6812
#define SK6812_T0H 300
#define SK6812_T0L 900
#define SK6812_T1H 600
#define SK6812_T1L 600

// RGBW SK6812
#define SK6812W_T0H 300
#define SK6812W_T0L 900
#define SK6812W_T1H 600
#define SK6812W_T1L 600


static const char* LOG_TAG = "LedStrip";

/**
 * @mainpage ESP32 Led Strip Driver (RGB and RGBW)
 *
 * @author PaulBreugnot
 * @brief Driver for Strip/NeoPixel data.
 * @see GitHub : https://github.com/PixLed/ESP32_RGBW_Led_Driver/
 *
 *
 * NeoPixels or Strips are LED devices that can illuminate in arbitrary colors with
 * 8 bits of data for each of the red, green and blue channels.  These devices can be
 * daisy chained together to produce a string of LEDs.  If we call each LED instance
 * a pixel, then when we want to set the value of a string of pixels, we need to supply
 * the data for all the pixels.  This class encapsulates setting the color value for
 * an individual pixel within the string and, once you have set up all the desired colors,
 * you can then set all the pixels in a show() operation.  The class hides from you
 * the underlying details needed to drive the devices.
 *
 * Currently, RGB Strips (WS2812 or NeoPixels, SK6812) and RGBW strips are
 * supported. For RGBW strips, you can either drive manually the 4 leds (be
 * careful to energy consumption if you set the 4 to high value) or drive them
 * normally in RGB. If you do so, the color will be converted to RGBW for a
 * "smart" white composant usage (from https://stackoverflow.com/questions/40312216/converting-rgb-to-rgbw).
 * A simpler function is also available :
 * @code
 *   w = min(r, g, b)
 *   r, g, b = r - w, g - w, b - w
 * @endcode
 *
 *
 * The choice between strip models is made instanciating the corresponding class.
 * Then, functions to set pixels color and show them are equal.
 *
 * Example code to drive RGBW and RGB strips with the same commands :
 *
 * @code{.cpp}
 * #include <stdio.h>
 * #include "LedStrip.h"
 * #include "freertos/task.h"
 *
 * #define WS2812_PIN 14
 * #define SK6812_PIN 12
 * #define NUM_LED 5
 *
 * extern "C" {
 *    void app_main();
 * }
 *
 * void app_main()
 * {
 *   SK6812W sk6812 = SK6812W((gpio_num_t) SK6812_PIN, NUM_LED, RMT_CHANNEL_0);
 *   WS2812 ws2812 = WS2812((gpio_num_t) WS2812_PIN, NUM_LED, RMT_CHANNEL_1);
 *   while(1) {
 *     for (int h=0; h < 360; h++) {
 *       for (int i=0; i < NUM_LED; i++) {
 *           sk6812.setHSBPixel(i, h, 0.8, 0.7);
 *           ws2812.setHSBPixel(i, h, 0.8, 0.7);
 *       }
 *       sk6812.show();
 *       ws2812.show();
 *       vTaskDelay(50 / portTICK_PERIOD_MS);
 *     }
 * }
 * @endcode
 */

/**
 * @brief A data type representing and RGB pixel.
 */
struct rgb_pixel {
	rgb_pixel();
	rgb_pixel(uint8_t red, uint8_t green, uint8_t blue);
	/**
	 * @brief The red component of the pixel.
	 */
	uint8_t red;
	/**
	 * @brief The green component of the pixel.
	 */
	uint8_t green;
	/**
	 * @brief The blue component of the pixel.
	 */
	uint8_t blue;
};

/**
 * @brief A data type representing an RGBW pixel.
 */
struct rgbw_pixel : rgb_pixel {
	rgbw_pixel();
	rgbw_pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
	/**
	 * @brief The white component of the pixel.
	 */
	uint8_t white;
};

/**
 * @brief A data type representing an HSB pixel.
 */
struct hsb_pixel {
	hsb_pixel();
	hsb_pixel(float hue, float saturation, float brightness);
	/**
	 * @brief Color hue, in [0;360]
	 */
	float hue;

	/**
	 * @brief Color saturation, in [0;1]
	 */
	float saturation;

	/**
	 * @brief Color brightness, in [0;1]
	 */
	float brightness;
};

/**
 * @fn static rgb_pixel HSBtoRGB(float hue, float saturation, float brightness)
 *
 * @brief Converts the specified HSB color to an RGB color.
 *
 * param [in] hue, between 0 and 360
 * param [in] saturation, between 0 and 1
 * param [in] brightness, between 0 and 1
 */
static rgb_pixel HSBtoRGB(float hue, float saturation, float brightness) {

	double      hh, p, q, t, ff;
	long        i;
	double      r_out;
	double      g_out;
	double 	    b_out;

	if(saturation <= 0.0) {       // < is bogus, just shuts up warnings
			r_out = brightness;
			g_out = brightness;
			b_out = brightness;
			return rgb_pixel(r_out * 255, g_out * 255, b_out * 255);
	}
	hh = hue;
	if(hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = brightness * (1.0 - saturation);
	q = brightness * (1.0 - (saturation * ff));
	t = brightness * (1.0 - (saturation * (1.0 - ff)));

	switch(i) {
	case 0:
			r_out = brightness;
			g_out = t;
			b_out = p;
			break;
	case 1:
			r_out = q;
			g_out = brightness;
			b_out = p;
			break;
	case 2:
			r_out = p;
			g_out = brightness;
			b_out = t;
			break;

	case 3:
			r_out = p;
			g_out = q;
			b_out = brightness;
			break;
	case 4:
			r_out = t;
			g_out = p;
			b_out = brightness;
			break;
	case 5:
	default:
			r_out = brightness;
			g_out = p;
			b_out = q;
			break;
	}

	return rgb_pixel(r_out * 255, g_out * 255, b_out * 255);
}

/**
 * @fn static rgbw_pixel RGBtoRGBW1(uint8_t red, uint8_t green, uint8_t blue)
 *
 * @brief First method to convert RGB to RGBW.
 *
 * @code
 *    w = min(r, g, b)
 *    r, g, b = r - w, g - w, b - w
 * @endcode
 *
 * @param[in] red, between 0 and 255
 * @param[in] green, between 0 and 255
 * @param[in] blue, between 0 and 255
 *
 */
static rgbw_pixel RGBtoRGBW1(uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t white = std::min(red, std::min(green, blue));
	return rgbw_pixel(
		red - white,
		green - white,
		blue - white,
		white
	);
}

/**
 * @fn static rgbw_pixel RGBtoRGBW2(uint8_t red, uint8_t green, uint8_t blue)
 *
 * @brief Second method to convert RGB to RGBW.
 *
 * Based on https://stackoverflow.com/questions/40312216/converting-rgb-to-rgbw
 *
 * @param[in] red, between 0 and 255
 * @param[in] green, between 0 and 255
 * @param[in] blue, between 0 and 255
 *
 */
static rgbw_pixel RGBtoRGBW2(uint8_t red, uint8_t green, uint8_t blue) {
	//Get the maximum between R, G, and B
	float tM = std::max(red, std::max(green, blue));

	//If the maximum value is 0, immediately return pure black.
	if(tM == 0)
	   { return rgbw_pixel(0, 0, 0, 0); }

	//This section serves to figure out what the color with 100% hue is
	float multiplier = 255.0f / tM;
	float hR = red * multiplier;
	float hG = green * multiplier;
	float hB = blue * multiplier;

	//This calculates the Whiteness (not strictly speaking Luminance) of the color
	float M = std::max(hR, std::max(hG, hB));
	float m = std::min(hR, std::min(hG, hB));
	float Luminance = ((M + m) / 2.0f - 127.5f) * (255.0f/127.5f) / multiplier;

	//Calculate the output values
	uint8_t Wo = Luminance;
	uint8_t  Bo = blue - Luminance;
	uint8_t  Ro = red - Luminance;
	uint8_t  Go = green - Luminance;

	return rgbw_pixel(Ro, Go, Bo, Wo);
}

/**
 * @brief General and abstract led Strip class.
 */
class Strip {
public:
	Strip(gpio_num_t gpioNum, uint16_t pixelCount, int channel, uint8_t t0h, uint8_t t0l, uint8_t t1h, uint8_t t1l);
	virtual void show() = 0;
	void setColorOrder(char* order);
	virtual void setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) = 0;
	virtual void setPixel(uint16_t index, uint32_t pixel) = 0;
	virtual void setPixel(uint16_t index, rgb_pixel pixel) = 0;
	virtual void setHSBPixel(uint16_t index, float hue, float saturation, float brightness) = 0;
	virtual void setHSBPixel(uint16_t index, hsb_pixel pixel) = 0;
	virtual void clear() = 0;
	virtual ~Strip();
	uint16_t pixelCount;

protected:
	char*          colorOrder;

	rmt_channel_t  channel;
	rmt_item32_t*  items;

	uint8_t t0h;
	uint8_t t0l;
	uint8_t t1h;
	uint8_t t1l;

	void setItem1(rmt_item32_t* pItem);
	void setItem0(rmt_item32_t* pItem);

};

/**
 * @brief RGB strip class.
 */
class RGB_Strip: public Strip {
public:
	RGB_Strip(gpio_num_t gpioNum, uint16_t pixelCount, int channel, uint8_t t0h, uint8_t t0l, uint8_t t1h, uint8_t t1l);
	void setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
	void setPixel(uint16_t index, rgb_pixel pixel);
	void setPixel(uint16_t index, uint32_t pixel);
	void setHSBPixel(uint16_t index, float hue, float saturation, float brightness);
	void setHSBPixel(uint16_t index, hsb_pixel pixel);
	void clear();
	void show();
	virtual ~RGB_Strip();
	rgb_pixel*   pixels;
};

/**
 * RGBW strip class.
 */
class RGBW_Strip:  public Strip {
public:
	RGBW_Strip(gpio_num_t gpioNum, uint16_t pixelCount, int channel, uint8_t t0h, uint8_t t0l, uint8_t t1h, uint8_t t1l);
	void setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
	void setPixel(uint16_t index, rgb_pixel pixel);
	void setPixel(uint16_t index, rgbw_pixel pixel);
	void setPixel(uint16_t index, uint32_t pixel);
	void setHSBPixel(uint16_t index, float hue, float saturation, float brightness);
	void setHSBPixel(uint16_t index, hsb_pixel pixel);
	void setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
	void clear();
	void show();
	void setRgbToRgbwConverter(rgbw_pixel (*converter) (uint8_t, uint8_t, uint8_t));
	virtual ~RGBW_Strip();
	rgbw_pixel*   pixels;

private:
	rgbw_pixel (*rgb2rgbwConverter) (uint8_t, uint8_t, uint8_t);
};

/**
 * @brief WS2812 RGB strip implementation.
 */
class WS2812: public RGB_Strip {
public:
	WS2812(gpio_num_t gpioNum, uint16_t pixelCount, int channel);
};

/**
 * @brief WS2815 RGB strip implementation.
 */
class WS2815: public RGB_Strip {
public:
	WS2815(gpio_num_t gpioNum, uint16_t pixelCount, int channel);
};

/**
 * @brief SK6812 RGB strip implementation.
 */
class SK6812: public RGB_Strip {
public:
	SK6812(gpio_num_t gpioNum, uint16_t pixelCount, int channel);
};

/**
 * @brief SK2812 RGBW strip implementation.
 */
class SK6812W: public RGBW_Strip {
public:
	SK6812W(gpio_num_t gpioNum, uint16_t pixelCount, int channel);
};

#endif /* MAIN_LEDSTRIP_H_ */

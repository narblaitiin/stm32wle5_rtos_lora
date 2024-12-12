/*
 * Copyright (c) 2024
 * Regis Rousseau
 * Univ Lyon, INSA Lyon, Inria, CITI, EA3720
 * SPDX-License-Identifier: Apache-2.0
 */

#include "app_lora.h"

//  ======== globals ============================================
struct payload_serial {
		char *id_test;
		uint16_t rand_val;
};

static const struct gpio_dt_spec led_tx = GPIO_DT_SPEC_GET(LED_TX, gpios);	// alias ledtx on devicetree
																			// test on customed lora_e5_mini board

//  ======== main ===============================================
int8_t main(void)
{
	const struct device *lora_dev;
	int8_t ret;
	int8_t itr = 0;

	char dev_eui[] = "0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x06, 0x21, 0xA5";

	// data to be transmitted
	struct payload_serial test_tx;
	test_tx.id_test = dev_eui;
	test_tx.rand_val = sys_rand16_get();	// random value simulating ADC value in uint16 format

	printk("LoRa Transmitter Example\nBoard: %s\n", CONFIG_BOARD);
	
	// setup lora radio device
	lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));
	if (!device_is_ready(lora_dev)) {
		printk("%s: device not ready\n", lora_dev->name);
		return 0;
	}

	// setup tx led at GPIO PC0
	ret = gpio_pin_configure_dt(&led_tx, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	// configuration of lora parameters 
	if (app_lora_config(lora_dev, TRANSMIT)) {
		printk("LoRa device configured\n");
	} else {
			return 0;
		}

	// transmission of packets on lora phy layer forever
	while (1) {

		ret = lora_send(lora_dev, &test_tx, sizeof(test_tx));
		if (ret < 0) {
			printk("LoRa send failed. error%d\n", ret);
			return 0;
		} else {
			// flashing of the LED when a packet is transmitted
			ret = gpio_pin_toggle_dt(&led_tx);	 
			if (ret < 0) {
				return 0;
			}
			
			// printing of data and size of packets
			printk("XMIT %d bytes: \n", sizeof(test_tx));
			for (uint16_t i = 0; i < sizeof(test_tx); i++) {
				printk("id: %s, value: %u\n", test_tx.id_test, test_tx.rand_val);
			}
			printk("\n");
		}
		k_sleep(K_MSEC(100));	// waiting 100ms - better to see spectrum with plutoSDR/GRC
	}
	return 0;
}
/*
 * Copyright (c) 2024
 * Regis Rousseau
 * Univ Lyon, INSA Lyon, Inria, CITI, EA3720
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef APP_LORA__H
#define APP_LORA__H

//  ======== includes =============================================
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/lora.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/random/random.h>

//  ======== defines ==============================================
#define TRANSMIT    1
#define LED_TX      DT_ALIAS(ledtx)  // declared in device tree 

//  ======== prototypes ===========================================
int8_t app_lora_config(const struct device *dev, bool TxRx);

#endif /* APP_LORA__H */
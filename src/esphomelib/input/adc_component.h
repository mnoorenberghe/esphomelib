//
//  adc_component.h
//  esphomelib
//
//  Created by Otto Winter on 24.02.18.
//  Copyright © 2018 Otto Winter. All rights reserved.
//

#ifndef ESPHOMELIB_ADC_COMPONENT_H
#define ESPHOMELIB_ADC_COMPONENT_H

#include <esphomelib/component.h>
#include <esphomelib/sensor/sensor.h>
#include "Arduino.h"

namespace esphomelib {

namespace input {

class ADCSensorComponent : public Component, public sensor::Sensor {
 public:
#ifdef ARDUINO_ARCH_ESP32
  explicit ADCSensorComponent(uint8_t pin, uint32_t check_interval = 1000, uint8_t mode = ANALOG);
#else
  explicit ADCSensorComponent(uint8_t pin, uint32_t check_interval = 1000);
#endif

  uint8_t get_pin() const;
  void set_pin(uint8_t pin);

#ifdef ARDUINO_ARCH_ESP32
  uint8_t get_mode() const;
  void set_mode(uint8_t mode);
#endif

  uint32_t get_check_interval() const;
  void set_check_interval(uint32_t check_interval);
  void setup() override;
  float get_setup_priority() const override;
  std::string unit_of_measurement() override;

#ifdef ARDUINO_ARCH_ESP32
  adc_attenuation_t get_attenuation() const;
  void set_attenuation(adc_attenuation_t attenuation);
#endif

 protected:
  uint8_t pin_;
  uint32_t check_interval_;

#ifdef ARDUINO_ARCH_ESP32
  uint8_t mode_;
  adc_attenuation_t attenuation_{ADC_0db};
#endif
};

} // namespace input

} // namespace esphomelib

#endif //ESPHOMELIB_ADC_COMPONENT_H

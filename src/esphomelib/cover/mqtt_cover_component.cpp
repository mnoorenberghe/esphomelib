//
//  mqtt_cover.cpp
//  esphomelib
//
//  Created by Otto Winter on 20.05.18.
//  Copyright © 2018 Otto Winter. All rights reserved.
//

#include "esphomelib/cover/mqtt_cover_component.h"
#include "esphomelib/log.h"

#ifdef USE_COVER

ESPHOMELIB_NAMESPACE_BEGIN

namespace cover {

static const char *TAG = "cover.mqtt";

MQTTCoverComponent::MQTTCoverComponent(Cover *cover) : cover_(cover) {}
void MQTTCoverComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MQTT cover '%s'...", this->friendly_name().c_str());
  this->cover_->add_on_publish_state_callback([this](CoverState state) {
    const char *state_s;
    switch (state) {
      case COVER_OPEN: state_s = "open"; break;
      case COVER_CLOSED: state_s = "closed"; break;
      default: {
        ESP_LOGW(TAG, "Unknown cover state.");
        return;
      }
    }
    ESP_LOGD(TAG, "'%s': Sending state %s", this->friendly_name().c_str(), state_s);
    this->send_message(this->get_state_topic(), state_s);
  });
  this->subscribe(this->get_command_topic(), [&](const std::string &payload) {
    if (strcasecmp(payload.c_str(), "OPEN") == 0) {
      ESP_LOGD(TAG, "'%s': Opening cover...", this->friendly_name().c_str());
      this->cover_->open();
    } else if (strcasecmp(payload.c_str(), "CLOSE") == 0) {
      ESP_LOGD(TAG, "'%s': Closing cover...", this->friendly_name().c_str());
      this->cover_->close();
    } else if (strcasecmp(payload.c_str(), "STOP") == 0) {
      ESP_LOGD(TAG, "'%s': Stopping cover...", this->friendly_name().c_str());
      this->cover_->stop();
    } else {
      ESP_LOGW(TAG, "'%s': Received unknown payload '%'s...", this->friendly_name().c_str(), payload.c_str());
    }
  });
}

void MQTTCoverComponent::send_discovery(JsonBuffer &buffer, JsonObject &root, mqtt::SendDiscoveryConfig &config) {
  // Nothing to do here, yay!
}
std::string MQTTCoverComponent::component_type() const {
  return "cover";
}

std::string MQTTCoverComponent::friendly_name() const {
  return this->cover_->get_name();
}

} // namespace cover

ESPHOMELIB_NAMESPACE_END

#endif //USE_COVER

//
//  template_switch.h
//  esphomelib
//
//  Created by Otto Winter on 20.05.18.
//  Copyright © 2018 Otto Winter. All rights reserved.
//

#ifndef ESPHOMELIB_SWITCH_TEMPLATE_SWITCH_H
#define ESPHOMELIB_SWITCH_TEMPLATE_SWITCH_H

#include "esphomelib/switch_/switch.h"
#include "esphomelib/helpers.h"
#include "esphomelib/defines.h"

#ifdef USE_TEMPLATE_SWITCH

ESPHOMELIB_NAMESPACE_BEGIN

namespace switch_ {

class TemplateSwitch : public Switch {
 public:
  TemplateSwitch(const std::string &name, std::function<optional<bool>()> &&f);

  void add_turn_on_actions(const std::vector<Action<NoArg> *> &actions);
  void add_turn_off_actions(const std::vector<Action<NoArg> *> &actions);

  void loop() override;

 protected:
  void turn_on() override;
  void turn_off() override;

  std::function<optional<bool>()> f_;
  ActionList<NoArg> turn_on_action_;
  ActionList<NoArg> turn_off_action_;
};

} // namespace switch_

ESPHOMELIB_NAMESPACE_END

#endif //USE_TEMPLATE_SWITCH

#endif //ESPHOMELIB_SWITCH_TEMPLATE_SWITCH_H

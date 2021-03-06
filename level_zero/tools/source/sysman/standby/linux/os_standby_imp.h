/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "shared/source/helpers/non_copyable_or_moveable.h"

#include "sysman/linux/os_sysman_imp.h"
#include "sysman/standby/os_standby.h"
#include "sysman/standby/standby_imp.h"

namespace L0 {

class LinuxStandbyImp : public OsStandby, public NEO::NonCopyableClass {
  public:
    ze_result_t getMode(zet_standby_promo_mode_t &mode) override;
    ze_result_t setMode(zet_standby_promo_mode_t mode) override;
    LinuxStandbyImp() = default;
    LinuxStandbyImp(OsSysman *pOsSysman);
    ~LinuxStandbyImp() override = default;

  protected:
    SysfsAccess *pSysfsAccess = nullptr;

  private:
    static const std::string standbyModeFile;
    static const int standbyModeDefault = 1;
    static const int standbyModeNever = 0;
};

} // namespace L0

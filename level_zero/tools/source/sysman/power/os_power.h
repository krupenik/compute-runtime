/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <level_zero/zet_api.h>

namespace L0 {

struct OsSysman;
class OsPower {
  public:
    virtual ze_result_t getEnergyCounter(uint64_t &energy) = 0;
    virtual ze_result_t getEnergyThreshold(zet_energy_threshold_t *pThreshold) = 0;
    virtual ze_result_t setEnergyThreshold(double threshold) = 0;
    virtual bool isPowerModuleSupported() = 0;
    static OsPower *create(OsSysman *pOsSysman);
    virtual ~OsPower() = default;
};

} // namespace L0

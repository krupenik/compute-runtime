/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "level_zero/core/test/unit_tests/fixtures/device_fixture.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mock_sysfs_power.h"
#include "sysman/linux/os_sysman_imp.h"
#include "sysman/power/power_imp.h"

using ::testing::_;

namespace L0 {
namespace ult {

class SysmanPowerFixture : public DeviceFixture, public ::testing::Test {

  protected:
    std::unique_ptr<SysmanImp> sysmanImp;
    zet_sysman_handle_t hSysman;

    PowerImp *pPowerImp = nullptr;
    PublicLinuxPowerImp linuxPowerImp;

    void SetUp() override {

        DeviceFixture::SetUp();
        sysmanImp = std::make_unique<SysmanImp>(device->toHandle());
        OsPower *pOsPower = nullptr;

        pOsPower = static_cast<OsPower *>(&linuxPowerImp);
        pPowerImp = new PowerImp();
        pPowerImp->pOsPower = pOsPower;
        pPowerImp->init();
        hSysman = sysmanImp->toHandle();
    }
    void TearDown() override {
        //pOsPower is static_cast of LinuxPowerImp class , hence in cleanup assign to nullptr
        if (pPowerImp != nullptr) {
            pPowerImp->pOsPower = nullptr;
            delete pPowerImp;
            pPowerImp = nullptr;
        }
        DeviceFixture::TearDown();
    }
};
TEST_F(SysmanPowerFixture, GivenValidOSPowerHandleWhenCheckingForPowerSupportThenExpectFalseToBeReturned) {
    EXPECT_FALSE(pPowerImp->pOsPower->isPowerModuleSupported());
}

TEST_F(SysmanPowerFixture, GivenValidOSPowerHandleWhenCallingGetEnergyThresholdExpectUnsupportedFeatureReturned) {
    zet_energy_threshold_t threshold;
    EXPECT_EQ(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, pPowerImp->pOsPower->getEnergyThreshold(&threshold));
}

TEST_F(SysmanPowerFixture, GivenValidOSPowerHandleWhenCallingSetEnergyThresholdExpectUnsupportedFeatureReturned) {
    double threshold = 0;
    EXPECT_EQ(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, pPowerImp->pOsPower->setEnergyThreshold(threshold));
}

TEST_F(SysmanPowerFixture, GivenComponentCountZeroWhenCallingZetSysmanPowerGetThenZeroCountIsReturnedAndVerifySysmanPowerGetCallSucceeds) {
    uint32_t count = 0;
    ze_result_t result = zetSysmanPowerGet(hSysman, &count, NULL);

    EXPECT_EQ(ZE_RESULT_SUCCESS, result);
    EXPECT_EQ(count, 0u);

    uint32_t testcount = count + 1;

    result = zetSysmanPowerGet(hSysman, &testcount, NULL);

    EXPECT_EQ(ZE_RESULT_SUCCESS, result);
    EXPECT_EQ(testcount, count);
}
} // namespace ult
} // namespace L0

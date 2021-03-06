#pragma once

#include <openvr/openvr_driver.h>
#include <memory>
#include <vector>
#include "tracked_device.h"
#include <driver_base_api.h>

class ServerDriver : public vr::IServerTrackedDeviceProvider
{
public:
    virtual ~ServerDriver();

    DRIVER_BASE_API TrackedDevice* getTrackedDeviceById(uint32_t id) const;

protected:
    virtual vr::EVRInitError onInit(std::vector<std::unique_ptr<TrackedDevice>>& devices);
    virtual void onShutdown();
    virtual void onUpdate();
    virtual void onStandbyEnter();
    virtual void onStandbyLeave();

private:
    vr::EVRInitError Init(
        vr::IDriverLog* pDriverLog,
        vr::IServerDriverHost* pDriverHost,
        const char* pchUserDriverConfigDir,
        const char* pchDriverInstallDir) override;
    void Cleanup() override;
    const char* const* GetInterfaceVersions() override;
    uint32_t GetTrackedDeviceCount() override;
    vr::ITrackedDeviceServerDriver* GetTrackedDeviceDriver(uint32_t unWhich) override;
    vr::ITrackedDeviceServerDriver* FindTrackedDeviceDriver(const char* pchId) override;
    void RunFrame() override;
    bool ShouldBlockStandbyMode() override;
    void EnterStandby() override;
    void LeaveStandby() override;

    vr::IServerDriverHost* driverHost = nullptr;
    std::vector<std::unique_ptr<TrackedDevice>> trackedDevices;
};

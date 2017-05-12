#include "Offload.h"

#include <android-base/logging.h>

#include "chre_interface_factory.h"
#include "hidl_return_util.h"

namespace android {
namespace hardware {
namespace wifi {
namespace offload {
namespace V1_0 {
namespace implementation {

using hidl_return_util::validateAndCall;

Offload::Offload() : mOffloadServer(new OffloadServer(new ChreInterfaceFactory())) {
    LOG(android::base::INFO) << "Wifi Offload HAL impl";
}

// Methods from ::android::hardware::wifi::offload::V1_0::IOffload follow.
Return<void> Offload::configureScans(const ScanParam &param, const ScanFilter &filter,
                                     configureScans_cb _hidl_cb) {
    return validateAndCall(this, &Offload::configureScansInternal, _hidl_cb, param, filter);
}

Return<void> Offload::getScanStats(getScanStats_cb _hidl_cb) {
    return validateAndCall(this, &Offload::getScanStatsInternal, _hidl_cb);
}

Return<void> Offload::subscribeScanResults(uint32_t delayMs, subscribeScanResults_cb _hidl_cb) {
    return validateAndCall(this, &Offload::subscribeScanResultsInternal, _hidl_cb, delayMs);
}

Return<void> Offload::unsubscribeScanResults() {
    if (!mOffloadServer->unsubscribeScanResults()) {
        LOG(ERROR) << "Unable to unsubscribe";
    }
    return Void();
}

Return<void> Offload::setEventCallback(const sp<IOffloadCallback>& cb) {
    if (!mOffloadServer->setEventCallback(cb)) {
        LOG(ERROR) << "No callback set";
    }
    return Void();
}

OffloadStatus Offload::configureScansInternal(const ScanParam &param, const ScanFilter &filter) {
    return mOffloadServer->configureScans(param, filter);
}

std::pair<OffloadStatus, ScanStats> Offload::getScanStatsInternal() {
    return mOffloadServer->getScanStats();
}

OffloadStatus Offload::subscribeScanResultsInternal(uint32_t delayMs) {
    return mOffloadServer->subscribeScanResults(delayMs);
}

// Methods from ::android::hidl::base::V1_0::IBase follow.

}  // namespace implementation
}  // namespace V1_0
}  // namespace offload
}  // namespace wifi
}  // namespace hardware
}  // namespace android

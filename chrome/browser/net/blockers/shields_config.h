#ifndef SHIELDS_CONFIG_H_
#define SHIELDS_CONFIG_H_

#include <jni.h>
#include "../../../../base/android/jni_weak_ref.h"

namespace net {
namespace blockers {

class ShieldsConfig {
public:
    ShieldsConfig(JNIEnv* env, jobject obj);
    ~ShieldsConfig();

    std::string getHostSettings(const std::string& host);
    void setBlockedCountInfo(const std::string& url, int adsAndTrackers, int httpsUpgrades,
            int scriptsBlocked);

    static ShieldsConfig* getShieldsConfig();
    // Register the ShieldsConfig's native methods through JNI.
    static bool RegisterShieldsConfig(JNIEnv* env);

private:
    JavaObjectWeakGlobalRef weak_java_shields_config_;
};
}
}

#endif //SHIELDS_CONFIG_H_
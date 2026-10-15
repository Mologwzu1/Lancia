#include "cyber_th/theta/indicator.h"

namespace cyber_th {
namespace theta {

    void Indicator::SetJitterNS(int64_t jitterns){
        jitterns_ = jitterns;
    }
    int64_t Indicator::JitterNS() const{
        return jitterns_;
    }
    double Indicator::JitterS() const{
        return static_cast<double>(jitterns_) / 1000000000UL;
    }
    
    void Indicator::SetDelayNS(int64_t delayns){
        delayns_ = delayns;
    }
    int64_t Indicator::DelayNS() const{
        return delayns_;
    }
    double Indicator::DelayS() const{
        return static_cast<double>(delayns_) / 1000000000UL;
    }
} // namespace theta

} // namespace cyber_th

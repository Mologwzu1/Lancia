#include "cyber_b/beta/delay.h"

namespace cyber_b {
namespace beta {
    Delay::Delay(int64_t nanoseconds){delayns_ = nanoseconds;}
    Delay::Delay(int nanoseconds){
        delayns_ = static_cast<int64_t>(nanoseconds);
    }
    Delay::Delay(double seconds){
        delayns_ = static_cast<int64_t>(seconds * 1000000000UL);
    }
    Delay::Delay(const Duration& other){
        delayns_ = other.ToNanosecond();
    }
    int64_t Delay::DelayNS() const{
        return delayns_;
    }
    double Delay::DelayS() const{
        return static_cast<double>(delayns_) / 1000000000UL;
    }
} // namespace beta

} // namespace cyber_b
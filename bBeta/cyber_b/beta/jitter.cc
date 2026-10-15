#include "cyber_b/beta/jitter.h"

namespace cyber_b {
namespace beta {
    Jitter::Jitter(int64_t nanoseconds){jitterns_ = nanoseconds;}
    Jitter::Jitter(int nanoseconds){
        jitterns_ = static_cast<int64_t>(nanoseconds);
    }
    Jitter::Jitter(double seconds){
        jitterns_ = static_cast<int64_t>(seconds * 1000000000UL);
    }
    Jitter::Jitter(const Duration& other){
        jitterns_ = other.ToNanosecond();
    }
    int64_t Jitter::JitterNS() const{
        return jitterns_;
    }
    double Jitter::JitterS() const{
        return static_cast<double>(jitterns_) / 1000000000UL;
    }
} // namespace beta

} // namespace cyber_b
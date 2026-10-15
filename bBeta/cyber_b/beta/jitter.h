#ifndef JITTER_H
#define JITTER_H

#include "cyber/time/duration.h"

namespace cyber_b {
namespace beta {
    using apollo::cyber::Duration;
    class Jitter {
    public:
        Jitter()=default;
        explicit Jitter(int64_t nanoseconds);
        explicit Jitter(int nanoseconds);
        explicit Jitter(double seconds);
        Jitter(const Duration& other);
        ~Jitter()=default;

        int64_t JitterNS() const;
        double JitterS() const;

    private:
        int64_t jitterns_ = 0;
    };
} // namespace beta

} // namespace cyber_b

#endif // JITTER_H
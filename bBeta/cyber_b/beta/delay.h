#ifndef DELAY_H
#define DELAY_H

#include "cyber/time/duration.h"

namespace cyber_b {
namespace beta {
    using apollo::cyber::Duration;
    class Delay {
    public:
        Delay()=default;
        explicit Delay(int64_t nanoseconds);
        explicit Delay(int nanoseconds);
        explicit Delay(double seconds);
        Delay(const Duration& other);
        ~Delay()=default;

        int64_t DelayNS() const;
        double DelayS() const;

    private:
        int64_t delayns_ = 0;
    };
} // namespace beta

} // namespace cyber_b

#endif // DELAY_H
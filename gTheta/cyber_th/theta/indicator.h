#ifndef INDICATOR_H
#define INDICATOR_H
#include "cyber/cyber.h"
namespace cyber_th {
namespace theta {
    class Indicator {
    public:
        Indicator()=default;
        ~Indicator()=default;

        void SetJitterNS(int64_t jitterns);
        int64_t JitterNS() const;
        double JitterS() const;

        
        void SetDelayNS(int64_t delayns);
        int64_t DelayNS() const;
        double DelayS() const;

    private:
        int64_t jitterns_ = 0;
        int64_t delayns_ = 0;
    };
} // namespace theta

} // namespace cyber_th

#endif // INDICATOR_H
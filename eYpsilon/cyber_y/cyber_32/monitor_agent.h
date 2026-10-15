#ifndef MONITOR_AGENT_H
#define MONITOR_AGENT_H

#include <map>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "indicator_monitor.h"
#include "cyber/common/macros.h"
#include "cyber_y/ypsilon/junior_log.pb.h"

namespace cyber_y {
namespace ypsilon {
using cyber_y::ypsilon::IndicatorMonitor;
using cyber_y::proto::JuniorLog;
    class MonitorAgent
    {
    public:
        ~MonitorAgent();

        void Init();
        bool ServiceFind(const uint64_t channel_id);
        void WriteRqst(const JuniorLog& log);
        void ReadRqst(const JuniorLog& log);
        void SaveLogs();

    private:
        // 共享内存相关
        static const char* SHM_NAME;
        static const size_t SHM_SIZE;
        
        void* shm_addr_;
        size_t shm_size_;
        key_t shm_key_;
        int shm_id_;
        bool is_creator_;
        
        // 共享内存数据结构
        struct SharedData {
            int monitor_count;
            int data_size; // 序列化后的数据大小
            char data[0];  // 序列化后的数据
        } *shared_data_;
        
        // 本地映射，用于快速访问
        std::map<uint64_t, IndicatorMonitor> monitor_map_;
        std::ofstream of_;
        std::string file_root_;
        std::string log_file_;
        
        // 共享内存操作方法
        void InitSharedMemory();
        bool CreateSharedMemory();
        bool AttachSharedMemory();
        void DetachSharedMemory();
        
        // 序列化和反序列化方法
        void SerializeMonitorMap();
        void DeserializeMonitorMap();
        
        DECLARE_SINGLETON(MonitorAgent)

    };
} // namespace ypsilon

} // namespace cyber_y

#endif // MONITOR_AGENT_H
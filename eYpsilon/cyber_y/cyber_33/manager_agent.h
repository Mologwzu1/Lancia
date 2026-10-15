#ifndef MANAGER_AGENT_H
#define MANAGER_AGENT_H

#include <map>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "monitor_manager.h"
#include "cyber/common/macros.h"
#include "cyber/proto/role_attributes.pb.h"
#include "cyber_y/ypsilon/indicator_log.pb.h"

namespace cyber_y {
namespace ypsilon {
using cyber_y::ypsilon::MonitorManager;
using cyber_y::proto::IndicatorLog;
using apollo::cyber::proto::RoleAttributes;
    class ManagerAgent
    {
    public:
        ~ManagerAgent();

        void Init();
        void WriterRegist(const uint64_t channel_id, const uint64_t writer_id);
        void ReaderRegist(const uint64_t channel_id, const uint64_t reader_id);
        void WriterCancel(const uint64_t channel_id, const uint64_t writer_id);
        void ReaderCancel(const uint64_t channel_id, const uint64_t reader_id);

        bool ServiceFind(const uint64_t channel_id);
        void WriteArrange(IndicatorLog& log, const uint64_t interval);
        void ReadArrange(const uint64_t channel_id);

        void SaveLogs();
        void SaveIndicatorLogs();

        void WriteArrange(const RoleAttributes node_attr_, const uint64_t interval);
        void ReadArrange(const RoleAttributes node_attr_);

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
            int manager_count;
            int data_size; // 序列化后的数据大小
            char data[0];  // 序列化后的数据
        } *shared_data_;
        
        // 本地映射，用于快速访问
        std::map<uint64_t, MonitorManager> manager_map_;
        std::ofstream of_;
        std::string file_root_;
        std::string log_file_;
        std::string indicator_log_file_;
        
        // 共享内存操作方法
        void InitSharedMemory();
        bool CreateSharedMemory();
        bool AttachSharedMemory();
        void DetachSharedMemory();
        
        // 序列化和反序列化方法
        void SerializeManagerMap();
        void DeserializeManagerMap();
        
        // 获取CPU使用率
        double GetCpuUsage();
        
        DECLARE_SINGLETON(ManagerAgent)

    };
} // namespace ypsilon

} // namespace cyber_y

#endif // MANAGER_AGENT_H

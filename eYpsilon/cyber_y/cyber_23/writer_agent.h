#ifndef WRITER_AGENT_H
#define WRITER_AGENT_H

#include <map>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "cyber_y/cyber_21/log_writer.h"
#include "cyber_y/ypsilon/log.pb.h"

namespace cyber_y {
namespace ypsilon {

using cyber_y::ypsilon::LogWriter;

class WriterAgent {
public:
    WriterAgent();
    ~WriterAgent();
    WriterAgent(const WriterAgent&) = delete;
    WriterAgent& operator=(const WriterAgent&) = delete;
    
    static WriterAgent& Instance();
    
    LogWriter& GetLogWriter(const uint64_t node_id);
    void SaveLogs();
    
private:
    void AssignCapsuleId();
    std::map<uint64_t, LogWriter> writer_map_;
    int capsule_id_;
    static const char* ROOT_DIR;
    // 共享内存相关
    static const char* SHM_NAME;
    static const size_t SHM_SIZE;
    static const int MAX_PROCESSES = 16;
    
    struct ProcessSharedMemory {
        void* shm_addr_;
        size_t shm_size_;
        key_t shm_key_;
        int shm_id_;
        bool is_creator_;
        struct SharedData {
            int writer_count;
            char data[0];
        } *shared_data_;
    };
    
    ProcessSharedMemory process_shm_[MAX_PROCESSES];
    
    void Init();
    bool CreateSharedMemory(int capsule_id);
    bool AttachSharedMemory(int capsule_id);
    void DetachSharedMemory(int capsule_id);
};

} // namespace ypsilon
} // namespace cyber_y

#endif // WRITER_AGENT_H

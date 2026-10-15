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
    std::map<uint64_t, LogWriter> writer_map_;
    std::string log_file_;
    
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
        int writer_count;
        char data[0];
    } *shared_data_;
    
    void Init();
    bool CreateSharedMemory();
    bool AttachSharedMemory();
    void DetachSharedMemory();
};

} // namespace ypsilon
} // namespace cyber_y

#endif // WRITER_AGENT_H

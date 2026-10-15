#include "monitor_manager.h"
#include <unistd.h>
#include "cyber/time/time.h"

namespace cyber_y {
namespace ypsilon {
using apollo::cyber::Time;

    void MonitorManager::WriterRegist(const uint64_t writer_id){
        writer_queue_.push(writer_id);
    }
    void MonitorManager::ReaderRegist(const uint64_t reader_id){
        reader_queue_.push(reader_id);
    }
    void MonitorManager::WriterCancel(const uint64_t writer_id){
        if(writer_queue_.empty()){
            return;
        }
        for (uint64_t i=0;writer_queue_.front() != writer_id&&i<writer_queue_.size();i++) {
            writer_queue_.push(writer_queue_.front()); 
            writer_queue_.pop();
        }
        if(writer_queue_.front() == writer_id){
            writer_queue_.pop();
        }
    }
    void MonitorManager::ReaderCancel(const uint64_t reader_id){
        if(reader_queue_.empty()){
            return;
        }
        for (uint64_t i=0;reader_queue_.front() != reader_id&&i<reader_queue_.size();i++) {
            reader_queue_.push(reader_queue_.front()); 
            reader_queue_.pop();
        }
        if(reader_queue_.front() == reader_id){
            reader_queue_.pop();
        }
    }

    void MonitorManager::WriteRqst(IndicatorLog log){
        log.set_write_time(Time::Now().ToNanosecond());
        if(reader_queue_.empty()){
            monitor_.WriteLostLog(log);
        }
        else{
            monitor_.WriteLog(log);
        }
    }
    void MonitorManager::ReadRqst(){
        while (writer_queue_.empty()) {sleep(1);}
        monitor_.ReadLog();
    }

    std::queue<IndicatorLog> MonitorManager::ReturnLogs(){
        return monitor_.ReturnLogs();
    }
    std::string MonitorManager::Serialize() const{//return monitor_.Serialize();
        std::string result;
        // 序列化writer_queue_
        int writer_size = writer_queue_.size();
        result.append(reinterpret_cast<const char*>(&writer_size), sizeof(writer_size));
        std::queue<uint64_t> temp_writer = writer_queue_;
        while (!temp_writer.empty()) {
            uint64_t writer_id = temp_writer.front();
            result.append(reinterpret_cast<const char*>(&writer_id), sizeof(writer_id));
            temp_writer.pop();
        }
        
        // 序列化reader_queue_
        int reader_size = reader_queue_.size();
        result.append(reinterpret_cast<const char*>(&reader_size), sizeof(reader_size));
        std::queue<uint64_t> temp_reader = reader_queue_;
        while (!temp_reader.empty()) {
            uint64_t reader_id = temp_reader.front();
            result.append(reinterpret_cast<const char*>(&reader_id), sizeof(reader_id));
            temp_reader.pop();
        }
        // 序列化monitor_
        std::string monitor_data = monitor_.Serialize();
        int monitor_size = monitor_data.size();
        result.append(reinterpret_cast<const char*>(&monitor_size), sizeof(monitor_size));
        result.append(monitor_data);
        
        return result;
    }
    void MonitorManager::Deserialize(const std::string& data){//monitor_.Deserialize(data);
        size_t offset = 0;
        // 反序列化writer_queue_
        int writer_size;
        memcpy(&writer_size, data.data() + offset, sizeof(writer_size));
        offset += sizeof(writer_size);
        writer_queue_ = std::queue<uint64_t>();
        for (int i = 0; i < writer_size; i++) {
            uint64_t writer_id;
            memcpy(&writer_id, data.data() + offset, sizeof(writer_id));
            offset += sizeof(writer_id);
            writer_queue_.push(writer_id);
        }
        
        // 反序列化reader_queue_
        int reader_size;
        memcpy(&reader_size, data.data() + offset, sizeof(reader_size));
        offset += sizeof(reader_size);
        reader_queue_ = std::queue<uint64_t>();
        for (int i = 0; i < reader_size; i++) {
            uint64_t reader_id;
            memcpy(&reader_id, data.data() + offset, sizeof(reader_id));
            offset += sizeof(reader_id);
            reader_queue_.push(reader_id);
        }
        
        // 反序列化monitor_
        int monitor_size;
        memcpy(&monitor_size, data.data() + offset, sizeof(monitor_size));
        offset += sizeof(monitor_size);
        std::string monitor_data = data.substr(offset, monitor_size);
        monitor_.Deserialize(monitor_data);
    }

} // namespace ypsilon

} // namespace cyber_y

#include "monitor_agent.h"
#include "cyber/time/time.h"
#include <queue>
#include <sstream>
#include <string>

namespace cyber_y {
namespace ypsilon {
using apollo::cyber::Time;

    //MonitorAgent::MonitorAgent() = default;
    
    MonitorAgent::MonitorAgent(){
        file_root_ = "output/logs/";
        log_file_ = "cybery_indic_" + Time::Now().ToString() + ".log";
    }
    MonitorAgent::~MonitorAgent(){
        SaveLogs();
    }
    
    bool MonitorAgent::ServiceFind(const uint64_t channel_id){
        if(monitor_map_.find(channel_id) == monitor_map_.end()){
            IndicatorMonitor monitor;
            monitor_map_[channel_id] = monitor;
        }
        return monitor_map_.find(channel_id) != monitor_map_.end();
    }
    void MonitorAgent::WriteRqst(const JuniorLog& log){
        if(!ServiceFind(log.channel_id())){
            return;
        }
        monitor_map_[log.channel_id()].WriteLog(log);
    }
    void MonitorAgent::ReadRqst(const JuniorLog& log){
        if(!ServiceFind(log.channel_id())){
            return;
        }
        monitor_map_[log.channel_id()].ReadLog(log);
    }
    void MonitorAgent::SaveLogs(){
        of_.open(file_root_ + log_file_, std::ios::trunc);
        for(auto& monitor_pair : monitor_map_){
            std::queue<JuniorLog> log_queue = monitor_pair.second.ReturnLogs();
            for(; !log_queue.empty(); log_queue.pop()){
                const JuniorLog log = log_queue.front();
                of_ << log.node_name() << "\t";
                of_ << log.node_id() << "\t";
                of_ << log.channel_name() << "\t";
                of_ << log.channel_id() << "\t";
                of_ << log.write_time() << "\t";
                of_ << log.read_time() << "\n";
            }
        }
        of_.close();
    }
/*
    MonitorAgent& MonitorAgent::Instance() {
        static MonitorAgent instance;
        return instance;
    }*/
} // namespace ypsilon

} // namespace cyber_y
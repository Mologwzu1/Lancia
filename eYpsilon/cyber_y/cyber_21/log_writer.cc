#include "log_writer.h"

namespace cyber_y {
namespace ypsilon {
    
    void LogWriter::WriteLog(const IndicatorLog& log){
        log_stack_.push(log);
    }
    
    const std::stack<IndicatorLog> LogWriter::Logs(){
        return log_stack_;  
    }  
    

} // namespace ypsilon

} // namespace cyber_y
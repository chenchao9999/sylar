#ifndef __SYLAR__LOG_H__
#define __SYLAR__LOG_H__

#include<string>
#include<stdint.h>
#include<memory>

namespace sylar{
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr ;
    LogEvent();
private:
    const char* m_file=nullptr;     //文件名
    int32_t m_line=0;               //行号
    uint32_t m_elapse=0;            //程序启动到现在的时间（已运行时间）毫秒数
    uint32_t m_threadid=0;          //线程id
    uint32_t m_fiberid=0;           //协程id
    uint64_t m_time=0;              //时间戳
    std::string m_content;
};


// 日志级别
class  LogLevel
{
public:
    enum level{
        DEBUG=1,
        INFO=2,
        WARNING=3,
        ERROR=4,
        FATAL=5
    };
};

// 日志格式
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(LogEvent::ptr event);
private:
};


//日志器
class Logger{
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name="root");
    void log(LogLevel::level level,LogEvent::ptr event);
private:
    LogAppender::ptr;
    std::string m_name;
    LogLevel::level m_level;
};


// 日志输出地
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){};
    void log(LogLevel::level level,LogEvent::ptr event);
private:
};

// 标准输出appender
class StdoutLogAppender:public LogAppender{};

// 文件appender
class FileLogAppender:public:LogAppender{};

}

#endif

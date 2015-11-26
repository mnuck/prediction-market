#include "Logger.h"

#include <boost/log/core/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

using namespace boost::log;
typedef sources::severity_logger_mt<trivial::severity_level> logger_t;

BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(p_id, "ProcessID", attributes::current_process_id::value_type);
BOOST_LOG_ATTRIBUTE_KEYWORD(t_id, "ThreadID", attributes::current_thread_id::value_type);
BOOST_LOG_ATTRIBUTE_KEYWORD(severity,  "Severity", trivial::severity_level)
 
BOOST_LOG_GLOBAL_LOGGER_INIT(logger, logger_t)
{
    logger_t logger;
 
    logger.add_attribute("TimeStamp", attributes::utc_clock());
    logger.add_attribute("ProcessID", attributes::current_process_id());
    logger.add_attribute("ThreadID", attributes::current_thread_id());

    core::get()->add_sink
    (
        add_file_log
        (
            keywords::file_name = "book_%5N.log",
            keywords::target = "Logs",
            keywords::rotation_size = 10 * 1024 * 1024, // 10 meg
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), // midnight
            keywords::filter = severity >= trivial::trace,
            keywords::format =
            (
                expressions::stream
                    << "[" << expressions::format_date_time<boost::posix_time::ptime>
                              ("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << "] "
                    << "(" << p_id << ":" << t_id << ") "
                    << "(" << trivial::severity << ") "
                    << expressions::smessage
            )
        )
    );

    return logger;
}


ScopeLog::ScopeLog(std::string message):
    _message(message)
{
    LOG(trace) << "ScopeLog Entering " << _message;
}

ScopeLog::~ScopeLog()
{
    LOG(trace) << "ScopeLog Exiting " << _message;    
}

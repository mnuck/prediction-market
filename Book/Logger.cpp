#include "Logger.h"

#include <boost/log/core/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

using namespace boost::log;
typedef sources::severity_logger_mt<boost::log::trivial::severity_level> logger_t;

BOOST_LOG_ATTRIBUTE_KEYWORD(line_id,   "LineID", long)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity,  "Severity", trivial::severity_level)
 
BOOST_LOG_GLOBAL_LOGGER_INIT(logger, logger_t)
{
    logger_t logger;
 
    logger.add_attribute("LineID", attributes::counter<long>(1));
    logger.add_attribute("TimeStamp", attributes::local_clock());

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
                    << expressions::attr<long>("LineID") << ": "
                    << "[" << expressions::format_date_time<boost::posix_time::ptime>
                              ("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << "] "
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

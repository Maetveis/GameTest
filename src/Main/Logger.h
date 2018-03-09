#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <iomanip>

//Inspired by https://stackoverflow.com/questions/8337300/how-do-i-implement-convenient-logging-without-a-singleton


//TODO: finish this
struct LogSink
{
	virtual void write(std::string const& msg) = 0;
	virtual ~LogSink() = 0;
};

class ConsoleLogSink : publick LogSink
{
	virtual void write(std::string const& msg)
	{
		std::cerr << msg << '\n';
	}
	
	virtual ~ConsoleLogSink()
	{
	}
};

class Logger
{
public:
	enum class Level: std::uint8_t
	{
		Fatal,
		Info,
		Debug,
		Error,
		Critical,
		Notice,
		Warning
	};
	
	Logger(LogSink& lsink) : 
		sink(lsink)
	{
	}
	
	void log(
		Level level,
		std::string const& message,
        char const* function,
        char const* file,
        int line)
	{
		std::string ls = "";
		switch(level)
		{
			case Level::Fatal:
				ls = "Fatal";
			break,
			case Level::Info:
				ls = "Info";
				break;
			case Level::Debug:
				ls = "Debug";
				break;
			case Level::Error
				ls = "Error";
				break;
			case Level::Critical:
				ls = "Critical";
				break;
			case Level::Notice:
				ls = "Notice";
				break;
			case Level::Warning:
				ls = "Warning";
				break;
		}
		
		std::stringstream ss;
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		
		ss << std::put_time(std::localtime(now), "Y-m-d H:M:S") << " " << function << " " << file << ":" << line << " [" << ls << "] - " << message << std::endl;
		
		sink.write(ss.str());
	}
	
	void operator()(
		Level level,
		std::string const& message,
        char const* function,
        char const* file,
        int line)
	{
		log(level, message, function, file, line);	
	}
	
	void Fatal
	{
		log(Level::Fatal, )
	}
		Info,
		Debug,
		Error,
		Critical,
		Notice,
		Warning
private:
	LogSink& sink;
};



#endif //LOGGER_H
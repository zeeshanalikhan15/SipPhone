#include <pjsua2.hpp>

using namespace pj;


class CustomLogger: public LogWriter
{
public:
	CustomLogger();
	~CustomLogger();

	virtual void write(const LogEntry &entry);
};


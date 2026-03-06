// ZmqEventSource.h
#include <JANA/JEventSource.h>
#include <JANA/JApplication.h>
#include <zmq.hpp>

class ZmqEventSource : public JEventSource {
public:
    ZmqEventSource(std::string resource_name, JApplication* app);
    virtual ~ZmqEventSource() = default;

    void Open() override;
    void Close() override;
    Result Emit(JEvent& event) override;

    static std::string GetDescription();

private:
    zmq::context_t m_ctx;
    zmq::socket_t m_sub;
    std::string m_endpoint;
};
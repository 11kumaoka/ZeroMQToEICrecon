#include <zmq.hpp>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t ctx(1);
    zmq::socket_t pub(ctx, ZMQ_PUB);
    pub.bind("tcp://*:5555");

    int evnum = 0;
    while (evnum < 100) {  // 100 events to send
        zmq::message_t msg(1024);  // dummy data
        memset(msg.data(), evnum, msg.size());
        pub.send(msg, zmq::send_flags::none);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        evnum++;
    }
    return 0;
}
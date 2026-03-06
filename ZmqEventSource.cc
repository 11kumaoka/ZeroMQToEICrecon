// ZmqEventSource.cc
#include "ZmqEventSource.h"
#include <JANA/JEvent.h>

#include <edm4eic/RawTrackerHitCollection.h>

ZmqEventSource::ZmqEventSource(std::string resource_name, JApplication* app)
: JEventSource(std::move(resource_name), app),
  m_ctx(1),
  m_sub(m_ctx, ZMQ_SUB)
{
    m_endpoint = GetResourceName();
}

std::string ZmqEventSource::GetDescription() {
    return "ZmqEventSource";
}

void ZmqEventSource::Open() {
    m_sub.connect(m_endpoint);
    m_sub.set(zmq::sockopt::subscribe, "");
}

void ZmqEventSource::Close() {
    m_sub.close();
    m_ctx.close();
}

JEventSource::Result ZmqEventSource::Emit(JEvent& event) {
    zmq::message_t msg;

    
    // Recieve data
    auto res = m_sub.recv(msg, zmq::recv_flags::none);

    // To avoid return value errors, treat all as "Success",
    // and if there is no data, do nothing (make it an empty event).
    if (!res) {
        return JEventSource::Result::Success;
    }

    struct MyHardwareData { uint64_t id; float q; float t; };
    auto* raw_data = static_cast<MyHardwareData*>(msg.data());


    // Create PODIO collection
    // To match JANA's Insert(T* item), we create it with a raw pointer
    auto hits = new edm4eic::RawTrackerHitCollection();

    // Use create with arguments to avoid name mismatches in setters
    // The order is generally RawTrackerHit(cellID, charge, time)
    // hits->create(12345, 100, 10.0f);

    auto hit = hits->create();
    hit.setCellID(raw_data->id);
    hit.setCharge(static_cast<int32_t>(raw_data->q));
    hit.setTimeStamp(static_cast<int32_t>(raw_data->t));

    // Insert into the event (collection name should match what EICrecon plugin expects)
    event.Insert(std::move(hits), "TOFBarrelADCTDC");

    static uint64_t evnum = 1;
    event.SetEventNumber(evnum++);
    return Result::Success;
}
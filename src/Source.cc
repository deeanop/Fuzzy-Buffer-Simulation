# include "Source.h"
# include "IPPacket_m.h"
Define_Module(Source);
Source::~Source(){
    cancelAndDelete(sendMessageEvent);
}
void Source::initialize(){
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime() + par("interArrivalTime").doubleValue(), sendMessageEvent);
}
void Source::handleMessage(cMessage *msg){
    if(msg == sendMessageEvent){
        IPPacket *packet = new IPPacket("Packet");
        int p = (dblrand() < 0.5)? 1: 0;
        packet -> setPriority(p);
        send(packet, "out");
        scheduleAt(simTime() + par("interArrivalTime").doubleValue(), sendMessageEvent);
    }
}

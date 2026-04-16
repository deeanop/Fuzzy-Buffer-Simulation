# include "FuzzyQueue.h"
Define_Module(FuzzyQueue);
FuzzyQueue::~FuzzyQueue() {
    cancelAndDelete(endServiceMsg);
}
void FuzzyQueue::initialize(){
    LMAX = par("LMAX");
    L_LP = par("L_LP");
    endServiceMsg = new cMessage("endService");
}
double FuzzyQueue::calculateFuzzy(int currentSize, int priority){
    double ratio = (double)currentSize / LMAX;
    if(priority == 1){
        if(ratio < 0.8) return 0.0;
        return (ratio - 0.8) / 0.2;
    }
    else{
        double lp_threshold = (double)L_LP/LMAX;
        if(ratio < lp_threshold) return 0.0;
        return (ratio - lp_threshold) / (1.0 - lp_threshold);
    }
}
void FuzzyQueue::handleMessage(cMessage *msg) {
    if(msg == endServiceMsg){
        if(!queue.isEmpty()){
            IPPacket *pktFromQueue = check_and_cast<IPPacket*>(queue.pop());
            send(pktFromQueue, "out");
            scheduleAt(simTime() + 0.1, endServiceMsg);
        }
        return;
    }
    IPPacket *pkt = dynamic_cast<IPPacket*>(msg);
    if(pkt){
        int p = pkt -> getPriority();
        int currentSize = queue.getLength();
        if(currentSize >= LMAX){
            EV << "Full buffer! Packet Dropped." << endl;
            delete pkt;
            return;
        }
        double drop = calculateFuzzy(currentSize, p);
        if(dblrand() < drop){
            EV << "Fuzzy drop: Packet with priority " << p << " dropped with occupation degree " << currentSize << endl;
            delete pkt;
        }
        else{
            queue.insert(pkt);
            EV << "Packet accepted. Size: " << queue.getLength() << endl;
            if(!endServiceMsg->isScheduled()){
                scheduleAt(simTime() + 0.1, endServiceMsg);
            }
        }
    }
}

# include "FuzzyQueue.h"
Define_Module(FuzzyQueue);
void FuzzyQueue::initialize(){
    LMAX = par("LMAX");
    L_LP = par("L_LP");
    endServiceMsg = new cMessage("endService");
}
void FuzzyQueue::handleMessage(cMessage *msg){
    IPPacket *pkt = dynamic_cast<IPPacket *>(msg);
    if(pkt != nullptr){
        int p = pkt -> getPriority();
        int currentSize = queue.getLength();
        bool accept = false;
        if(p == 1){
            if(currentSize < LMAX)
                accept = true;
            else if(p == 0){
                if(currentSize < L_LP)
                    accept = true;
            }
            if(accept){
                queue.insert(pkt);
                EV << "Packet accepted. Queue size: " << queue.getLength() << endl;
                if(!endServiceMsg -> isScheduled()){
                    scheduleAt(simTime() + 0.1, endServiceMsg);
                }
            }
            else{
                delete pkt;
                EV << "Packet dropped." << endl;
            }
        }
    }
    else if(msg == endServiceMsg){
        if(!queue.isEmpty()){
            IPPacket *pktFromQueue = check_and_cast<IPPacket *>(queue.pop());
            send(pktFromQueue, "out");
            if(!queue.isEmpty()){
                scheduleAt(simTime() + 0.1, endServiceMsg);
            }
        }
        EV << "Service finished for a packet." << endl;
    }
}

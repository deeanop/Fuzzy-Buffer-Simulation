# include "Sink.h"
Define_Module(Sink);
void Sink::handleMessage(cMessage *msg){
    EV << "Sink required the package " << msg -> getName() << endl;
    delete msg;
}

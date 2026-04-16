# ifndef __SINK_H_
# define __SINK_H_
# include <omnetpp.h>
using namespace omnetpp;
    class Sink : public cSimpleModule{
    protected:
        virtual void handleMessage(cMessage *msg) override;
    };
# endif

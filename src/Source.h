# ifndef __SOURCE_H_
# define __SOURCE_H_
# include <omnetpp.h>
using namespace omnetpp;
    class Source: public cSimpleModule{
        private:
            cMessage *sendMessageEvent = nullptr;
        protected:
            virtual void initialize() override;
            virtual void handleMessage(cMessage *msg) override;
            virtual ~Source();
    };
# endif

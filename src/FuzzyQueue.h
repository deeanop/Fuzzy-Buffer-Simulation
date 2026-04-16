# ifndef FUZZYQUEUE_H_
# define FUZZYQUEUE_H_
# include <omnetpp.h>
# include "IPPacket_m.h"
using namespace omnetpp;
    class FuzzyQueue : public cSimpleModule{
        private:
            int LMAX;
            double L_LP;
            cQueue queue;
            cMessage *endServiceMsg;
            double calculateFuzzy(int currentSize, int priority);
        protected:
            virtual void initialize() override;
            virtual void handleMessage(cMessage *msg) override;
            virtual ~FuzzyQueue();
    };
# endif

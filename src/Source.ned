package fuzzybuffersim;
simple Source{
    parameters:
        int priority = default(0);
        volatile double interArrivalTime @unit(s) = default(0.1s);
    @class(Source);
    gates:
        output out;
}
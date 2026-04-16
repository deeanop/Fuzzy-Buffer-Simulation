package fuzzybuffersim;

simple FuzzyQueue
{
    parameters:
        int LMAX = default(100);
        int L_LP = default(80);
    @class(FuzzyQueue);
    gates:
        input in[];
        output out;
}
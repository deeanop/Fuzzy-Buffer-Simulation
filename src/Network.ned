package fuzzybuffersim;
import fuzzybuffersim.Source;
import fuzzybuffersim.FuzzyQueue;
import fuzzybuffersim.Sink;
network FuzzyNetwork
{
    @display("bgb=472,321");
    submodules:
        srcHP: fuzzybuffersim.Source {
            priority = 1;
            interArrivalTime = exponential(0.2s);
            @display("is=vl;p=429,291");
        }
        srcLP: fuzzybuffersim.Source {
            priority = 0;
            interArrivalTime = exponential(0.1s);
            @display("is=vl;p=28,36");
        }
        queue: fuzzybuffersim.FuzzyQueue {
            @display("is=vl;p=220,164");
        }
        sink: fuzzybuffersim.Sink {
            @display("is=vl;p=396,27");
        }
    connections:
        srcHP.out --> queue.in++;
        srcLP.out --> queue.in++;
        queue.out --> sink.in;
}

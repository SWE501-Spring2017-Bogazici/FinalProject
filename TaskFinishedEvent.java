/**
 * Created by veraxmedax on 04/06/2017.
 */
public class TaskFinishedEvent extends Event {
    public TaskFinishedEvent(Simulation sim, Task task, double time) {
        super(sim, task, time);
    }

    @Override
    void process() {
        // do nothing
    }
}

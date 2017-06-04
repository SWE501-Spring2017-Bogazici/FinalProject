/**
 * Created by veraxmedax on 03/06/2017.
 */
public class TaskOutArrivalEvent extends Event {

    public TaskOutArrivalEvent(Simulation sim, Task task, double time) {
        super(sim, task, time);
    }

    @Override
    void process() {
        OutputDevice outputDevice = getSim().getFirstIdleOutputDevice();
        if (outputDevice != null) {
            Event outInEvent = new OutInEvent(getSim(), getTask(), getTime(), outputDevice);
            getSim().schedule(outInEvent);
        } else {
            getSim().getRrQueue().add(getTask());
        }
    }
}

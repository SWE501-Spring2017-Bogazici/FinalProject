/**
 * Created by veraxmedax on 04/06/2017.
 */
public class OutFreeEvent extends Event {
    private OutputDevice outputDevice;

    public OutFreeEvent(Simulation sim, Task task, double time, OutputDevice outputDevice) {
        super(sim, task, time);
        this.outputDevice = outputDevice;
    }

    public OutputDevice getOutputDevice() {
        return outputDevice;
    }

    public void setOutputDevice(OutputDevice outputDevice) {
        this.outputDevice = outputDevice;
    }

    @Override
    void process() {
        getOutputDevice().setIdle(true);
        if (getTask().isFinished()) {
            Event taskFinishedEvent = new TaskFinishedEvent(getSim(), getTask(), getTime());
            getSim().schedule(taskFinishedEvent);
        } else {
            getSim().getRrQueue().add(getTask());
        }
        setTask(getSim().getRrQueue().peek());
        double newTime = getTask().getWaitOut() + getTime() - getTask().getOutTime();
        getTask().setWaitOut(newTime);
        Event taskOutArrivalEvent = new TaskOutArrivalEvent(getSim(), getTask(), getTime());
        getSim().schedule(taskOutArrivalEvent);
    }
}

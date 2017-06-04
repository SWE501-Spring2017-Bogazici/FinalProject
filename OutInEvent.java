/**
 * Created by veraxmedax on 04/06/2017.
 */
public class OutInEvent extends Event {

    private OutputDevice outputDevice;

    public OutInEvent(Simulation sim, Task task, double time, OutputDevice outputDevice) {
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
        getOutputDevice().work(getTask(), getTime());
    }
}

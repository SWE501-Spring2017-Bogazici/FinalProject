/**
 * Created by veraxmedax on 03/06/2017.
 */
public abstract class Event {
    private Simulation sim;
    private Task task;
    private double time;

    public Event() {
    }

    public Event(Simulation sim, Task task, double time) {
        this.sim = sim;
        this.task = task;
        this.time = time;
    }

    public double getTime() {
        return time;
    }

    public void setTime(double time) {
        this.time = time;
    }

    public Task getTask() {
        return task;
    }

    public void setTask(Task task) {
        this.task = task;
    }

    public Simulation getSim() {
        return sim;
    }

    public void setSim(Simulation sim) {
        this.sim = sim;
    }

    abstract void process();

    @Override
    public String toString() {
        return "Event{" +
                "time=" + time +
                ", task=" + task +
                ", sim=" + sim +
                '}';
    }
}

/**
 * Created by veraxmedax on 03/06/2017.
 */
public class OutputDevice {
    private int id;
    private boolean idle;
    private double quantum;
    private double activeTime;
    private Simulation sim;

    public OutputDevice(int id, double quantum, Simulation sim) {
        this.idle = true;
        this.id = id;
        this.quantum = quantum;
        this.sim = sim;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public boolean isIdle() {
        return idle;
    }

    public void setIdle(boolean idle) {
        this.idle = idle;
    }

    public double getQuantum() {
        return quantum;
    }

    public void setQuantum(double quantum) {
        this.quantum = quantum;
    }

    public double getActiveTime() {
        return activeTime;
    }

    public void setActiveTime(double activeTime) {
        this.activeTime = activeTime;
    }

    public Simulation getSim() {
        return sim;
    }

    public void setSim(Simulation sim) {
        this.sim = sim;
    }

    public void work(Task task, double now) {
        setIdle(false);
        if (task.getRemainingOutWork() <= getQuantum()) {
            task.setOutTime(now + task.getRemainingOutWork());
            setActiveTime(getActiveTime() + task.getRemainingOutWork());
            Event outFreeEvent = new OutFreeEvent(getSim(), task, task.getOutTime(), this);
            getSim().schedule(outFreeEvent);
            task.setRemainingOutWork(0);
            task.setFinished(true);
        } else {
            double newTime = task.getRemainingOutWork() - getQuantum();
            task.setRemainingOutWork(newTime);
            setActiveTime(getActiveTime() + getQuantum());
            task.setOutTime(now + getQuantum());
            Event outFreeEvent = new OutFreeEvent(getSim(), task, task.getOutTime(), this);
            getSim().schedule(outFreeEvent);
        }
    }
}

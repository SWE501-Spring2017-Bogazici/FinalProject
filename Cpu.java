/**
 * Created by veraxmedax on 03/06/2017.
 */
public class Cpu {
    private int id;
    private boolean idle;
    private double freq;
    private double activeTime;

    public Cpu(int id, double freq) {
        this.id = id;
        this.idle = true;
        this.freq = freq;
        this.activeTime = 0.0;
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

    public double getFreq() {
        return freq;
    }

    public void setFreq(double freq) {
        this.freq = freq;
    }

    public double getActiveTime() {
        return activeTime;
    }

    public void setActiveTime(double activeTime) {
        this.activeTime = activeTime;
    }

    void work(Task task, double now) {
        idle = false;
        task.setCpuServiceStart(now);
        double processingTime = task.getCpuWork() / this.getFreq();
        task.setCpuServiceStop(now + processingTime);
        setActiveTime(getActiveTime() + processingTime);
    }
}

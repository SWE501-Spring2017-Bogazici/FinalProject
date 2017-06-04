/**
 * Created by veraxmedax on 03/06/2017.
 */
public class CpuOutEvent extends Event {
    private Cpu cpu;

    public CpuOutEvent(Simulation sim, Task task, double time, Cpu cpu) {
        super(sim, task, time);
        this.cpu = cpu;
    }

    public Cpu getCpu() {
        return cpu;
    }

    public void setCpu(Cpu cpu) {
        this.cpu = cpu;
    }

    @Override
    void process() {
        getCpu().setIdle(true);
        if (!getSim().getSjfQueue().isEmpty()) {
            Task newTask = getSim().getSjfQueue().poll();
            Event cpuInEvent = new CpuInEvent(getSim(), newTask, getTime(), cpu);
            getSim().schedule(cpuInEvent);
        }
        // Move inside if block
        getTask().setOutTime(getTime());
        Event taskOutArrivalEvent = new TaskOutArrivalEvent(getSim(), getTask(), getTime());
        getSim().schedule(taskOutArrivalEvent);
    }
}

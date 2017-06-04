/**
 * Created by veraxmedax on 03/06/2017.
 */
public class CpuInEvent extends Event {
    private Cpu cpu;

    public CpuInEvent(Simulation sim, Task task, double time, Cpu cpu) {
        setSim(sim);
        setTask(task);
        setTime(time);
        setCpu(cpu);
    }

    @Override
    void process() {
        double duration = getTime() - (getTask().getArrivalTime());
        getTask().setWaitCpu(duration);
        getCpu().work(getTask(), getTime());
        CpuOutEvent cpuOutEvent = new CpuOutEvent(getSim(), getTask(), getTask().getCpuServiceStop(), getCpu());
        getSim().schedule(cpuOutEvent);
    }

    public Cpu getCpu() {
        return cpu;
    }

    public void setCpu(Cpu cpu) {
        this.cpu = cpu;
    }
}

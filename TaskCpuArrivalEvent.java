/**
 * Created by veraxmedax on 03/06/2017.
 */
public class TaskCpuArrivalEvent extends Event {

    public TaskCpuArrivalEvent(Simulation sim, Task task, double time) {
        super(sim, task, time);
    }

    @Override
    void process() {
        Cpu cpu = getSim().getFirstIdleCpu();
        if (cpu != null) {
            Event cpuInEvent = new CpuInEvent(getSim(), getTask(), getTime(), cpu);
            getSim().schedule(cpuInEvent);
        } else {
            getSim().getSjfQueue().add(getTask());
        }
    }
}

/**
 * Created by veraxmedax on 03/06/2017.
 */
public class DiscreteEventSimulationApplication {

    public static void main(String[] args) {
        Simulation sim = new Simulation();

        Cpu cpu1 = new Cpu(1, 1.0);
        Cpu cpu2 = new Cpu(2, 2.0);
        sim.addCpu(cpu1);
        sim.addCpu(cpu2);

        OutputDevice o1 = new OutputDevice(1, 5.0, sim);
        OutputDevice o2 = new OutputDevice(2, 10.0, sim);
        sim.addOutputDevice(o1);
        sim.addOutputDevice(o2);

        Task t0 = new Task(0, 10.0, 5.0);
        Task t1 = new Task(1, 22.0, 20.0);
        Task t2 = new Task(2, 5.0, 2.0);
        Task t3 = new Task(3, 3.0, 50.0);
        sim.addTask(t0);
        sim.addTask(t1);
        sim.addTask(t2);
        sim.addTask(t3);

        sim.run();
    }
}

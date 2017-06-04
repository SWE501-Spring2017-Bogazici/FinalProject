import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

/**
 * Created by veraxmedax on 03/06/2017.
 */
public class Simulation {
    private double time;
    private int sjf_queue_max_size;
    private int rr_queue_max_size;
    private int max_active_cpu_id;
    private int max_active_out_id;
    private double average_wait_time;
    private double longest_wait_time;
    private double average_time_spent;
    private double grand_total_wait;
    private double total_time_spent;

    private List<Cpu> cpus = new ArrayList<>();
    private List<OutputDevice> outs = new ArrayList<>();
    private List<Task> tasks = new ArrayList<>();

    private SJFCompare sjfCompare = new SJFCompare();
    private RoundRobinCompare roundRobinCompare = new RoundRobinCompare();
    private EventTimeCompare eventTimeCompare = new EventTimeCompare();

    private PriorityQueue<Event> futureEventsQueue;
    private PriorityQueue<Task> sjfQueue;
    private PriorityQueue<Task> rrQueue;
    private double max_cpu_active_time;
    private double max_out_active_time;
    private int current_sjf_size;
    private int current_rr_size;

    public Simulation() {
        futureEventsQueue = new PriorityQueue<>(eventTimeCompare);
        sjfQueue = new PriorityQueue<>(sjfCompare);
        rrQueue = new PriorityQueue<>(roundRobinCompare);
    }

    public List<Cpu> getCpus() {
        return cpus;
    }

    public void setCpus(List<Cpu> cpus) {
        this.cpus = cpus;
    }

    public List<OutputDevice> getOuts() {
        return outs;
    }

    public void setOuts(List<OutputDevice> outs) {
        this.outs = outs;
    }

    public List<Task> getTasks() {
        return tasks;
    }

    public void setTasks(List<Task> tasks) {
        this.tasks = tasks;
    }

    public double getTime() {
        return time;
    }

    public void setTime(double time) {
        this.time = time;
    }

    void addCpu(Cpu cpu) {
        cpus.add(cpu);
    }

    void addOutputDevice(OutputDevice out) {
        out.setSim(this);
        outs.add(out);
    }

    void addTask(Task task) {
        tasks.add(task);
    }

    void run() {
        for (Task task : tasks) {
            TaskCpuArrivalEvent event = new TaskCpuArrivalEvent(this, task, task.getArrivalTime());
            futureEventsQueue.add(event);
        }

        while (!futureEventsQueue.isEmpty()) {
            Event event = futureEventsQueue.poll();
            setTime(event.getTime());
            event.process();

            current_sjf_size = sjfQueue.size();
            if (current_sjf_size > sjf_queue_max_size) {
                sjf_queue_max_size = current_sjf_size;
            }

            current_rr_size = rrQueue.size();
            if (current_rr_size > rr_queue_max_size) {
                rr_queue_max_size = current_rr_size;
            }

            if (futureEventsQueue.isEmpty()) {
                break;
            }

            max_cpu_active_time = 0;
        }

        for (Cpu cpu : getCpus()) {
            if (cpu.getActiveTime() > max_cpu_active_time) {
                max_cpu_active_time = cpu.getActiveTime();
                max_active_cpu_id = cpu.getId();
            }
        }

        max_out_active_time = 0;
        for (OutputDevice outputDevice : getOuts()) {
            if (outputDevice.getActiveTime() > max_out_active_time) {
                max_out_active_time = outputDevice.getActiveTime();
                max_active_out_id = outputDevice.getId();
            }
        }

        grand_total_wait = 0.0;
        total_time_spent = 0.0;

        for (Task task : getTasks()) {
            double time_spent = task.getOutTime() - task.getArrivalTime();
            total_time_spent += time_spent;
            double total_wait = task.getWaitCpu() + task.getWaitOut();
            grand_total_wait += total_wait;

            if (total_wait > longest_wait_time) {
                longest_wait_time = total_wait;
            }
        }

        average_wait_time = grand_total_wait / tasks.size();
        average_time_spent = total_time_spent / tasks.size();

        System.out.println("sjf_queue_max_size: " + sjf_queue_max_size);
        System.out.println("rr_queue_max_size: " + rr_queue_max_size);
        System.out.println("max_active_cpu_id: " + max_active_cpu_id);
        System.out.println("max_active_out_id: " + max_active_out_id);
        System.out.println("average_wait_time: " + average_wait_time);
        System.out.println("longest_wait_time: " + longest_wait_time);
        System.out.println("average_time_spent: " + average_time_spent);

    }

    void schedule(Event event) {
        futureEventsQueue.add(event);
    }

    Event popEvent() {
        Event top = futureEventsQueue.poll();
        futureEventsQueue.remove(top);
        return top;
    }

    OutputDevice getFirstIdleOutputDevice() {
        for(OutputDevice outputDevice : outs) {
            if (outputDevice.isIdle()) {
                return outputDevice;
            }
        }
        return null;
    }

    Cpu getFirstIdleCpu() {
        for (Cpu cpu : cpus) {
            if (cpu.isIdle()) {
                return cpu;
            }
        }
        return null;
    }

    public PriorityQueue<Event> getFutureEventsQueue() {
        return futureEventsQueue;
    }

    public void setFutureEventsQueue(PriorityQueue<Event> futureEventsQueue) {
        this.futureEventsQueue = futureEventsQueue;
    }

    public PriorityQueue<Task> getSjfQueue() {
        return sjfQueue;
    }

    public void setSjfQueue(PriorityQueue<Task> sjfQueue) {
        this.sjfQueue = sjfQueue;
    }

    public PriorityQueue<Task> getRrQueue() {
        return rrQueue;
    }

    public void setRrQueue(PriorityQueue<Task> rrQueue) {
        this.rrQueue = rrQueue;
    }
}

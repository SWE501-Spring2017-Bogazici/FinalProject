
/**
 * Created by fparlayan on 6/4/2017.
 */
public class Work {

    private String name;
    private double arrival_time, GPU_work, Output_work,waiting_time;
    private boolean done;

    public Work(String name, double arrival_time, double GPU_work, double output_work) {
        this.name = name;
        this.arrival_time = arrival_time;
        this.GPU_work = GPU_work;
        Output_work = output_work;
    }

    public String getName() {
        return name;
    }

    public double getArrival_time() {
        return arrival_time;
    }

    public double getGPU_work() {
        return GPU_work;
    }

    public boolean isDone() {
        return done;
    }

    public void setDone(boolean done) {
        this.done = done;
    }

    public double getWaiting_time() {
        return waiting_time;
    }

    public void setWaiting_time(double waiting_time) {
        this.waiting_time = waiting_time;
    }

    public double getOutput_work() {
        return Output_work;
    }
}

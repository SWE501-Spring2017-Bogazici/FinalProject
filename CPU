/**
 * Created by fparlayan on 6/4/2017.
 */
public class CPU {

    private String name = "CPU ";
    private int frequency;
    private boolean isAvaliable = true;
    private double workingTime = 0.0;
    private double requiredTime = 0.0;

    public CPU(String name, int frequency) {
        this.name = this.name + name;
        this.frequency = frequency;
    }

    public void setAvaliable(boolean avaliable) {
        isAvaliable = avaliable;
    }

    public String getName() {
        return name;
    }

    public void setRequiredTime(double requiredTime) {
        this.requiredTime = requiredTime;
    }

    public int getFrequency() {
        return frequency;
    }

    public boolean isAvaliable() {
        return isAvaliable;
    }

    public double getWorkingTime() {
        return workingTime;
    }

    private void setRequiredTimeForJob(double GPU_Work) {
        requiredTime = GPU_Work / frequency;
        workingTime = workingTime + requiredTime;
    }

    public double getRequiredTime() {
        return requiredTime;
    }

    public void doWork(Work work) {
        if(work != null){
            System.out.println(getName() + " doing " + work.getName());
            isAvaliable = false;
            setRequiredTimeForJob(work.getGPU_work());
            work.setDone(true);
        }
    }
}

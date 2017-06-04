/**
 * Created by veraxmedax on 03/06/2017.
 */
public class Task {
    private int id;
    private double arrivalTime;
    private double cpuWork;
    private double outputWork;
    private double remainingOutWork;
    private double cpuServiceStart;
    private double cpuServiceStop;
    private double outTime;
    private double waitCpu;
    private double waitOut;
    private boolean isFinished;

    public Task(double cpuWork, double arrivalTime, double outputWork) {
        this.cpuWork = cpuWork;
        this.arrivalTime = arrivalTime;
        this.outputWork = outputWork;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getArrivalTime() {
        return arrivalTime;
    }

    public void setArrivalTime(double arrivalTime) {
        this.arrivalTime = arrivalTime;
    }

    public double getCpuWork() {
        return cpuWork;
    }

    public void setCpuWork(double cpuWork) {
        this.cpuWork = cpuWork;
    }

    public double getOutputWork() {
        return outputWork;
    }

    public void setOutputWork(double outputWork) {
        this.outputWork = outputWork;
    }

    public double getCpuServiceStart() {
        return cpuServiceStart;
    }

    public void setCpuServiceStart(double cpuServiceStart) {
        this.cpuServiceStart = cpuServiceStart;
    }

    public double getCpuServiceStop() {
        return cpuServiceStop;
    }

    public void setCpuServiceStop(double cpuServiceStop) {
        this.cpuServiceStop = cpuServiceStop;
    }

    public double getOutTime() {
        return outTime;
    }

    public void setOutTime(double outTime) {
        this.outTime = outTime;
    }

    public boolean isFinished() {
        return isFinished;
    }

    public void setFinished(boolean finished) {
        isFinished = finished;
    }

    public double getWaitCpu() {
        return waitCpu;
    }

    public void setWaitCpu(int waitCpu) {
        this.waitCpu = waitCpu;
    }

    public double getWaitOut() {
        return waitOut;
    }

    public void setWaitOut(double waitOut) {
        this.waitOut = waitOut;
    }

    public double getRemainingOutWork() {
        return remainingOutWork;
    }

    public void setRemainingOutWork(double remainingOutWork) {
        this.remainingOutWork = remainingOutWork;
    }

    public void setWaitCpu(double waitCpu) {
        this.waitCpu = waitCpu;
    }


}

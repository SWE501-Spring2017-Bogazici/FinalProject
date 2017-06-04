import java.util.ArrayList;
import java.util.List;

/**
 * Created by fparlayan on 6/4/2017.
 */
public class main {

    static List<CPU> cpuList = new ArrayList<CPU>();

    public static void main(String[] args) {

        CPU cpu1 = new CPU("1", 1);
        CPU cpu2 = new CPU("2", 2);

        cpuList.add(cpu1);
        cpuList.add(cpu2);

        Output output1 = new Output("1", 5);
        Output output2 = new Output("2", 10);

        Work work1 = new Work("work1", 0, 10, 5);
        Work work2 = new Work("work2", 1, 22, 20);
        Work work3 = new Work("work3", 2, 5, 2);
        Work work4 = new Work("work4", 3, 3, 50);

        ShortestJobFirstQueue.addWorktoQueue(work1);
        ShortestJobFirstQueue.addWorktoQueue(work2);
        ShortestJobFirstQueue.addWorktoQueue(work3);
        ShortestJobFirstQueue.addWorktoQueue(work4);
        System.out.println(ShortestJobFirstQueue.queue.size());

        while (ShortestJobFirstQueue.queue.size() > 0) {
            for (CPU cpu : cpuList) {
                if (cpu.isAvaliable()) {
                    cpu.doWork(ShortestJobFirstQueue.getWork());
                    releaseCPU();
                }
            }
        }
        for (CPU cpu : cpuList) {
            System.out.println("working time . " + cpu.getName() + " " + cpu.getWorkingTime());
        }

    }

    public static void releaseCPU() {
        double passedTime = 10000;
        for (CPU cpu : cpuList) {
            if (cpu.getRequiredTime() < passedTime) {
                passedTime = cpu.getRequiredTime();
            }
        }
        for (CPU cpu : cpuList) {
            if (passedTime == cpu.getRequiredTime()) {
                cpu.setAvaliable(true);
            }
            cpu.setRequiredTime(cpu.getRequiredTime() - passedTime);
        }
        for (Work work : ShortestJobFirstQueue.queue) {
            work.setWaiting_time(work.getWaiting_time() + passedTime);
            System.out.println("waiting tim of work "+work.getWaiting_time());
        }
    }

}

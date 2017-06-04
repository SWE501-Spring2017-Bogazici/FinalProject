import java.util.ArrayList;
import java.util.List;

/**
 * Created by fparlayan on 6/4/2017.
 */
public class ShortestJobFirstQueue {

    public static List<Work> queue = new ArrayList<Work>();

    public static void addWorktoQueue(Work work) {
        if (queue.size() < 1) {
            queue.add(work);
        } else {
            for (int i = 0; i < queue.size(); i++) {
                if (queue.get(i).getGPU_work() > work.getGPU_work()) {
                    queue.add(0,work);
                    break;
                }else {
                    queue.add(work);
                    break;
                }
            }
        }
    }

    public static Work getWork() {
        if(queue.size() > 0){
            Work work = queue.get(0);
            queue.remove(0);
            return work;
        }
        return null;
    }

}

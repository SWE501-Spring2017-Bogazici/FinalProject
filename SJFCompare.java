import java.util.Comparator;

/**
 * Created by veraxmedax on 04/06/2017.
 */
public class SJFCompare implements Comparator<Object> {

    @Override
    public int compare(Object o1, Object o2) {
        Task t1 = (Task) o1;
        Task t2 = (Task) o2;
        return Double.compare(t1.getCpuWork(), t2.getCpuWork());
    }
}

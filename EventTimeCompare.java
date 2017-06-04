import java.util.Comparator;

/**
 * Created by veraxmedax on 04/06/2017.
 */
public class EventTimeCompare implements Comparator {

    @Override
    public int compare(Object o1, Object o2) {
        Event event1 = (Event) o1;
        Event event2 = (Event) o2;
        return Double.compare(event1.getTime(), event2.getTime());
    }
}

import java.util.ArrayList;
import java.util.List;

public class ContextUtils {
    private static List<String> arrays = new ArrayList<>();

    public static void add() {
        arrays.add("123");
    }

    public static List<String> get() {
        return arrays;
    }

    public static void clear() {
        arrays = new ArrayList<>();
    }
}

public class demo {
    public void demoF() {
        try {
            ContextUtils.add();
        } finally {
            ContextUtils.clear();
        }
    }
}

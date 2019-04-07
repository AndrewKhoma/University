public class chown {
  private static String PROGRAM_NAME = "chown";

  public static void main(String[] args) throws Exception {
    Kernel.initialize();
    if (args.length < 2) {
      Kernel.perror("USAGE: chown <uid_number> <entry_names>...");
      Kernel.exit(1);
    }
    short uid = Short.valueOf(args[0]);
    for (int i = 1; i < args.length; i++) {
      int status = Kernel.chown(args[i], uid);
      if (status < 0) {
        Kernel.perror(PROGRAM_NAME);
        System.err.println(PROGRAM_NAME + ": unable to find inode");
        Kernel.exit(1);
      }
    }
    Kernel.exit(0);
  }
}

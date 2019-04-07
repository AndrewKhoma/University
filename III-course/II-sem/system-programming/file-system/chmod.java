public class chmod {
  private static String PROGRAM_NAME = "chomd";

  public static void main(String[] args) throws Exception {
    Kernel.initialize();
    if (args.length < 2) {
      Kernel.perror("USAGE: chown <mode> <entry_names>...");
      Kernel.exit(1);
    }
    short mode = Short.valueOf(args[0]);
    for (int i = 1; i < args.length; i++) {
      if (mode < 0 || mode > 777) {
        Kernel.perror(PROGRAM_NAME);
        System.err.println(PROGRAM_NAME + ": unable to set mode with " + mode + " value");
        Kernel.exit(1);
      }
      int status = Kernel.chmod(args[i], mode);
      if (status < 0) {
        Kernel.perror(PROGRAM_NAME);
        System.err.println(PROGRAM_NAME + ": unable to find inode");
        Kernel.exit(1);
      }
    }
    Kernel.exit(0);
  }
}

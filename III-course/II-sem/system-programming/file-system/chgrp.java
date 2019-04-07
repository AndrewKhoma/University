public class chgrp {
  private static String PROGRAM_NAME = "chgrp";

  public static void main(String[] args) throws Exception {
    Kernel.initialize();
    if (args.length < 2) {
      Kernel.perror("USAGE: chown <gid_number> <entry_names>...");
      Kernel.exit(1);
    }
    short gid = Short.valueOf(args[0]);
    for (int i = 1; i < args.length; i++) {
      int status = Kernel.chgrp(args[i], gid);
      if (status < 0) {
        Kernel.perror(PROGRAM_NAME);
        System.err.println(PROGRAM_NAME + ": unable to find inode");
        Kernel.exit(1);
      }
    }
    Kernel.exit(0);
  }
}

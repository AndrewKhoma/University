/*
 * Created by ahoma on 28/03/2019.
 * Copyright (c) 2019 Andrii Khoma. All rights reserved.
 */

public class ln {
  /**
   * The name of this program. This is the program name that is used when displaying error messages.
   */
  public static final String PROGRAM_NAME = "ln";

  /**
   * Makes hard link
   *
   * @exception java.lang.Exception if an exception is thrown by an underlying operation
   */
  public static void main(String[] argv) throws Exception {
    // initialize the file system simulator kernel
    Kernel.initialize();

    // display a helpful message if no arguments are given
    if (argv.length != 2) {
      System.err.println(
          PROGRAM_NAME + ": usage: java " + PROGRAM_NAME + " input-file1 input-file2");
      Kernel.exit(1);
    }

    System.out.println("Path 1: " + argv[0]);
    System.out.println("Path 2: " + argv[1]);
    int result = Kernel.link(argv[0], argv[1]);

    if (result < 0) {
      Kernel.perror(PROGRAM_NAME);
      Kernel.exit(1);
    }

    // exit with success if we read all the files without error
    Kernel.exit(0);
  }
}

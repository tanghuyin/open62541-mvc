import java.io.File;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class testFile {

    public static void main(String[] args) {

        Thread thread1 = new Thread(new Runnable() {
            @Override
            public void run() {
                File file1 = new File("2020_03_27_hat.json");
                System.out.println(file1.exists());
                long lastModified = 0;
                while (true) {
                    if (lastModified != file1.lastModified()) {
                        System.out.println("2020_03_27_hat.json" + "+changed");
                        lastModified = file1.lastModified();
                    }
                    try {
                        TimeUnit.SECONDS.sleep(1);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        Thread thread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                File file1 = new File("2020_03_27.json");
                System.out.println(file1.exists());
                long lastModified = 0;
                while (true) {
                    if (lastModified != file1.lastModified()) {
                        System.out.println("2020_03_27.json" + "+changed");
                        lastModified = file1.lastModified();
                    }
                    try {
                        TimeUnit.SECONDS.sleep(1);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        Thread thread3 = new Thread(new Runnable() {
            @Override
            public void run() {
                File file1 = new File("2020_03_27_lbgk.json");
                System.out.println(file1.exists());
                long lastModified = 0;
                while (true) {
                    if (lastModified != file1.lastModified()) {
                        System.out.println("2020_03_27_lbgk.json" + "+changed");
                        lastModified = file1.lastModified();
                    }
                    try {
                        TimeUnit.SECONDS.sleep(1);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        thread1.start();
        thread2.start();
        thread3.start();
        Scanner scanner = new Scanner(System.in);
        scanner.next();
    }

}

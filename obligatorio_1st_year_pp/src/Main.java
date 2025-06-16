import java.util.Random;
import java.util.Scanner;

public class Main {
    public static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {

        int balance = 0;
        int bet = 0;
        boolean pride = false;
        int choice = 0;
        int outcome = 0;
        boolean hit = false;
        final int BALANCE_LIMIT = 1000;
        final int MINIMAL_BET = 50;
        Random random = new Random();

        System.out.println("Welcome, we will start to play now. For each bet you must state with a 1 2 or 3, in which cup the ball is located. \nRemember that you can also chose to leave the game");
        balance = initialBalance();

        if (balance < MINIMAL_BET || balance > BALANCE_LIMIT)
            System.out.println("The balance must be between 50 y 1000");

        choice = startGame();
        while (choice != 4 || balance > MINIMAL_BET) {
            outcome = random.nextInt(3) + 1;

            bet = placeBet();

            while (bet < MINIMAL_BET || bet> balance) {
                System.out.printf("You can only place your bet between %d y %d %n", MINIMAL_BET, balance);
                System.out.println("How much would you like to bet?");
                bet = placeBet();
            }

            createCups(outcome, 3);
            hit = checkOutcome(outcome, choice);

            if (hit) {
                System.out.println("Congratulations! You have won");
            } else {
                System.out.println("Bummer, You have lost");
            }
            balance = updateBalance(balance, hit, bet);

            choice = startGame();
            if (bet > 200 && !hit && choice == 4) {
                while (choice != 3) {
                    System.out.println("You are a proud person so you cannot leave, you must play again");
                    choice = startGame();
                }
            }

        }
        System.out.println("See you later alligator");

    }

    static int initialBalance() {
        System.out.println(" Now, how much money do you have?");
        return sc.nextInt();
    }

    static int startGame() {
        System.out.println("0 0 0");
        System.out.println("1 2 3");
        System.out.println("Cup?");

        return sc.nextInt();
    }

    static int placeBet() {
        System.out.println("How much would you like to bet?");

        return sc.nextInt();
    }

    static void createCups(int value, int length) {

        for (int x = 1; x <= length; x++)
            if (x == value) System.out.print(". ");
            else System.out.print("0 ");
        System.out.print("\n");
    }

    static boolean checkOutcome(int outcome, int choice) {
        return outcome == choice;
    }

    static int updateBalance(int balance, boolean outcome, int bet) {
        if (outcome) balance += bet;
        else balance -= bet;
        System.out.println("Current balance: " + balance);
        return balance;
    }
}
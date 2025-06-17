import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Main {

    final static int BALANCE_LIMIT = 1000;
    final static int MINIMAL_BET = 50;
    final static int GAME_SIZE = 5;

    static List<Player> players = new ArrayList<>();
    static List<Bet> bets = new ArrayList<>();


    public static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {


        System.out.println("Welcome to the game menu, please chose the option suits you best");
        System.out.println("1 - Player management");
        System.out.println("2 - Game queries");
        System.out.println("3 - Play the game");
        System.out.println("4 - Exit");

        switch (sc.nextInt()) {
            case 1 -> playerManagement();
            case 2 -> gameQueries();
            case 3 -> playGame();
            case 4 -> System.out.println("Good bye!");
        }

    }

    public static void playerManagement() {
        System.out.println("Welcome to the player management menu, please chose the option suits you best");
        System.out.println("1 - Create Player");
        System.out.println("2 - Update Player");
        System.out.println("3 - Delete Player");
        System.out.println("4 - Back to previous menu");

        switch (sc.nextInt()) {
            case 1 -> createPlayer();
            case 2 -> updatePlayer();
            case 3 -> deletePlayer();
            case 4 -> System.out.println("Going back...");
        }
    }

    public static void createPlayer() {
        Player DTOPlayer;

        System.out.println("Please enter the player's nickname");

        DTOPlayer = checkExistingNickname(sc.next());
        if (DTOPlayer != null) {
            System.out.println("A player already exists with the provided nickname");
            if (!DTOPlayer.isActive())
                System.out.println("The player has been reactivated");
            return;
        }
        DTOPlayer = new Player();
        DTOPlayer.setNickName(sc.next());

        System.out.println("Please enter the player's id");
        DTOPlayer.setId(sc.nextLong());

        if (checkExistingID(DTOPlayer.getId())) {
            System.out.println("The ID provided is not valid");
            return;
        }

        System.out.println("Please enter the player's firstname");
        DTOPlayer.setFirstName(sc.next());

        System.out.println("Please enter the player's lastname");
        DTOPlayer.setLastName(sc.next());

        DTOPlayer.setBalance(1000);
        DTOPlayer.setActive(true);

        Player player = new Player(DTOPlayer.getId(), DTOPlayer.getNickName(), DTOPlayer.getFirstName(), DTOPlayer.getLastName(), DTOPlayer.isActive(), DTOPlayer.getBalance());
        players.add(player);

        System.out.println("Player created successfully");

    }

    public static Player checkExistingNickname(String nickName) {

        return players.stream()
                .filter(p -> p.getNickName().equalsIgnoreCase(nickName))
                .findFirst()
                .orElse(null);
    }

    public static boolean checkExistingID(long id) {
        return id < 1111111 || id > 99999999;
    }

    public static void updatePlayer() {

    }

    public static void deletePlayer() {

    }

    public static void gameQueries() {

    }

    private static void playGame() {
        int balance;
        int bet;
        int choice ;
        int outcome;
        boolean hit;

        Random random = new Random();

        System.out.println("Welcome, we will start to play now. For each bet you must state with a 1 2 or 3, in which cup the ball is located. \nRemember that you can also chose to leave the game by tiping " + (GAME_SIZE + 1));
        balance = initialBalance();

        while (balance < MINIMAL_BET || balance > BALANCE_LIMIT) {
            System.out.println("The balance must be between 50 y 1000");
            balance = initialBalance();
        }
        choice = createCups();

        while (choice != (GAME_SIZE + 1) && balance >= MINIMAL_BET) {
            outcome = random.nextInt(3) + 1;

            bet = placeBet();

            while (bet < MINIMAL_BET || bet > balance) {
                System.out.printf("You can only place your bet between %d y %d %n", MINIMAL_BET, balance);
                System.out.println("How much would you like to bet?");
                bet = placeBet();
            }

            createWinningCup(outcome);
            hit = outcome == choice;

            if (hit) {
                System.out.println("Congratulations! You have won");
            } else {
                System.out.println("Bummer, You have lost");
            }
            balance = updateBalance(balance, hit, bet);
            System.out.printf("Your current balance is: %d \n", balance);

            if (balance < MINIMAL_BET)
                break;
            else {
                choice = createCups();

                if (bet > 200 && !hit && choice == (GAME_SIZE + 1)) {
                    while (choice == (GAME_SIZE + 1)) {
                        System.out.println("You are a proud person so you cannot leave, you must play again");
                        choice = createCups();
                    }
                }
            }
        }
        if (balance < MINIMAL_BET)
            System.out.println("Money talks, and you cannot talk");
        else
            System.out.println("See you later alligator");
    }

    static int initialBalance() {
        System.out.println("Now, how much money do you have?");
        return sc.nextInt();
    }

    static int createCups() {
        for (int x = 1; x <= GAME_SIZE; x++) {
            System.out.print("0 ");

        }
        System.out.print("\n");

        for (int x = 1; x <= GAME_SIZE; x++) {
            System.out.print(x + " ");
        }
        System.out.print("\n");

        System.out.println("Cup?");

        int choice = sc.nextInt();

        while (choice > (GAME_SIZE + 1) || choice <= 0) {
            System.out.println("Please chose between 1 and " + (GAME_SIZE + 1));
            System.out.println("Cup?");
            choice = sc.nextInt();
        }
        return choice;

    }

    static int placeBet() {
        System.out.println("How much would you like to bet?");

        return sc.nextInt();
    }

    static void createWinningCup(int value) {

        for (int x = 1; x <= GAME_SIZE; x++)
            if (x == value) System.out.print(". ");
            else System.out.print("0 ");
        System.out.print("\n");
    }


    static int updateBalance(int balance, boolean outcome, int bet) {
        if (outcome) balance += bet;
        else balance -= bet;
        return balance;
    }
}
import java.util.*;

public class Main {

    final static int MINIMAL_BET = 50;
    final static int GAME_SIZE = 5;
    final static int BALANCE = 1000;

    static List<Player> players = new ArrayList<>();
    static List<Bet> bets = new ArrayList<>();


    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {

        testData();
        int choice = 0;

        while (choice != 4) {
            System.out.println("Welcome to the game menu, please chose the option suits you best");
            System.out.println("1 - Player management");
            System.out.println("2 - Game queries");
            System.out.println("3 - Play the game");
            System.out.println("4 - Exit");

            choice = sc.nextInt();

            switch (choice) {
                case 1 -> playerManagement();
                case 2 -> gameQueries();
                case 3 -> playGame();
                case 4 -> System.out.println("Good bye!");
            }
        }
    }

    static void testData() {

        players.add(new Player(63333333, "Carleto", "Carlos", "Ramírez", true, 1000));
        players.add(new Player(52222222, "Marita", "María", "Gómez", true, 1000));
        players.add(new Player(41111111, "Juanca", "Juan Carlos", "Fernández", true, 1000));
        players.add(new Player(41111111, "Auanca", "Juan Carlos", "Fernández", true, 1000));
        players.add(new Player(41111111, "Buanca", "Juan Carlos", "Fernández", true, 1000));

        bets.add(new Bet(150, false, "Carleto", 850));
        bets.add(new Bet(150, true, "Marita", 1150));
        bets.add(new Bet(300, false, "Carleto", 550));
        bets.add(new Bet(550, true, "Carleto", 1100));
        bets.add(new Bet(100, false, "Carleto", 1000));
        bets.add(new Bet(700, false, "Juanca", 1000));
    }

    static void playerManagement() {
        int choice = 0;

        while (choice != 4) {
            System.out.println("Welcome to the player management menu, please choose the option that suits you best:");
            System.out.println("1 - Create Player");
            System.out.println("2 - Update Player");
            System.out.println("3 - Delete Player");
            System.out.println("4 - Back to previous menu");

            choice = sc.nextInt();

            switch (choice) {
                case 1 -> createPlayer();
                case 2 -> updatePlayer();
                case 3 -> deletePlayer();
                case 4 -> System.out.println("Going back...");
                default -> System.out.println("❌ Invalid option. Please try again.");
            }
        }
    }


     static void createPlayer() {

        System.out.println("Please enter the player's nickname");

        Player checkPlayer = getPlayer(sc.next());
        if (checkPlayer != null) {
            System.out.println("A player already exists with the provided nickname");
            if (!checkPlayer.isActive()) {
                checkPlayer.setActive(true);
                updatePlayer(checkPlayer);
                System.out.println("The player has been reactivated");
                return;
            }
        }

        Player DTOPlayer = new Player();
        DTOPlayer.setNickName(sc.next());

        System.out.println("Please enter the player's id");
        DTOPlayer.setId(sc.nextLong());

        if (checkValidID(DTOPlayer.getId())) {
            System.out.println("The ID provided is not valid");
            return;
        }

        System.out.println("Please enter the player's firstname");
        DTOPlayer.setFirstName(sc.next());

        System.out.println("Please enter the player's lastname");
        DTOPlayer.setLastName(sc.next());

        DTOPlayer.setBalance(1000);
        DTOPlayer.setActive(true);

        Player player = new Player(DTOPlayer.getId(), DTOPlayer.getNickName(), DTOPlayer.getFirstName(), DTOPlayer.getLastName(), DTOPlayer.isActive(), BALANCE);
        players.add(player);

        System.out.println("Player created successfully");

    }

     static Player getPlayer(String nickName) {

        return players.stream()
                .filter(p -> p.getNickName().equalsIgnoreCase(nickName))
                .findFirst()
                .orElse(null);
    }

     static boolean checkValidID(long id) {
        return id < 1111111 || id > 99999999;
    }

     static void updatePlayer() {

        System.out.println("Please enter the player's nickname");

        Player updatedPlayer = getPlayer(sc.next());
        if (updatedPlayer == null) {
            System.out.println("A player does not exists with that nickName");
            return;
        }
        System.out.printf("Current first name is: %s \n", updatedPlayer.getFirstName());
        System.out.println("Please enter the new first name");
        updatedPlayer.setFirstName(sc.next());

        System.out.printf("Current lastname name is: %s \n", updatedPlayer.getLastName());
        System.out.println("Please enter the new last name");
        updatedPlayer.setLastName(sc.next());

        System.out.printf("Current id is: %d \n", updatedPlayer.getId());
        System.out.println("Please enter the id name");
        updatedPlayer.setId(sc.nextLong());

        players.stream()
                .filter(player -> player.getNickName()
                        .equalsIgnoreCase(updatedPlayer.getNickName()))
                .findFirst()
                .ifPresent(player -> {
                    player.setFirstName(updatedPlayer.getFirstName());
                    player.setLastName(updatedPlayer.getLastName());
                    player.setId(updatedPlayer.getId());
                });

        System.out.println("Player updated successfully");
    }

     static void updatePlayer(Player updatedPlayer) {

        players.stream()
                .filter(player -> player.getNickName()
                        .equalsIgnoreCase(updatedPlayer.getNickName()))
                .findFirst()
                .ifPresent(player -> {
                    player.setFirstName(updatedPlayer.getFirstName());
                    player.setLastName(updatedPlayer.getLastName());
                    player.setId(updatedPlayer.getId());
                    player.setBalance(updatedPlayer.getBalance());
                    player.setActive(updatedPlayer.isActive());
                });
    }

     static void deletePlayer() {

        System.out.println("Please enter the player's nickname");

        Player removedPlayer = getPlayer(sc.next());
        if (removedPlayer == null) {
            System.out.println("A player does not exists with that nickName");
            return;
        }
        players.stream()
                .filter(player -> player.getNickName()
                        .equalsIgnoreCase(removedPlayer.getNickName()))
                .findFirst()
                .ifPresent(player -> player.setActive(false));
        System.out.println("Player removed successfully");
    }

     static void gameQueries() {
        int choice = 0;

        while (choice != 4) {
            System.out.println("Welcome to the queries menu, please choose the option that suits you best:");
            System.out.println("1 - Display active Players");
            System.out.println("2 - Display all bets");
            System.out.println("3 - Display bets by player");
            System.out.println("4 - Back to previous menu");

            choice = sc.nextInt();

            switch (choice) {
                case 1 -> displayAllPlayers();
                case 2 -> displayAllBets();
                case 3 -> displayBetsByPlayers();
                case 4 -> System.out.println("Going back...");
                default -> System.out.println("❌ Invalid option. Please try again.");
            }
        }
    }

     static void sortPlayers(){

        for (int i = 1; i<players.size();i++)
        {
            int pointer = i;
            Player checker = players.get(i);
            while(pointer>0){
                Player checked = players.get(pointer-1);
                if(checked.getNickName().compareTo(checker.getNickName())>0) {
                    players.set(pointer, checked);
                    players.set(pointer - 1, checker);
                    pointer--;
                }
                else
                    pointer=0;
            }
        }
    }

     static void displayAllPlayers() {

        String format = "| %-15s | %-15s | %-12s | %-10s |%n";
        String line = "+-----------------+-----------------+--------------+------------+";
        System.out.println(line);
        System.out.printf(format, "Nickname", "First Name", "Last Name", "Balance");
        System.out.println(line);

        sortPlayers();

        players.forEach(player -> {
                    if (player.isActive())
                        System.out.printf(format, player.getNickName(), player.getFirstName(), player.getLastName(), player.getBalance());
                });

        System.out.println(line);

    }

     static void displayAllBets() {
        String format = "| %-15s | %-15s | %-12s | %-20s |%n";
        String line = "+-----------------+-----------------+--------------+----------------------+";

        System.out.println(line);
        System.out.printf(format, "Nickname", "Amount Gambled", "Won?", "Remaining Balance");
        System.out.println(line);

        for (Bet bet : bets) {
            System.out.printf(
                    format,
                    bet.getNickName(),
                    bet.getBetAmount(),
                    bet.isOutcome() ? "Player won" : "Player lost",
                    bet.getRemainingBalance()

            );
        }

        System.out.println(line);
    }

     static void displayBetsByPlayers() {
        System.out.println("Please enter the player's nickname");
        String format = "| %-15s | %-12s | %-21s |%n";
        String line = "+-----------------+-----------------+--------------------+";
        Player player = getPlayer(sc.next());

        if (player != null) {
            System.out.printf("The bets for the player ** %s ** are: %n", player.getNickName());

            List<Bet> playersBets = bets.stream()
                    .filter(bet -> bet.getNickName().equals(player.getNickName()))
                    .toList();
            if (!playersBets.isEmpty()) {
                System.out.println(line);
                System.out.printf(format, "Amount Gambled", "Won?", "Remaining Balance");
                System.out.println(line);
                playersBets.forEach(bet -> System.out.printf(
                        format,
                        bet.getBetAmount(),
                        bet.isOutcome() ? "Won!" : "Lost",
                        bet.getRemainingBalance()));
                System.out.println(line);

            }
        }
    }

    private static void playGame() {
        int amountGambled;
        int choice;
        int outcome;
        boolean hit;

        Random random = new Random();

        System.out.println("Welcome, we will start to play now. For each bet you must state with a 1 2 or 3, in which cup the ball is located. \nRemember that you can also chose to leave the game by tiping " + (GAME_SIZE + 1));
        System.out.println("Please enter your nickname");
        Player player = getPlayer(sc.next());
        if (player == null) {
            System.out.println("A player does not exists with that nickName");
            return;
        }
        choice = createCups();

        while (choice != (GAME_SIZE + 1)) {
            outcome = random.nextInt(3) + 1;

            amountGambled = placeBet();

            while (amountGambled < MINIMAL_BET) {
                System.out.printf("You can only place your bet between %d y %d %n", MINIMAL_BET, player.getBalance());
                System.out.println("How much would you like to bet?");
                amountGambled = placeBet();
            }

            createWinningCup(outcome);
            hit = outcome == choice;

            if (hit) {
                System.out.println("Congratulations! You have won");
            } else {
                System.out.println("Bummer, You have lost");
            }
            player.setBalance(updateBalance(player.getBalance(), hit, amountGambled));
            updatePlayer(player);
            System.out.printf("Your current balance is: %d \n", player.getBalance());

            bets.add(new Bet(amountGambled, hit, player.getNickName(), player.getBalance()));

            if (player.getBalance() < MINIMAL_BET)
                break;
            else {
                choice = createCups();

                if (amountGambled > 200 && !hit && choice == (GAME_SIZE + 1)) {
                    while (choice == (GAME_SIZE + 1)) {
                        System.out.println("You are a proud person so you cannot leave, you must play again");
                        choice = createCups();
                    }
                }
            }
        }
        if (player.getBalance() < MINIMAL_BET)
            System.out.println("Money talks, and you cannot talk");
        else
            System.out.println("See you later alligator");
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
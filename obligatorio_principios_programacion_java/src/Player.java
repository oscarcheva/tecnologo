public class Player {

    private long id;
    private String nickName;
    private String firstName;
    private String lastName;
    private int balance;
    private boolean active;

    public Player(long id, String nickName, String firstName, String lastName, boolean active, int balance) {
        this.id = id;
        this.nickName = nickName;
        this.firstName = firstName;
        this.lastName = lastName;
        this.active = active;
        this.balance = balance;
    }

    public Player() {
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getNickName() {
        return nickName;
    }

    public void setNickName(String nickName) {
        this.nickName = nickName;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public int getBalance() {
        return balance;
    }

    public void setBalance(int balance) {
        this.balance = balance;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}

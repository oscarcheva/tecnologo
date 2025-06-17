public class Bet {

    private int betAmount;
    private boolean outcome;
    private String nickName;
    private int remainingBalance;

    public Bet(int betAmount, boolean outcome, String nickName, int remainingBalance) {
        this.betAmount = betAmount;
        this.outcome = outcome;
        this.nickName = nickName;
        this.remainingBalance = remainingBalance;
    }

    public int getBetAmount() {
        return betAmount;
    }

    public void setBetAmount(int betAmount) {
        this.betAmount = betAmount;
    }

    public boolean isOutcome() {
        return outcome;
    }

    public void setOutcome(boolean outcome) {
        this.outcome = outcome;
    }

    public String getNickName() {
        return nickName;
    }

    public void setNickName(String nickName) {
        this.nickName = nickName;
    }

    public int getRemainingBalance() {
        return remainingBalance;
    }

    public void setRemainingBalance(int remainingBalance) {
        this.remainingBalance = remainingBalance;
    }
}

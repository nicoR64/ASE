package de.unistuttgart.ase.groupseven.sheetone;

public class BowlingGame {

    private static final int MAX_FRAMES_ALLOWED = 10;

    private final Frame[] officialFrames;
    private int currentFrame = 0;

    public BowlingGame() {
        this.officialFrames = new Frame[MAX_FRAMES_ALLOWED];
        for (int i = MAX_FRAMES_ALLOWED; i > 0; i--) {
            Frame frame;
            if (i == MAX_FRAMES_ALLOWED) {
                frame = new Frame(true);
            } else {
                frame = new Frame(officialFrames[i]);
            }
            officialFrames[i - 1] = frame;
        }
    }

    public void roll(int pins) {
        if (officialFrames[currentFrame].isFinished()) {
            currentFrame++;
        }
        if (currentFrame >= MAX_FRAMES_ALLOWED) {
            throw new IllegalStateException("No more rolls allowed");
        }
        officialFrames[currentFrame].roll(pins);
    }

    public int score() {
        int totalScore = 0;
        for (Frame frame : officialFrames) {
            totalScore += frame.getFullScore();
        }
        return totalScore;
    }
}

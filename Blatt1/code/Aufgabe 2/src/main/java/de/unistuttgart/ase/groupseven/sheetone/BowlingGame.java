package de.unistuttgart.ase.groupseven.sheetone;

/**
 * Maximilian Peresunchak (st152466@stud.uni-stuttgart.de)
 * Nico Reng (st188620@stud.uni-stuttgart.de)
 * Viorel Tsigos (st188085@stud.uni-stuttgart.de)
 * Philip Reimann (st182312@stud.uni-stuttgart.de)
 * Christian Keller (st166512@stud.uni-stuttgart.de)
 * Florian Frank  (st@stud.uni-stuttgart.de)
 * Johannes Heugel (st@stud.uni-stuttgart.de)
 * Maysaa Abualqumboz (st@stud.uni-stuttgart.de)
 * Benedikt Wachmer (st177118@stud.uni-stuttgart.de)
 * Miles Holl (st@stud.uni-stuttgart.de)
 */

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

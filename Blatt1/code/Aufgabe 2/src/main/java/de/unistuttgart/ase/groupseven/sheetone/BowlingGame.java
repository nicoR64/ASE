package de.unistuttgart.ase.groupseven.sheetone;

import org.jspecify.annotations.NullMarked;

/**
 * Models a bownling game consisting of {@link #MAX_FRAMES_ALLOWED} frames.
 * <p>
 * Internally, the game consists of an array with the size of {@link #MAX_FRAMES_ALLOWED} {@link Frame} objects.
 * Rolls are forwarded to the current played frame; when a frame is finished, the game goes on to the next frame.
 */
@NullMarked
public class BowlingGame {

    /**
     * Maximum number of frames in a game.
     */
    private static final int MAX_FRAMES_ALLOWED = 10;

    /**
     * The frames of the game.
     */
    private final Frame[] officialFrames;

    /**
     * Index of the currently played frame.
     */
    private int currentFrame = 0;

    /**
     * Constructs a new bowling game with {@link #MAX_FRAMES_ALLOWED} frames.
     * The last frame is marked as the last frame to allow bonus rolls and disable bonus calculation.
     */
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

    /**
     * Records a roll for the current frame. If the current frame is already finished, the game goes on to the next frame.
     *
     * @param pins the number of pins knocked down in this roll (0-{@link Frame#MAX_PINS})
     * @throws IllegalStateException if no more rolls are allowed (after the last frame is finished)
     */
    public void roll(int pins) throws IllegalStateException {
        if (officialFrames[currentFrame].isFinished()) {
            currentFrame++;
        }
        if (currentFrame >= MAX_FRAMES_ALLOWED) {
            throw new IllegalStateException("No more rolls allowed");
        }
        officialFrames[currentFrame].roll(pins);
    }

    /**
     * Calculates the total score of the game as the sum of the full scores of all frames.
     *
     * @return the total game score
     */
    public int score() {
        int totalScore = 0;
        for (Frame frame : officialFrames) {
            totalScore += frame.getFullScore();
        }
        return totalScore;
    }
}

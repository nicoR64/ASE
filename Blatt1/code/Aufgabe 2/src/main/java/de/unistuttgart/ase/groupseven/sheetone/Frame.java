package de.unistuttgart.ase.groupseven.sheetone;

import org.jspecify.annotations.NullMarked;
import org.jspecify.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Represents a frame in a bowling game.
 * <p>
 * The (normal) frame allows up to two rolls to knock down {@link #MAX_PINS}  (default 10) pins.
 * If this is the last frame {@link #isLastFrame}, the frame can have bonus rolls ({@link #BONUS_ROLLS_LAST_FRAME}) when {@link #isStrike()} or {@link #isSpare()}.
 * It computes the total score for the frame including bonus points when a strike or spare occurs.
 */
@NullMarked
public class Frame {

    /**
     * Maximum number of pins that can be knocked down in a frame (also relevant for a strike and spare).
     */
    private static final int MAX_PINS = 10;

    /**
     * Maximum number of regular rolls per frame.
     */
    private static final int MAX_ROLLS = 2;

    /**
     * Number of bonus rolls granted in the last frame for a spare (strike grants one more).
     */
    private static final int BONUS_ROLLS_LAST_FRAME = 1;

    /**
     * True if this is the (last) frame of the game.
     */
    private final boolean isLastFrame;

    /**
     * Reference to the next frame, used to compute bonus for strikes/spares. Is null for the last frame.
     */
    @Nullable
    private final Frame nextFrame;

    /**
     * All regular rolls in this frame.
     */
    private final List<Roll> rolls;

    /**
     * All bonus rolls in this frame, if this is the last frame.
     */
    private final List<Roll> bonusRollsLastFrame;

    /**
     * Internal Constructor.
     *
     * @param isLastFrame whether this is the last frame of the game
     * @param nextFrame   the next frame in the game
     */
    private Frame(boolean isLastFrame, @Nullable Frame nextFrame) {
        this.isLastFrame = isLastFrame;
        this.nextFrame = nextFrame;
        this.rolls = new ArrayList<>();
        this.bonusRollsLastFrame = new ArrayList<>();
    }

    /**
     * Creates a frame which is not the last frame and links it to the provided next frame.
     *
     * @param nextFrame the next frame in the game
     */
    public Frame(Frame nextFrame) {
        this(false, nextFrame);
    }

    /**
     * Creates a frame with the given last frame flag.
     *
     * @param isLastFrame whether this is the last frame of the game
     */
    public Frame(boolean isLastFrame) {
        this(isLastFrame, null);
    }

    /**
     * Creates a not last frame with no next frame.
     */
    public Frame() {
        this(false, null);
    }

    /**
     * Records a roll in this frame.
     * <p>
     * For a non last frame, up to two regular rolls are permitted unless a strike occurs.
     * For the last frame, spare/strike allows additional bonus rolls.
     *
     * @param pins the number of pins knocked down in this roll (0-{@link #MAX_PINS})
     * @throws IllegalArgumentException if {@code pins} is not between 0 and {@link #MAX_PINS} (inclusive)
     * @throws IllegalStateException    if no more rolls are allowed in this frame
     */
    public void roll(int pins) throws IllegalArgumentException, IllegalStateException {
        if (pins < 0 || pins > MAX_PINS) {
            throw new IllegalArgumentException(String.format("A roll has to be between 0 and %s", MAX_PINS));
        }
        if (rolls.size() < MAX_ROLLS && !isStrike()) {
            rolls.add(new Roll(pins));
            return;
        }

        if (!isLastFrame) {
            return;
        }

        if (isStrike() && bonusRollsLastFrame.size() <= BONUS_ROLLS_LAST_FRAME) {
            bonusRollsLastFrame.add(new Roll(pins));
        } else if (isSpare() && bonusRollsLastFrame.size() < BONUS_ROLLS_LAST_FRAME) {
            bonusRollsLastFrame.add(new Roll(pins));
        } else {
            throw new IllegalStateException("No more rolls allowed in this frame");
        }
    }

    /**
     * Returns an optional roll at the given index, counting both regular and bonus (last frame) rolls.
     *
     * @param index zero-based index of the roll
     * @return the roll at that index, or an empty optional if index is out of bounds
     */
    private Optional<Roll> getRoll(int index) {
        if (index < 0 || index >= rolls.size() + bonusRollsLastFrame.size()) {
            return Optional.empty();
        }
        return Optional.of(index < rolls.size() ? rolls.get(index) : bonusRollsLastFrame.get(index - rolls.size()));
    }

    /**
     * Indicates whether this frame is completed.
     *
     * @return true if the frame is completed false otherwise
     */
    public boolean isFinished() {
        if (!isLastFrame) {
            return isStrike() || rolls.size() >= MAX_ROLLS;
        }
        if (isStrike()) {
            return bonusRollsLastFrame.size() >= BONUS_ROLLS_LAST_FRAME + 1;
        }
        if (isSpare()) {
            return bonusRollsLastFrame.size() >= BONUS_ROLLS_LAST_FRAME;
        }
        return rolls.size() >= MAX_ROLLS;
    }

    /**
     * Provides the next frame if it exists.
     *
     * @return an Optional containing the next frame, or empty if no next frame exists
     */
    public Optional<Frame> getNextFrame() {
        return Optional.ofNullable(nextFrame);
    }

    /**
     * Determines whether this frame is a strike (all pins knocked down on the first roll).
     *
     * @return true if first roll equals {@link #MAX_PINS}; false otherwise
     */
    public boolean isStrike() {
        return getScore(0) == MAX_PINS;
    }

    /**
     * Determines whether this frame is a spare (all pins knocked down across the regular rolls).
     *
     * @return true if base score equals {@link #MAX_PINS} and the frame is not a strike; false otherwise
     */
    public boolean isSpare() {
        return !isStrike() && getBaseScore() == MAX_PINS;
    }

    /**
     * Computes the total score of this frame including bonus from following frames.
     *
     * @return the full frame score
     */
    public int getFullScore() {
        return getBaseScore() + getBonusScore();
    }

    /**
     * Computes the base score for this frame by summing up all base rolls including the scores from the bonus rolls.
     *
     * @return the base score for the frame
     */
    public int getBaseScore() {
        return rolls.stream().mapToInt(Roll::pins).sum() + bonusRollsLastFrame.stream().mapToInt(Roll::pins).sum();
    }

    /**
     * Returns the number of pins knocked down for the roll at the given index, or 0 when absent.
     *
     * @param index zero-based index across regular then bonus rolls
     * @return pins knocked down, or 0 if the roll does not exist
     */
    public int getScore(int index) {
        return getRoll(index).map(Roll::pins).orElse(0);
    }

    /**
     * Indicates if this frame is the last one in the game.
     *
     * @return true if last frame; false otherwise
     */
    public boolean isLastFrame() {
        return isLastFrame;
    }

    /**
     * Computes the bonus score for this frame.
     *
     * For non-final frames:
     * - {@link #isStrike()}: adds the base score from the following frame as bonus. If the next frame is also a strike, it peeks one more frame and reads the first roll there.
     * - {@link #isSpare()}: adds the first roll from the following frame as bonus.
     * For the final frame, no extra bonus is added.
     *
     * @return the bonus score for this frame
     */
    public int getBonusScore() {
        if (isLastFrame) {
            return 0;
        }
        if (isStrike() && getNextFrame().isPresent()) {
            Frame next = getNextFrame().get();
            if (next.isStrike()) {
                if (next.isLastFrame()) {
                    return next.getScore(0) + next.getScore(1);
                }
                return next.getBaseScore() + next.getNextFrame().map(frame -> frame.getScore(0)).orElse(0);
            }
            return next.getBaseScore();
        } else if (isSpare()) {
            return getNextFrame().map(frame -> frame.getScore(0)).orElse(0);
        }
        return 0;
    }
}

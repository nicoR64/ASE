package de.unistuttgart.ase.groupseven.sheetone;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Frame {

    private static final int MAX_PINS = 10;
    private static final int MAX_ROLLS = 2;
    private static final int BONUS_ROLLS_LAST_FRAME = 1;
    private final boolean isLastFrame;

    private final Frame nextFrame;

    private final List<Roll> rolls;
    private final List<Roll> bonusRollsLastFrame;

    private Frame(boolean isLastFrame, Frame nextFrame) {
        this.isLastFrame = isLastFrame;
        this.nextFrame = nextFrame;
        this.rolls = new ArrayList<>();
        this.bonusRollsLastFrame = new ArrayList<>();
    }

    public Frame(Frame nextFrame) {
        this(false, nextFrame);
    }

    public Frame(boolean isLastFrame) {
        this(isLastFrame, null);
    }

    public Frame() {
        this(false, null);
    }

    public void roll(int pins) {
        if (pins < 0 || pins > MAX_PINS) {
            throw new IllegalArgumentException(String.format("A roll has to be between 0 and %s", MAX_PINS));
        }
        if (rolls.size() < MAX_ROLLS && !isStrike()) {
            rolls.add(new Roll(pins));
            return;
        }
        if (isLastFrame) {
            if (isStrike()) {
                if (bonusRollsLastFrame.size() <= BONUS_ROLLS_LAST_FRAME) {
                    bonusRollsLastFrame.add(new Roll(pins));
                } else {
                    throw new IllegalStateException("No more rolls allowed in this frame");
                }
            } else if (isSpare()) {
                if (bonusRollsLastFrame.size() < BONUS_ROLLS_LAST_FRAME) {
                    bonusRollsLastFrame.add(new Roll(pins));
                } else {
                    throw new IllegalStateException("No more rolls allowed in this frame");
                }
            } else {
                throw new IllegalStateException("No more rolls allowed in this frame");
            }
        }
    }

    private Optional<Roll> getRoll(int index) {
        if (index < 0 || index >= rolls.size() + bonusRollsLastFrame.size()) {
            return Optional.empty();
        }
        return Optional.of(index < rolls.size() ? rolls.get(index) : bonusRollsLastFrame.get(index - rolls.size()));
    }

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

    public Optional<Frame> getNextFrame() {
        return Optional.ofNullable(nextFrame);
    }

    public boolean isStrike() {
        return getScore(0) == MAX_PINS;
    }

    public boolean isSpare() {
        return !isStrike() && getBaseScore() == MAX_PINS;
    }

    public int getFullScore() {
        return getBaseScore() + getBonusScore();
    }

    public int getBaseScore() {
        return rolls.stream().mapToInt(Roll::pins).sum() + bonusRollsLastFrame.stream().mapToInt(Roll::pins).sum();
    }

    public int getScore(int index) {
        return getRoll(index).map(Roll::pins).orElse(0);
    }

    public boolean isLastFrame() {
        return isLastFrame;
    }

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

package de.unistuttgart.ase.groupseven.sheetone;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;


class BowlingGameTests {

    private BowlingGame bowlingGame;

    @BeforeEach
    void setUp() {
        bowlingGame = new BowlingGame();
    }

    @Test
    void perfectGameTest() {
        rollTimes(10, 10);

        bowlingGame.roll(10); // Bonus roll 1
        bowlingGame.roll(10); // Bonus roll 2

        assertEquals(300, bowlingGame.score());
        assertThrows(IllegalStateException.class, () -> bowlingGame.roll(10));
    }

    @Test
    void withOnlySparesTest() {
        rollTimes(5, 18); // 18 because we need each roll twice

        // Frame 10 starts here
        bowlingGame.roll(5);
        bowlingGame.roll(5);
        bowlingGame.roll(10); // Bonus roll 1
        assertEquals(155, bowlingGame.score());
        assertThrows(IllegalStateException.class, () -> bowlingGame.roll(10));
    }


    // used first game here https://templatelab.com/wp-content/uploads/2021/03/bowling-score-sheet-08.jpg as testing data
    @Test
    void realGameTest() {
        bowlingGame.roll(5);
        bowlingGame.roll(5);

        bowlingGame.roll(4);
        bowlingGame.roll(5);

        bowlingGame.roll(8);
        bowlingGame.roll(2);

        bowlingGame.roll(10);

        bowlingGame.roll(0);
        bowlingGame.roll(10);

        bowlingGame.roll(10);

        bowlingGame.roll(6);
        bowlingGame.roll(2);

        bowlingGame.roll(10);

        bowlingGame.roll(4);
        bowlingGame.roll(6);

        bowlingGame.roll(10);
        bowlingGame.roll(10);
        bowlingGame.roll(0);

        assertEquals(169, bowlingGame.score());
        assertThrows(IllegalStateException.class, () -> bowlingGame.roll(10));
    }

    @Test
    public void wrongScoreTest() {
        assertThrows(IllegalArgumentException.class, () -> bowlingGame.roll(100));
        assertThrows(IllegalArgumentException.class, () -> bowlingGame.roll(-1));
    }

    @Test
    public void singleRollTest() {
        bowlingGame.roll(5);
        assertEquals(5, bowlingGame.score());
    }

    @Test
    public void noRollsTest() {
        assertEquals(0, bowlingGame.score());
    }

    @Test
    public void checkStrikeBonus() {
        bowlingGame.roll(10);
        bowlingGame.roll(5);
        bowlingGame.roll(5);
        assertEquals(30, bowlingGame.score());
    }

    @Test
    public void checkDoubleStrikeBonus() {
        bowlingGame.roll(10);
        bowlingGame.roll(10);
        bowlingGame.roll(5);
        assertEquals(45, bowlingGame.score());
    }

    @Test
    public void checkTripleeStrikeBonus() {
        bowlingGame.roll(10);
        bowlingGame.roll(10);
        bowlingGame.roll(10);
        assertEquals(60, bowlingGame.score());
    }

    @Test
    public void checkSpareBonus() {
        bowlingGame.roll(5);
        bowlingGame.roll(5);
        bowlingGame.roll(5);
        assertEquals(20, bowlingGame.score());
    }

    private void rollTimes(int scoreToRoll, int amount) {
        for (int i = 0; i < amount; i++) {
            bowlingGame.roll(scoreToRoll);
        }
    }
}